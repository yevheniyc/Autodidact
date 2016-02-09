#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

/* Be prepared accept a response of this length */
#define BUFSIZE 4096

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  transferclient [options]\n"                                                    \
"options:\n"                                                                  \
"  -s                  Server (Default: localhost)\n"                         \
"  -p                  Port (Default: 8888)\n"                                \
"  -o                  Output file (Default: foo.txt)\n"                       \
"  -h                  Show this help message\n"                              

/* Main ========================================================= */
int main(int argc, char **argv) {
	int option_char = 0; // used for commandline arguments
	char *hostname = "localhost"; // default hostname
	unsigned short portno = 8888; // default port to send request on
    // socket variables
	int sockfd, numbytes; // socket file descriptor, 
    struct sockaddr_in their_addr; // server's address info
    struct hostent *server; // struct to figure out IP from hostname
	char *filename = "foo.txt";
	char recvBuff[256]; // devide incoming file into these chunks
	int bytesReceived = 0;

	// Parse and set command line arguments
	while ((option_char = getopt(argc, argv, "s:p:o:h")) != -1) {
		switch (option_char) {
			case 's': // server
				hostname = optarg;
				break; 
			case 'p': // listen-port
				portno = atoi(optarg);
				break;                                        
			case 'o': // output file name
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
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	// server's info
	their_addr.sin_family = AF_INET; //host byte order
	their_addr.sin_port = htons(portno); // port - network byte order 
        //server = gethostbyname(hostname); // get the hostname IP
   	if ((server=gethostbyname(hostname)) == NULL) {
		herror("gethostbyname: ");
		exit(1);
	}
        // Show name and ip addresses of the server we are connecting to////////////////
 	printf("    IP Addresses: ");
 	struct in_addr **addr_list;
 	addr_list = (struct in_addr **)server->h_addr_list;
 	int i;
 	for (i = 0; addr_list[i] != NULL; i++) {
  		printf("%d ", inet_ntoa(*addr_list[i]));
  	}
  	printf("\n");
        printf("Official name is: %s\n", server->h_name);
	///////////////////////////////////////////////////////////////////////////////
        // copy the IP address into the server's address struct
	bcopy((char *)server->h_addr, (char *)&their_addr.sin_addr.s_addr, server->h_length); 
	memset(&(their_addr.sin_zero), '\0', 8); // zero the rest for the structure
	memset(recvBuff, '0', sizeof(recvBuff));

	// connect to the server
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	// create a file where data will be stored
	FILE *fp; 
	fp = fopen(filename, "ab");
	if (NULL == fp) {
		printf("Error opening file");
		return 1;
	}

	// receive data in chunks of 256 bytes
	while ((bytesReceived = read(sockfd, recvBuff, 256)) > 0 ) {
		printf("Bytes received %d\n", bytesReceived);
		fwrite(recvBuff, 1, bytesReceived, fp);
	}

	if (bytesReceived < 0) {
		printf("Read Error\n");
	}

	return 0;
}