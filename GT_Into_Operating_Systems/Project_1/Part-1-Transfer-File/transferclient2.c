/*
	transferclient2.c - Yevheniy Chuba - 02/13/2016
	A client that receives a file in chunks.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <getopt.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

//////////// GLOBALS /////////////////////////////////////////////////
/* Be prepared accept a response of this length */
#define BUFSIZE 256

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  transferclient [options]\n"                                                \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -o                  Output file (Default foo.txt)\n"                       \
"  -h                  Show this help message\n"                             
//////////////////////////////////////////////////////////////////////


/////// PROTOTYPES ////////////////////////////////////////////////////
void *get_in_addr(struct sockaddr *sa);
///////////////////////////////////////////////////////////////////////

/////// MAIN //////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	int sockfd; 					  // connect over sockfd
	int option_char = 0;			  // handle commanline argv
	char *hostname = "localhost";	  // the server our client will be connecting to
	unsigned short portno = 8888;	  // the port client will be connecting to
	char port_char[15];				  // technically 4 bytes should be enough - used for int portno -> char
	char  *message = "Hello World!";  // pointer to message to be sent
	char message_buff[BUFSIZE];		  // for sending and receiving messages
	int num_bytes_received; 		  // for receiving - how many bytes were actually received
	char ip_info[INET6_ADDRSTRLEN];   // enough to handle IPv6 as well as IPv4 addresses
	struct addrinfo hints,			  // hints - preload ? info; 
					*servinfo;		  // copy return from getaddrinfo() about the server
	int res;						  // return result flag for getaddrinfo
	char * filename = "foo.txt";	  // name of the file to be transferred in chunks

	char buffer[BUFSIZE];			  // buffer for receiving file length
	ssize_t len;                      // received length of the entier file about to be sent by the server
	int file_size;					  // the size of the actual chunk/file being sent
	FILE * received_file; 			  // the received file
	int remain_data = 0;			  // remaining data

	// Parse and set command line arguments
	while ((option_char = getopt(argc, argv, "s:p:o:h")) != -1) {
		switch (option_char) {
			case 's': // server
				hostname = optarg;
				break; 
			case 'p': // listen-port
				portno = atoi(optarg);
				break;                                        
			case 'o': // filename
				filename = optarg;
				break;       
			case 'h': // help
				fprintf(stdout, "%s", USAGE);
				exit(0);
				break;       
			default:
				fprintf(stderr, "%s", USAGE);
				exit(1);
		}
	}

	/* Socket Code Here */
	memset(&hints, 0, sizeof hints); // make sure hints struct is empty
	hints.ai_family = AF_INET;		 // IPv4 only for now
	hints.ai_socktype = SOCK_STREAM; // streaming sockets

	// get more detailed server information
	snprintf(port_char, sizeof port_char, "%d", portno); // convert numerial port to chars for here
	if ((res = getaddrinfo(hostname, port_char, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
		return 1;
	}
	printf("getaddrinfo is executed\n");

	// use that information to create socket to the proper server port
	if ((sockfd = socket(servinfo->ai_family,
					     servinfo->ai_socktype,
					     servinfo->ai_protocol)) == -1) {
		perror("client: socket");
		exit(1); // couldn't connect
	}
	printf("socket is created\n");

	// let's connect to the server: this is where getaddrinfo is handy
	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
		close(sockfd); // close if cannot connect
		perror("client: connect");
		exit(1);
	}

	// let's get server's information
	inet_ntop(servinfo->ai_family, 
			  get_in_addr((struct sockaddr *)servinfo->ai_addr), 
			  ip_info, sizeof ip_info);
	printf("client: connecting to %s\n", ip_info);



	// receiving the file size about to arrive
	recv(sockfd, buffer, BUFSIZE, 0);
	file_size = atoi(buffer); // array of chars into an integer
	fprintf(stdout, "\nFile size: %d\n", file_size);

	received_file = fopen(filename, "w");
	if (received_file == NULL) {
		fprintf(stderr, "Failed to open file foo --> %s\n", strerror(errno));
		exit(1);
	}

	remain_data = file_size; // starting with remaining data being the entire file

	// let's get the file chunk-by-chunk
	while (((len = recv(sockfd, buffer, BUFSIZE, 0)) > 0) && (remain_data > 0)) {
		// write into buffer the chunk we've received
		fwrite(buffer, sizeof(char), len, received_file);
		remain_data -= len;
		fprintf(stdout, "Received %d bytes and we hope: - %d bytes\n", (int)len, remain_data);
	}
	fclose(received_file);
	close(sockfd);

	return 0;
}
//////////////////////////////////////////////////////////////////


//////// FUNCTIONS ///////////////////////////////////////////////
/*
    get_in_addr - takes in pointer to struct of type sockaddr 
                - returns address of a string representing internet address
*/
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
//////////////////////////////////////////////////////////////////