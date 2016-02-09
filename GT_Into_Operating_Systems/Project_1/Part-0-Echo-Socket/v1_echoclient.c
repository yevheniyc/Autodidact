#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <getopt.h>

/* Be prepared accept a response of this length */
#define BUFSIZE 16 // however, we are hardcoding for now

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoclient [options]\n"                                                    \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -m                  Message to send to server (Default: \"Hello World!\"\n"\
"  -h                  Show this help message\n"                              

/* Main ========================================================= */
int main(int argc, char **argv) {
	int option_char = 0; // used for commandline arguments
	char *hostname = "localhost"; // default hostname
	unsigned short portno = 8888; // default port to send request on
	char *message = "Hello World!"; // default message to send to the server
        // socket variables
	int sockfd, numbytes; // socket file descriptor, 
        char buf[16]; // static buffer size
        struct sockaddr_in their_addr; // server's address info
        struct hostent *server; // struct to figure out IP from hostname

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
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	// server's info
	their_addr.sin_family = AF_INET; //host byte order
	their_addr.sin_port = htons(portno); // port - network byte order
        server = gethostbyname(hostname); // get the hostname IP
        printf("Hostname: %d\n", *server->h_addr); // test gethostbyname
        // copy the IP address into the server's address struct
	bcopy((char *)server->h_addr, (char *)&their_addr.sin_addr.s_addr, server->h_length); 
	memset(&(their_addr.sin_zero), '\0', 8); // zero the rest fo the structi

	// connect to the server
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	// send a message to the server
	if (send(sockfd, message, 15, 0) == -1) {
		perror("send");
	}
	// receive the message back
	if ((numbytes=recv(sockfd, buf, 15, 0)) == -1) {
		perror("recv");
		exit(1);
	}

	// including trailing 0
	buf[numbytes] = '\0';
	// print the echo from the server
	fprintf(stdout, "%s\n", buf);
	return 0;
}