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

#define BUFSIZE 4096

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -h                  Show this help message\n"                              



int main(int argc, char **argv) {
  int option_char;   // passed options
  int portno = 8888; /* port to listen on */
  struct sockaddr_in address;
  char buffer[16];
  int sock = -1;
  
  // Parse and set command line arguments
  while ((option_char = getopt(argc, argv, "p:h")) != -1){
    switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg); // global optarg; aoti -> int
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

  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = portno;

  bind(sock, (struct sockaddr *)&address, sizeof(struct sockaddr_in));
  listen(sock, 5);
  printf("%s: ready and listening on port %d\n", argv[0], portno);
  return 0;

}
