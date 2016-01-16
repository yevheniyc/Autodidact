/*
  transferserver2.c - Yevheniy Chuba - 02/13/2016
  A streaming server that upon accept()ing a connection
  transfers a file in chunks.
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
#include <errno.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

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

#define BUFFER_SIZE  256
#define MAX_PENDING  5
#define USAGE                                                                 \
"usage:\n"                                                                    \
"  transferserver [options]\n"                                                \
"options:\n"                                                                  \
"  -p                  Port (Default: 8888)\n"                                \
"  -f                  Filename (Default: bar.txt)\n"                         \
"  -h                  Show this help message\n"                             


void * get_in_addr(struct sockaddr * sa);

int main(int argc, char **argv) {
    int sockfd, new_fd;                 // listen on sock_fd, new connection on new_fd
    int option_char;                    // for handling commandline argv
    int portno = 8888;                  // default port to listen on
    char port_char[15];                 // use chars version for getaddrinfo()
    int maxnpending = MAX_PENDING;      // max of pending connections in the queue
    struct addrinfo hints,              // hints - preload server info; 
                    *servinfo;          // copy return from getaddrinfo() to servinfo
    struct sockaddr_storage their_addr; // connector's address informmation that handle both sockaddr_in and sockaddr_in6
    socklen_t sin_size;                 // their_addr' struct size
    char message_buff[BUFFER_SIZE];     // for receiving and sending messages
    int num_bytes_total;                // for sending - how many bytes were totally sent
    int res;                            // return result flag for getaddrinfo
    int yes;                            // used for setsockopt - to reap zombies
    char ip_info[INET6_ADDRSTRLEN];     // enough to handle IPv6 as well as IPv4
    char * filename = "bar.txt";        // pointer to first character of file name array
    FILE * file_pointer;                // pointer to file object
    int num_bytes_sent;                 // return from send() - bytes sent
    
    int fd;                             // file descriptor for sending a file
    struct stat file_stat;              // used with filestats and contains all sorts of info
    off_t offset;                       // helps with traking location in the file
    int remain_data;                    // remaining data
    char file_size[4];                // the size of the sending file or the sending chunk??
    ssize_t len;                        // length of the sent file size - we send if first so that client knows what to expect
    int sent_bytes = 0;                 // length of the actual file chunk that is being sent out


    // Parse and set command line arguments
    while ((option_char = getopt(argc, argv, "p:f:h")) != -1){
        switch (option_char) {
            case 'p': // listen-port
                portno = atoi(optarg);
                break;                                        
            case 'f': // listen-port
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
    memset(&hints, 0, sizeof hints);  // make sure hints is empty
    hints.ai_family = AF_INET;        // IPv4 only for now
    hints.ai_socktype = SOCK_STREAM;  // steaming 
    hints.ai_flags = AI_PASSIVE;      // my ip


    /* 
        get more detailed server information: 
        IMPORTANT: 
            - NULL in getaddrinfo says to get all info from the server - from here!
            - Client will have server's IP instead, which is more useful there
            - I need to practice with this!
    */
    snprintf(port_char, sizeof port_char, "%d", portno); // convert numerial port to chars for here
    if ((res = getaddrinfo(NULL, port_char, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return 1;
    }
    printf("getaddrinfo is executed\n");

    // use that information to create a socket: this info is especially handy in the client code
    if ((sockfd = socket(servinfo->ai_family, 
                         servinfo->ai_socktype, 
                         servinfo->ai_protocol)) == -1) {
        perror("server: socket");
        exit(1);
    }
    printf("socket is created\n");

    // get rid of zombie processes = lose the pesky "Address already in use" error message
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    printf("zombies are killed\n");

    // let's bind to the socket
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        close(sockfd);
        perror("server:bind");
        exit(1);
    }
    printf("bind to socket\n");

    // now let's listen to the socket
    if (listen(sockfd, maxnpending) == -1) {
        perror("listen");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) { // main accept loop
        sin_size = sizeof their_addr; // we want to know client's information
        
        // let's accept
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1){ // accept and cast to sockaddr pointer
            perror("accept");
            exit(1); // exit if acception did not work
        }

        // let's find connector's (client's) information
        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  ip_info, sizeof ip_info);
        printf("server: got connection from %s\n", ip_info);


        // let's handle files here for now
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Error opening file --> %s\n", strerror(errno));
            exit(1);
        }

        // get file stats
        if (fstat(fd, &file_stat) < 0) {
            fprintf(stderr, "Error fstat --> %s\n", strerror(errno));
            exit(1);
        }

        fprintf(stdout, "File Size: \n%d bytes \n", (int)file_stat.st_size); // get file size
        sprintf(file_size, "%d", (int)file_stat.st_size); // convert int to char

        // sending file size first
        len = send(new_fd, file_size, sizeof(file_size), 0);
        if (len < 0) {
            fprintf(stderr, "Error on sending greetings --> %s", strerror(errno));
            exit(1);
        }

        fprintf(stdout, "server: sent %d bytes for the size\n", (int)len);

        // initiate variables for keeping how much as been sent out
        offset = 0;
        remain_data = file_stat.st_size;

        // sending file data in chunks
        while (((sent_bytes = sendfile(new_fd, fd, &offset, BUFFER_SIZE)) > 0) && (remain_data > 0)) { // the size of sent chunk ...i think
            fprintf(stdout, "1. Server sent %d bytes from file's data, offset is now: %d and remaining data = %d\n", sent_bytes, (int)offset, remain_data);
            remain_data -= sent_bytes;
            fprintf(stdout, "2. Server sent %d bytes from file's data, offset is now: %d and remaining data = %d\n", sent_bytes, (int)offset, remain_data);
        }
        close(sockfd);
        close(new_fd);
    }

    return 0;

}

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