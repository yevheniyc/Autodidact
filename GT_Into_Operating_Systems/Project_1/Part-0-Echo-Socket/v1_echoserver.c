#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

#define BUFSIZE 16 // however, we are hadcoding for now

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -n                  Maximum pending connections\n"                         \
"  -h                  Show this help message\n"                              

int main(int argc, char **argv) {
  int option_char; // used for command line options
  int portno = 8888; /* port to listen on */
  int maxnpending = 5; // number of connections allowed; usually 20 by default
  char *hostname = "localhost"; // server's default hostname
  // socket variables
  int sockfd, new_fd; // listen on sockfd; when client connects, new file descriptor
  struct sockaddr_in my_addr; // my address info of sockaddr_in type
  struct sockaddr_in their_addr; //  client's address info of sockaddr_in type
  int sin_size;
  char buf[16]; // hardcode buffer size for now
  int numbytes;
  struct hostent *server; // struct to figure out IP from hostname
  int yes;
 
  // Parse and set command line arguments
  while ((option_char = getopt(argc, argv, "p:n:h")) != -1){
    switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg);
        break;                                        
      case 'n': // server
        maxnpending = atoi(optarg);
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

  // free any bound sockets
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  // before binding build server (my machine) network info
  my_addr.sin_family = AF_INET; // my host byte order
  my_addr.sin_port = htons(portno); // short, turn to network byte order
  // get the server IP into hostent struct
  server = gethostbyname(hostname);
  // copy the IP address into the server's (my local machine) address struct
  bcopy((char *)server->h_addr, (char *)&my_addr.sin_addr.s_addr, server->h_length);
  memset(&(my_addr.sin_zero), '\0', 8); // zero the rest of the structure
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

  // now let's wait and accept new connections
  while(1) {
    // the size of a struct of type sockaddr_in
    sin_size = sizeof(struct sockaddr_in);
    // waiting for the connections
    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
      perror("accept");
      continue;
    }

    // recieve the message from the client
    if ((numbytes=recv(new_fd, buf, 15, 0)) == -1) {
        perror("recv");
	    exit(1);
    }

    // send the received message back to the client
    if (send(new_fd, buf, 15, 0) == -1) {
	perror("send");
    }
    
    // include trailing 0
    buf[numbytes] = '\0';
    // print the message sent from the client
    fprintf(stdout, "%s\n", buf);
  }
  return 0;
}
