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
    struct sockaddr_in address_server; // address info of the server
    struct sockaddr address_client; // address info of a connected client
    int addr_client_len; // length of the client field
    int read_size; // size of the message received
    char client_message[16];
    int sock_server;
    int sock_client;

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

    sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    address_server.sin_family = AF_INET;
    address_server.sin_addr.s_addr = INADDR_ANY;
    address_server.sin_port = portno;

    bind(sock_server, (struct sockaddr *)&address_server, sizeof(struct sockaddr_in));
    listen(sock_server, 5);
    printf("%s: ready and listening on port %d\n", argv[0], portno);

    while(1) {
        sock_client = accept(sock_server, (struct sockaddr *)&address_client, (socklen_t *) sizeof(struct sockaddr_in));
        
        while ((read_size = recv(sock_client, client_message, 15, 0)) > 0 ) // I think 0 will be added to the end
            write(sock_client, client_message, strlen(client_message)); // return the message
    }
}
