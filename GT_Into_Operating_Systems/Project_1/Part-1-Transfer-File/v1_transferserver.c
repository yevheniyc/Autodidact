#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#if 0
/* 
 * Structs exported from netinet/in.h (for easy reference)
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr; 
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

#define BUFSIZE 4096

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  transferserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -f                  Filename (Default: bar.txt)\n"                         \
"  -h                  Show this help message\n"                              

int main(int argc, char **argv) {
  int option_char; // used for command line options
  int portno = 8888; /* port to listen on */
  char *filename = "bar.txt"; // file to transfer
  char *hostname = "localhost"; // server's default hostname
  // socket variables
  int sockfd, new_fd; // listen on sockfd; when client connects, new file descriptor
  struct sockaddr_in my_addr; // my address info of sockaddr_in type
  struct sockaddr_in their_addr; //  client's address info of sockaddr_in type
  int sin_size;
  char sendBuff[1025]; // send buffer size
  int numbytes;
  struct hostent *server; // struct to figure out IP from hostname
  int yes;
  int maxnpending = 5;
 
  // Parse and set command line arguments
  while ((option_char = getopt(argc, argv, "p:f:h")) != -1){
    switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg);
        break;                                        
      case 'f': // file to transfer
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
  // create a new socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket"); 
    exit(1);
  }

  // free any bound sockets (not freeing the port as fast as I thought it would)
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  // before binding build server (my machine) network info
  my_addr.sin_family = AF_INET; // my host byte order
  my_addr.sin_port = htons(portno); // short, turn to network byte order
  // get the server IP into hostent struct
  server = gethostbyname(hostname);
  // Show name and ip address(es) of the server - Udacity is not working; however local is/////
  printf("    IP Addresses: ");
  struct in_addr **addr_list;
  addr_list = (struct in_addr **)server->h_addr_list;
  int i;
  for (i = 0; addr_list[i] != NULL; i++) {
    printf("%s ", inet_ntoa(*addr_list[i]));
  }
  printf("\n");
  printf("Official name is: %s\n", server->h_name);
  //////////////////////////////////////////////////////////////////
  // copy the IP address into the server's (my local machine) address struct
  bcopy((char *)server->h_addr, (char *)&my_addr.sin_addr.s_addr, server->h_length);
  memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the structure
  memset(sendBuff, '0', sizeof(sendBuff)); // zero the rest of the buffer
  // bind to a proper port
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }
  // listen to incomming connections
  if (listen(sockfd, maxnpending) == -1) {
    perror("listen");
    exit(1);
  }
  // a message that the server is waiting for connections
  printf("Server is waiting for connections...hostname: %d, port: %d\n", *server->h_addr, portno);
  // now let's wait and accept new connections
  while(1) {
    // the size of a struct of type sockaddr_in
    sin_size = sizeof(struct sockaddr_in);
    // waiting for the connections
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
      perror("accept");
      continue;
    }

    // Open the file we want to transfer
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("File open error.");
	return 1;
    }

    // Read data from the file and send it
    while (1) {
        // Read file in chinks of the specified size
        unsigned char buff[256] = {0};
        int nread = fread(buff, 1, 256, fp);
        printf("Bytes read %d\n", nread);

        // if read was success, send out data
        if (nread > 0) {
            printf("Sending\n");
            write(new_fd, buff, nread);
        }

        // check file integrity/if it is the end
        if (nread < 256) {
            if (feof(fp)) {
            printf("End of file\n");
            }
            if (ferror(fp)) {
            printf("Error reading\n");
            }
            break;
        }
    }
 
    // after file is transferred, close the socket/connection  
    close(new_fd);
    exit(0);
  }
  return 0;
}