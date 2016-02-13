/*
  echoserver2.c - a stream socket that repeats and sends back client's message
*/

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

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -n                  Maximum pending connections\n"                         \
"  -h                  Show this help message\n"                              

int main(int argc, char **argv) {
  int sockfd, new_fd;                 // listen on sock_fd, new connection on new_fd
  int option_char;                    // for handling commandline argv
  int portno = 8888;                  // default port to listen on 
  int maxnpending = 5;                // max of pending connections in the queue
  struct addrinfo hints,              // hints - preload know server info; 
                  *servinfo;          // copy return from getaddrinfo() to servinfo
  struct sockaddr_storage their_addr; // connector's address informmation
  socklen_t sin_size;                 // their_addr' struct size
  char buf[16];                       // for receiving and sending messages 
  
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
  memset(&hints, 0, sizeof hints);  // make sure hints is empty
  hints.ai_family = AF_INET;        // IPv4 only for now
  hints.ai_socktype = SOCK_STREAM;  // steaming 
  hints.ai_flags = AI_PASSIVE;      // my ip



}