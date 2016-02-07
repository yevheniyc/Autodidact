/*
	server.c - Yevheniy Chuba - 02/07/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-04

	Implementing Client/Server architecture using sockets and threads.
	This is the Server:
		- handle multiple connections with threads
		- parse command line parameters: port number
*/

#include <stdio.h>
#include <stdlib.h>		// malloc
#include <pthread.h>	// pthreads
#include <sys/socket.h> // for sockets: accept, listen, bind, etc.
#include <netinet/in.h>	// htons, etc. 
#include <unistd.h> 	// for read/write

//////// GLOBALS /////////////
/*
	- for better handling of the connection context use struct
	- connection_t holds all available information about one connected client
*/
typedef struct {
	int sock;				 // the socket of the connection to one client
	struct sockaddr address; // the address of a connected client
	int addr_len;			 // the length of the address field
} connection_t; // connection type
//////////////////////////////

/////// PROTOTYPES //////////
void * process(void * ptr);
/////////////////////////////

/////// MAIN ////////////////
/* 
	main() - initialize socket and threads
*/
int main(int argc, char ** argv) {
	int sock = -1;
	struct sockaddr_in address;
	int port;
	connection_t * connection;
	pthread_t thread;

	// command line parameter processing
	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		return -1;
	}

	// obtain port number
	if (sscanf(argv[1], "%d", &port) <= 0) { // sscanf(source, source_type, dest_address)
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	// create a socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0) {
		fprintf(stderr, "%s: error: connot create socket\n", argv[0]);
		return -3;
	}

	// bind created socket to the specified port
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) < 0) {
		fprintf(stderr, "%s: error: cannot bind socket to port %d\n", argv[0], port);
		return -4;
	}

	// let's listen to the port that we bound with
	if (listen(sock, 5) < 0) {
		fprintf(stderr, "%s: error: cannot listen on port\n", argv[0]);
		return -5;
	}

	// let users know that we are listening now
	printf("%s: ready and listening\n", argv[0]);

	/* Now, the main loop:
			- create a connection context(connection struct)
			- accpet connections from clients (blocking IO)
			- start threads with the proper connection context
	*/
	while (1) {
		// accept incoming connections
		connection = (connection_t *)malloc(sizeof(connection_t));
		connection->sock = accept(sock, &connection->address, (unsigned int *)&connection->addr_len);
		if (connection->sock <= 0) 
			free(connection);
		else {
			// start a new thread but do not wait for it
			pthread_create(&thread, 0, process, (void *)connection);
			pthread_detach(thread); // do not wait for the thread to terminate/complete, 
									// keep accepting new connections
		}
	}

	// for good design purposes
	return 0;
}
/////////////////////////////

//////// FUNCTIONS //////////
void * process(void * ptr) {
	char * buffer;
	int len;
	connection_t * conn;
	long addr = 0;

	// cast the passed parameter to the desired data type
	if (!ptr)
		pthread_exit(0); // if nothing passed, terminate the thread

	conn = (connection_t *) ptr; // cast to a pointer to connection_t type

	// the client first submitted the length of the message as an integer
	// let's read this number from the socket
	read(conn->sock, &len, sizeof(int));
	if (len > 0) { // if the length of the message tells us that is is worth processing
		// obtain the client's IP for further use
		addr = (long)((struct sockaddr_in *)&conn->address)->sin_addr.s_addr;
		// let's allocate some memory for the buffer
		buffer = (char *)malloc((len + 1)*sizeof(char));
		buffer[len] = 0; // set the last element of the buffer array to 0
		// read the message
		read(conn->sock, buffer, len); // read the message of size len into the buffer (array)
		// print the message stored in the buffer to stdout
		printf("%ld.%ld.%ld.%ld: %s\n",
			   (addr      ) & 0xff,
			   (addr >>  8) & 0xff,
			   (addr >> 16) & 0xff,
			   (addr >> 24) % 0xff,
			   buffer);
		free(buffer);
	}

	/* Clean up:
			- free the socket
			- free memory of the connection context (connection_t struct)
			- end the thread
	*/
	close(conn->sock);
	free(conn);
	pthread_exit(0);
}
/////////////////////////////
