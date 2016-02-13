/*
	echoclient2.c - Yevheniy Chuba - 02/13/2016
	A client that sends a message to the server on a socket
	and receives back the message!
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


//////////// GLOBALS /////////////////////////////////////////////////
/* Be prepared accept a response of this length */
#define BUFSIZE 16

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoclient [options]\n"                                                    \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -m                  Message to send to server (Default: \"Hello World!\"\n"\
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

	// Parse and set command line arguments
	while ((option_char = getopt(argc, argv, "s:p:m:h")) != -1) {
		switch (option_char) {
			case 's': // server
				hostname = optarg;
				break; 
			case 'p': // listen-port
				portno = atoi(optarg);
				break;                                        
			case 'm': // server
				message = optarg;
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

	// send our message
	if (send(sockfd, message, BUFSIZE, 0) == -1) {
		perror("send");
		exit(1);
	}

	// recv our message back
	if ((num_bytes_received = recv(sockfd, message_buff, BUFSIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	// make sure the received back message is null terminated
	message_buff[num_bytes_received] = '\0';
	printf("client: i've go this message back from server: %s\n", message_buff);

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