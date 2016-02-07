/*
	client.c - Yevheniy Chuba - 02/06/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-04

	Implementing Client/Server architecture using sockets and threads.
	This is the Client:
		- parse command line parameters: server IP/host, server port, the message
		- create socket
		- find server with gethostbyname(domain name)
		- connect to the server
		- write a message
		- close socket

	Intro:
		The process handling is much more resource consuming than 
		the handling of threads, the complexity is about the same. 
		The advantage of being less resource consuming has an important 
		disadvantage. If one thread (handling one connection) dumps the core, 
		it will affect the other threads as well.
*/

#include <stdio.h>
#include <sys/socket.h> // sockets: socket, connect
#include <netdb.h>		// htons, etcs
#include <string.h>		// memcpy
#include <unistd.h>		// read/write

/*
	main()
*/
int main(int argc, char ** argv) {
	int port;
	int sock = -1;
	struct sockaddr_in address;
	struct hostent * host;
	int len;

	// checking commandline parameters
	if (argc != 4) {
		printf("Usage: %s hostname port text\n", argv[0]); // executable name
		return -1; // terminate
	}

	// the number of parameters was ok, let's obtain port number
	if (sscanf(argv[2], "%d", &port) <= 0) { // sscanf(source_arg, "source_arg type", dest_address)
		fprintf(stderr, "%s: error: wrong parameter: port\n", argv[0]);
		return -2;
	}

	// create a TCP socket for streaming data and for the Internet domain
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock <= 0) {
		fprintf(stderr, "%s: error: cannot create socket\n", argv[0]);
		return -3;
	}

	// get server address and connect to the server
	address.sin_family = AF_INET; 	// specify address family
	address.sin_port = htons(port); // add port info to address - host byte order -> network byte order
	host = gethostbyname(argv[1]); 	// get host info
	if (!host) { // check if gethostbyname has returned assaciated info
		fprintf(stderr, "%s: error: unknown host/server %s\n", argv[0], argv[1]);
		return -4;
	}
	// memcpy(void * dest, void * src, int number_of_chars_copied)
	// copy host ip to the address sturct used by socket
	memcpy(&address.sin_addr, host->h_addr_list[0], host->h_length);

	/*
		at this point we have:
			- socket
			- address to host/server

		now let's connect!
	*/
	if (connect(sock, (struct sockaddr *)&address, sizeof(address))) { // if not 0 -> error
		fprintf(stderr, "%s: error: cannot connect to host %s\n", argv[0], argv[1]);
		return -5;
	}

	/*
		the connection is now open to the server
		now let's send some messages:
			- first, send the length of the incomming message
			- second, send the actual message
	*/
	len = strlen(argv[3]);
	write(sock, &len, sizeof(int)); // pass address of len with size of int (4 bytes)
	write(sock, argv[3], len); // pass address of the first character in argv[3] array of characters

	// close the socket
	close(sock);

	return 0;
}