Network Sockets
---------------

The following code/desciptions are borrowed and analyzed from:
http://beej.us/guide/bgnet/output/html/multipage/theory.html

This is a summary document created for learning purposes. Most of the text is copied from the original source.
Writing everything by hand helped me to remember all of this (which is a lot). I also wanted to create a shorter 
single page document for easy reference. 


File Descriptors
^^^^^^^^^^^^^^^^
File descriptor for network communication is retrieved by::
	a call to the socket() system routine

File descriptor https://en.wikipedia.org/wiki/File_descriptor:
	* In Unix and related computer operating systems, a file descriptor (FD) is an abstract indicator used to access a file or other input/output resource, such as a pipe or network connection. 
	* File descriptors form part of the POSIX application programming interface. 
	* A file descriptor is a non-negative integer, represented in C programming language as the type int.
	* Each Unix process (except perhaps a daemon) should expect to have three standard POSIX file descriptors, corresponding to the three standard streams:
		* 0 -> standard input  -> STDIN_FILENO  (unistd.h - symbolic constant) -> stdin  (stdio.h - file stream)
		* 1 -> standard output -> STDOUT_FILENO (unistd.h - symbolic constant) -> stdout (stdio.h - file stream)
		* 2 -> standard error  -> STDERR_FILENO (unistd.h - symbolic constant) -> stderr (stdio.h - file stream)
		
	* In the traditional implementation of Unix, file descriptors index into a per-process file descriptor table maintained by the kernel, that in turn indexes into a system-wide table of files opened by all processes, called the **file table**. 
	* File Table records the mode with which the file (or other resource) has been opened for:
		* reading 
		* writing
		* appending
		* reading and writing
		* possibly other modes
		
	* File Table also indexes into a third table called the **inode table** that describes the actual underlying files.
	* To perform input or output, the process passes the file descriptor to the kernel through a system call, and the kernel will access the file on behalf of the process. The process does not have direct access to the file or **inode tables**.
	* On Linux, the set of file descriptors open in a process can be accessed under the path /proc/PID/fd/, where PID is the process identifier.
	* In Unix-like systems, file descriptors can refer to any Unix file type named in a file system. As well as regular files, this includes:
		* directories
		* block and character devices (also called "special files")
		* Unix domain sockets
		* named pipes. 
		
	* File descriptors can also refer to other objects that do not normally exist in the file system:
		* anonymous pipes
		* network sockets
		
	* The **FILE** data structure in the C standard I/O library usually includes a low level file descriptor for the object in question on Unix-like systems. The overall data structure provides additional abstraction and is instead known as a **file handle**.
	* Operations on file descriptors:
		* creating file descriptors::
	
			- open()
			- creat()
			- socket()
			- accept()
			- socketpair()
			- pipe()
			- opendir()
		* operations on a single file descriptor::
	
			- read(), write()
			- readv(), writev()
			- pread(), pwrite()
			- recv(), send()
			- recvmsg(), sendmsg()
			- sendfile()
			- lseek()
			- fstat()
			- fchmod()
			- fchown()
			- fdopen()
			- ftruncate()
			- fsync()
			- fdatasync()
			- fstatvfs()
		* operations on multiple file descriptors::
	
			- select(), pselect()
			- poll()
			- epoll() (linux)
			- kqueue() (BSD)
		* operations on the file descriptor table::
	
			-  The fcntl() function is used to perform various operations on a file descriptor, depending on the command argument passed to it. There are commands to get and set attributes associated with a file descriptor, including F_GETFD, F_SETFD, F_GETFL and F_SETFL.
	
			- close()
			- closefrom() (BSD)
			- dup()
			- dup2()
			- fcntl(F_DUPFD)
		* operations that modify process state::
	
			- fchdir() -> sets the process's current working directory based on a directory file descriptor
			- mmap()   -> maps ranges of a file into the process's address space
		* file locking::
	
			- flock()
			- fcntl()
			- lockf()
		* **Sockets**::
	
			- connect()
			- bind()
			- accept() - creates a new file descriptor for an incoming connection
			- getsockname()
			- getpeername()
			- getsockopt()
			- setsockopt()
			- shutdown() - shuts down one or both halves of a full duplex connection

It returns the socket descriptor over which communication is possible using the specialied::
	
	send() and recv() socket calls

We could use read() and write() calls to communication through the socket, however, send() and recv() offer greater control over data transmission.


Unix Sockets
^^^^^^^^^^^^
Types of sockets:
	* DARPA Internet addresses (Internet Sockets)
	* Path names on a local node (Unix Sockets)
	* CCITT X.25 addresses (X.25 Sockets)

Two types of Internet sockets:
	* Stream Sockets -> "SOCK_STREAM"
	* Datagram Sockets -> "SOCK_DGRAM" == "connectionless sockets"

Stream sockets:
	* provide reliable two-way connected communication streams
	* if two items are output into the socket in order '1, 2', they will arrive in that order on the opposite side
	* error-free communication (almost always) 

Who uses stream sockets:
	* telnet www.google.com "GET / HTTP/1.0"
	* web browsers use the HTTP protocol which uses stream sockets to get pages

What stream sockets are using for such a high quality transmission:
	* stream sockets use TCP protocol
	* TCP protocol ensures sequential data arrival

Datagram Sockets:
	* connectionless sockets that use UDP
	* no need to maintain open connection: build a packet, add IP header with destination information and send
	* Used when dropped packets are not a big deal: tftp, dhcpcd, multiplayer games streaming audio, video converencing

How tftp, dhcpcd and others retain data integrity if packets are lost?
	* tftp and similar programs have their own protocol on top of UDP. For example, the tftp protocol says that for each packet that gets sent, the recipient has to send back a packet that says, "I got it!" (an "ACK" packet). If the sender of the original packet gets no reply in, say, five seconds, he'll re-transmit the packet until he finally gets an ACK. This acknowledgment procedure is very important when implementing reliable SOCK_DGRAM applications.
	
	* It's way faster to fire-and-forget than it is to keep track of what has arrived safely and make sure it's in order and all that. If you're sending chat messages, TCP is great; if you're sending 40 positional updates per second of the players in the world, maybe it doesn't matter so much if one or two get dropped, and UDP is a good choice


Network Theaory Overview
^^^^^^^^^^^^^^^^^^^^^^^^
So how SOCK_DGRAM packets are built? 

Data Encapsulation (bottom -> top):
	* Ethernet - hardware strips ethernet header
	* IP - kernel strips IP header
	* UDP/TCP - kernel strips UDP header
	* TFTP - tftp program strips this header
	* Data - we handle this!

Unix Network Model (button -> top):
	* Network Access Layer (Ethernet, wi-fi)
	* Internet Layer (IP/routing)
	* Host-to-Host Transport Layer (TCP, UDP)
	* ApplicationLayer (telnet, ftp)

Of course all of this is invisible to us and all we have to do is:
	* stream sockets -> **send()** the data out
	* datatagram sockets -> encapsulate the packet in the method of your choosing and **sendto() it out
	* the kernel builds the Transport Layer and Internet Layer and the hardware does the Network Access Layer!
	* routers strip the packet to the IP header, consult routing tables... I am taking a different course for that (check my Python repo)


IP Addresses, stucts and Data Munging
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Here we will discuss IP addresses, ports, and how sockets API stores and manipulates IP addresses and other data.

IP Addresses, version 4 and 6:
	* IPv4 -> Vint Cert -> 32bit -> 2^32 - running out -> 192.0.2.111
	* IPv6 -> 128bit -> 2^128 -> alot -> hex -> 2001:0db8:c9d2:aee5:73e3:934a:a5ae:9551 -> IPv6 compression::

		2001:0db8:c9d2:0012:0000:0000:0000:0051
		2001:db8:c9d2:12::51

		2001:0db8:ab00:0000:0000:0000:0000:0000
		2001:db8:ab00::

		0000:0000:0000:0000:0000:0000:0000:0001
		::1 -> loopback!

	* IPv4 in IPv6 wrapper::

		192.0.2.33 -> ::ffff:192.0.2.33


Subnets
^^^^^^^
IP address - 192.0.2.12 -> host 12 on network 192.0.2.0:
	* network portion - first 3 bytes
	* host portion - last byte

Network classes:
	* A -> 1 byte for network and 3 bytes for hosts
	* B -> 2 bytes for network and 2 bytes for hosts
	* C -> 3 bytes for network and 1 byte for hosts

Network portion of the IP address is descibed by netmask:
	* with netmask of 255.255.255.0, if IP is 192.0.2.12 -> network is 192.0.2.12 AND 255.255.255.0 0, which gives 192.0.2.0
	* this was unsustainable
	* netmask now is allowed to be an arbitrary number of bits, not just 8, 16, 24:
		* netmask could be 255.255.255.252 with 30 bits representing network and 2 bits of hosts (2^2 hosts on the network)
		* the netmask is ALWAYS a bunch of 1-bits followed by a bunch of 0-bits

	* to represent IPv4 network, use 192.0.2.12/30, where:
		* 30 out of 32 bits of the IP address for the network
		* 2 out of 32 bits of the IP address for the hosts

	* to represent IPv6:
		* 2001:db8::/32 or 2001:db8:5413:4028::9db9/64.


Port Numbers
^^^^^^^^^^^^
In the network model both IP (Internet Layer) and TCP/UDP (Transport Layer) represent addresses:
	* IP address:
		* 32 bits IPv4 and 128 bits IPv6
		* specifies the network location (your company) and subnets (your company's servers)
		* they are used for node-to-node communication
	
	* Port address
		* 16 bits
		* used by TCP (stream sockets) and UDP (datagram sockets)
		* serves as a local address for the connection
		* for example, any message comming on port# 5324 (on company's network) is a stream socket communication handled by TCP protocol
		* so how would a single computer handle incoming mail and web services and sockets?
			* different internet services on the web have well-known port numbers
			* the Big IANA Por List specifies them
			* on Unix, `vi /etc/services' file
			* HTTP - 80, telnet - 23, SMTP - 25, special - 1024 (requires OS privileges)


Byte Order
^^^^^^^^^^
The way computer stores bytes:
	* two-byte hex number (b34f) is saved sequencially with b3 and then 4f - big end first -> ** Big Endian **
	* Intel/Intel-compatible processors store bytes reversed - in memory with 4f and then b3 - little end first -> ** Little-Endian**

Terminology:
	* Big Endian is also called ** Network Byte Order **, because that is the direction 0|1s are traveling via wires
	* Our computer stores numbers in ** Host Byte Order **, which as mentioned above could be in Big or Little Endian. For example:
		* Intel 80x86's Host Byte Order is Little-Endian
		* Motorola 68k's Host Byte Order is Big-Endian
		* For PCs - it depends (of course)

So, how do we keep track of which Host Byte Order my computer stores 0|1s in? If I don't know the Host Byte Order, how do I make sure that my two- and four-byte 0|1s I use for building packets or data structures are in Network Byte Order?
	* we assume that the Host Byte Order isn't right
	* we **always** run the packet via a function that sets our numbers to Network Byte Order
	* now our code is portable to machines of different endianness!

Conversion:
	* there are two types of numbers we can convert from Host Byte Order -> Network Byte Order: short(two bytes) and long(four bytes)
	* work for the unsigned variations as well
	* to convert a short from Host Byte Order to Network Byte Order: htons (Host to Network Short). More examples::

		----------------------------------------------------------------------------------
		htons() - host to network short - sending 2-byte data from a program via network
		htonl() - host to network long  - sending 4-byte data from a program via network
		ntohs() - network to host short - receiving 2-byte data from network into a program
		ntohl() - network to host long  - recieving 4-byte data from network into a program
		-----------------------------------------------------------------------------------

	* for 64-bit systems and for floating point use a different research paper


Structs
^^^^^^^
Let's cover different data types used by the sockets interface

Socket descriptor type::
	
	int

When making a connection, one of the first structs used is struct addrinfo.
	* it is used to prepare the socket address structures for subsequent use
	* it is used in host name lookups
	* it is used in service name lookups
	* struct addrinfo holds address information, example::

		struct addrinfo {
			int 			ai_flags; 		// AI_PASSIVE, AI_CANNONNAME, etc.
			int 			ai_family; 		// AF_INET, AF_INET6, AF_UNSPEC
			int 			ai_socktype; 	// SOCK_STREAM, SOCK_DGRAM
			int 			ai_protocol; 	// use 0 for "any"
			size_t	 		ai_addrlen; 	// size of ai_addr in bytes (2 vs. 4 bytes, depending on Internet Protocol)
			struct sockaddr *ai_addr;		// struct sockaddr_in or _in6
			char 			*ai_canonname;	// full canonical hostname

			struct addrinfo *ai_next; 		// linked list, next node

		}

	* this struct will be loaded a bit and then used for getaddrinfo()
		* getaddrinfo() will return a pointer to a new linked list of these structures, filled out will all network/host info we need!
	
	* we can force it to use IPv4 or IPv6 in the ai_family field, or leave it as AF_UNSPEC - to use whatever
		* this is powerful, because now we are writing IP version-agnostic code

	* addrinfo struct is a linked list, where ai_next points at the next element of type addrinfo
	* the ai_addr field in the struct addrinfo is a pointer to a struct sockaddr - where all of the details of the IP address structure are stored
	* we will not usually need to write to these structures; a call to ** getaddrinfo() ** will fill out the addrinfo struct; but the details are improtant

Struct sockaddr holds socket address information for many types of sockets:

Let's first examine IP4V structures::
	* struct sockaddr::

		struct sockaddr {
			unsigned short 	sa_family; 	 // address family, AF_INET, AF_INET6, AF_UNSPEC
			char 			sa_data[14]; // 14 bytes of protocol address
		} // -> short (2 bytes) + array of 14 chars (14 bytes) = 16 bytes

		
	* sa_family - could be a variety of things, but it will be AFINET (IPv4) or AF_INET6(IPv6) for everything we do in this document
	* sa_data 	- contains a destination address and port number for the socket. This is rather unwieldy since you don't want to tediously pack the address in the sa_data by hand
	* to deal with struct sockaddr, programmers created a parallel structure::

		struct sockaddr_in ("in" for internet") to be used with IPv4

	* a pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vise-versa
	* so even though ** connect() ** wants a struct sockaddr*, we can still us a struct sockaddr_in and cast it in the last minute::

		// (IPv4 only - see struct sockaddr_in6 for IPv6)

		struct sockaddr_in {
			short int 			in_family; 	 // Address family, AF_INET
			unsigned short int  sin_port; 	 // port number
			struct in_addr		sin_addr; 	 // internet address
			unsigned char 		sin_zero[8]; // same size as struct sockaddr
		} // -> short int (2 bytes) + short int (2 bytes) + in_addr(4 bytes - 32 bit address) + array of 8 chars (8 bytes) = 16 bytes

	* struct sockaddr_in makes it easy to reference elements of the struct sockaddr, because struct sockaddr packs all of it into char sa_data[14] - why not just use sockaddr_in then, instead of confusing a hack out of me
		* sin_zero:

			* is used to pad the sockaddr_in structure to the length of a struct sockaddr
			* should be set to all zeros with the function ** memset() **. 

		* sin_family corresponds to sa_family in a struct sockaddr and should be set to AF_INET
		* sin_port must be in Network Byte Order - ** htons() **

	* let's dig deeper into ** sin_addr ** field of struct in_addr type - one of the scariest unions of all time::

		// (IPv4 only - see struct in6_addr for IPv6)
		// internet address (a structure for historical reasons)
		struct in_addr {
			uint32_t s_addr; // that's a 32-bit int (4 bytes)
		}

		* very nice, so if we declared ** struct sockaddr_in ina **, then ** ina.sin_addr.s_addr ** references 4-byte IP address (in Network Byte Order)
		* uint32_t used to be a union, but not anymore; however, if your system still uses that union, #defines will ensure that the 4-byte IP address in (NBO) is referenced
	

Let's examine IPv6 structs:
	* struct sockaddr_in6::

		// (IPv6 only - see struct sockaddr_in and struct in_addr for IPv4)
		struct sockaddr_in6 {
			u_int16_t 		sin6_family;	// address family, AF_INET6
			u_int16_t 		sin6_port; 		// port number, Network Byte Order
			u_int32_t		sin6_flowinfo; 	// IPv6 flow information
			struct in6_addr sin6_addr; 		// IPv6 address
			u_init32_t		sin6_scope_id; 	// Scope ID
		};

		struct in6_addr {
			unsigned char s6_addr[16]; 	// IPv6 address - 128 bits
		}

	* Note that IPv6 has an IPv6 address and a port number, just like IPv4 has an IPv4 address and a port number
	* Also note that we will not going to talk about the IPv6 flow information or Scope ID fields for now

Handling both IPv4 and IPv6:
	* struct sockaddr_storage is designed to be large enought to hold both IPv4 and IPv6 structures
		* the reasoning behind is that sometimes we don't know in advance if packets will fill out struct sockaddr with an IPv4 or IPv6 address
		* so we pass in this parallel structure, very similar to struct sockaddr except larger and then cast it to the type we need::

			struct sockaddr_storage {
				sa_family_t ss_family; 		// address family
				// all of this is padding, implementation specific
				char 		__ss_pad1[_SS_PAD1SIZE];
				int64_t		__ss_align;
				char 		__ss_pad2[_SS_PAD2SIZE];
			}

	* What's important is that you can see the address family in the ss_family field—check this to see if it's AF_INET or AF_INET6 (for IPv4 or IPv6). Then you can cast it to a struct sockaddr_in or struct sockaddr_in6 if you wanna.


IP Addresses, Part Deux
^^^^^^^^^^^^^^^^^^^^^^^
There are many functions that help to manipulate IP addresses. No need to figure them out by hand and stuff into long <<

Task 1 - stor an IP array of chars into struct sockaddr_in ina:
	* we have a struct sockaddr_in ina into which we want to stor IP address "10.12.110.57" or "2001:db8:63b3:1::3490"
	* we want to use inet_pton function - converts IP address in numbers-and-dots notation into either a struct in_addr or struct in6_addr, depending on whether we specify AF_INET or AF_INET6
	* "pton" stands for "presentation to networ"
	* here is how to perform the string IP address conversion to its binary representations::

		struct sockaddr_in  sa; 	// IPv4
		struct sockaddr_in6 sa6; 	// IPv6

		inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); 			// IPv4
		inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa.sin6_addr));  // IPv6

		// note: the old way of doing things used a function called inet_addr() or another function called inet_aton(); 
		// these are now obsolete and don't work with IPv6

		// Now, the above code snippet isn't very robust because there is no error checking. 
		// See, inet_pton() returns -1 on error, or 0 if the address is messed up. 
		// So check to make sure the result is greater than 0 before using!

	* here is how to convert struct in_addr (binary represenation) to numbers-and-dots notation or struct in6_addr to hex-and-colons notations::

		// IPv4:

		char ip4[INET_ADDRSTRLEN]; 	// space to hold the IPv4 string
		struct sockaddr_in sa;		// pretend this is loaded with something

		inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
		printf("The IPv4 address is: %s\n", ip4);

		// IPv6:

		char ip6[INET6_ADDRSTRLEN];  // space to hold the IPv6 string
		struct sockaddr_in6 sa6; 	 // pretend this is loaded with something

		inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
		printf("The IPv6 address is: %s\n", ip6);

		// note: the historical function to do this conversion was called inet_ntoa(). 
		// It's also obsolete and won't work with IPv6

		// When you call it, you'll pass the address type (IPv4 or IPv6), the address, a pointer to a string to hold the result, 
		// and the maximum length of that string. (Two macros conveniently hold the size of the string you'll need to hold the 
		// largest IPv4 or IPv6 address: INET_ADDRSTRLEN and INET6_ADDRSTRLEN.)

	* Lastly, these functions only work with numeric IP addresses—they won't do any nameserver DNS lookup on a hostname, like "www.example.com". You will use getaddrinfo() to do that, as you'll see later on


Private (Or Disconnected) Networks
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Lots of places have a firewall that hides the network from the rest of the world for their own protection. And often times, the firewall translates "internal" IP addresses to "external" (that everyone else in the world knows) IP addresses using a process called Network Address Translation, or NAT.

For now we don't even have to worry about NAT, since it's done for you transparently. But I wanted to talk about the network behind the firewall in case you started getting confused by the network numbers you were seeing.

For instance, I have a firewall at home. I have two static IPv4 addresses allocated to me by the DSL company, and yet I have seven computers on the network. How is this possible? Two computers can't share the same IP address, or else the data wouldn't know which one to go to!

The answer is: they don't share the same IP addresses. They are on a private network with 24 million IP addresses allocated to it. They are all just for me. Well, all for me as far as anyone else is concerned. Here's what's happening:
	* If I log into a remote computer, it tells me I'm logged in from 192.0.2.33 which is the public IP address my ISP has provided to me. 
	* But if I ask my local computer what its IP address is, it says 10.0.0.5. Who is translating the IP address from one to the other? 
	* That's right, the firewall! It's doing NAT!
	* 10.x.x.x is one of a few reserved networks that are only to be used either on fully disconnected networks, or on networks that are behind firewalls. 
	* The details of which private network numbers are available for you to use are outlined in RFC 1918, but some common ones you'll see are 10.x.x.x and 192.168.x.x, where x is 0-255, generally. 
	* Less common is 172.y.x.x, where y goes between 16 and 31.
	* Networks behind a NATing firewall don't need to be on one of these reserved networks, but they commonly are.
	* IPv6 has private networks, too, in a sense. They'll start with fdxx: (or maybe in the future fcXX:), as per RFC 4193. NAT and IPv6 don't generally mix, however (unless you're doing the IPv6 to IPv4 gateway thing which is beyond the scope of this document)—in theory you'll have so many addresses at your disposal that you won't need to use NAT any longer. But if you want to allocate addresses for yourself on a network that won't route outside, this is how to do it.


Jumping from IPv4 to IPv6
^^^^^^^^^^^^^^^^^^^^^^^^^
	* First of all, try to use getaddrinfo() to get all the struct sockaddr info, instead of packing the structures by hand. This will keep you IP version-agnostic, and will eliminate many of the subsequent steps.
	* Any place that you find you're hard-coding anything related to the IP version, try to wrap up in a helper function.
	* Change AF_INET to AF_INET6.
	* Change PF_INET to PF_INET6.
	* Change INADDR_ANY assignments to in6addr_any assignments, which are slightly different::

		struct sockaddr_in sa;
		struct sockaddr_in6 sa6;

		sa.sin_addr.s_addr = INADDR_ANY;  // use my IPv4 address
		sa6.sin6_addr = in6addr_any; // use my IPv6 address

	* Also, the value IN6ADDR_ANY_INIT can be used as an initializer when the struct in6_addr is declared, like so::

		struct in6_addr ia6 = IN6ADDR_ANY_INIT;
	
	* Instead of struct sockaddr_in use struct sockaddr_in6, being sure to add "6" to the fields as appropriate (see structs, above). There is no sin6_zero field.
	* Instead of struct in_addr use struct in6_addr, being sure to add "6" to the fields as appropriate (see structs, above).
	* Instead of inet_aton() or inet_addr(), use inet_pton().
	* Instead of inet_ntoa(), use inet_ntop().
	* Instead of gethostbyname(), use the superior getaddrinfo().
	* Instead of gethostbyaddr(), use the superior getnameinfo() (although gethostbyaddr() can still work with IPv6).
	* INADDR_BROADCAST no longer works. Use IPv6 multicast instead.


System Calls or Bust
^^^^^^^^^^^^^^^^^^^^
Let's examine system calls (library calls) that allow us to access the network functionality on Unix. 

getaddrinfo() - prepare to launch:
	* helps out to set up structs used later
	* used to use gethostbyname() to do DNS lookups and then load that info into struct sockaddr_in by hand, which was wasteful and not addoptable to both IPv4/IPv6 protocols
	* getaddrinfo() does both DNS and service name lookups, and fills out the structs we need::

		#include <sys/types.h>
		#include <sys/socket.h>
		#include <netdb.h>

		int getaddrinfo(const char *node,				// e.g. "www.example.com" or IP
						const char *service,			// e.g. "http" or port number
						const struct addrinfo *hints,	// fill it up before passing, so that res receives everything else
						struct addrinfo **res)			// res will contain results received

		// status = getaddrinfo(....)					// -1 is error, 0 is confused, 1 is good		

	* Give this function three input parameters and it gives back a pointer to linked-list res of type addrinfo
	* the "node" parameter is the host name or IP address
	* Next is the parameter service, which can be a port number, like "80", or the name of a particular service (found in The IANA Port List or the /etc/services file on your Unix machine) like "http" or "ftp" or "telnet" or "smtp" or whatever
	* the hints parameter points to a struct addrinfo that you've already filled out with relevant information
	* let's setup structures that will be used when a server is listening on my host's (machine's) IP address and port 3490::

		int status;
		struct addrinfo hints;
		struct addrinfo *servinfo;	// will point to the results

		memset(&hints, 0, sizeof hints); 	// make sure the struct is empty and filled with 0s
		hints.ai_family = AF_UNSPEC; 		// don't care IPv4 or IPv6
		hints.ai_socktype = SOCK_STREAM;	// TCP stream sockets
		hints.ai_flags = AI_PASSIVE;		// fill in my IP for me

		if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo) != 0)) {
			fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
			exit(1);
		}

		// servinfo now points to a linked list of 1 or more struct addrinfos
		// ... do everything until we don't need servinfo anymore...

		freeaddrinfo(servinfo); 			// free the linked-list

	* let's setup structures used when a client wants to connect to a particular server - "www.example.net" port 3490::

		int status;
		struct addrinfo hints;
		struct addrinfo *servinfo; 			// will point to the results

		memset(&hints, 0, sizeof hints); 	// make sure the struct is empty
		hints.ai_family = AF_UNSPEC; 		/ don't care IPv4 or IPv6
		hints.ai_socktype = SOCK_STREAM; 	// TCP stream sockets

		// get ready to connect
		status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

		// servinfo now points to a linked list of 1 or more struct addrinfos

		// etc.

	* let's examine the linked list struct servinfo in more details: check showip.c example:
		* the code calls getaddrinfo() on whatever you pass on the command line
		* argv[1] fills out the linked list pointed to by res
		* then we can iterate over the list and print out the info::

			$ showip www.example.net
			IP addresses for www.example.net:

			  IPv4: 192.0.2.88

			$ showip ipv6.example.com
			IP addresses for ipv6.example.com:

			  IPv4: 192.0.2.101
			  IPv6: 2001:db8:8c00:22::171

		* Now that we have that under control, we'll use the results we get from getaddrinfo() to pass to other socket functions and, at long last, get our network connection established


socket() - Get the File Descriptor
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Here is the socket() system call::
	#include <sys/types.h>
	#include <sys/socket.h>

	int socket(int domain, int type, int protocol);

The arguments:
	* they allow you to say what kind of socket you want (IPv4/IPv6, stream/datagram, TCP/UDP)
	* these values used be hardcoded:
		* domain   - PF_INET/PF_INET6
		* type     - SOCK_STREAM/SOCK_DGRAM
		* protocol - 0 to choose proper protocol for the give type or call getprotobyname() to look up protocol (tcp/udp)
		* a story::

			This PF_INET thing is a close relative of the AF_INET that you can use when initializing 
			the sin_family field in your struct sockaddr_in. In fact, they're so closely related that 
			they actually have the same value, and many programmers will call socket() and pass AF_INET 
			as the first argument instead of PF_INET. Now, get some milk and cookies, because it's times 
			for a story.

			Once upon a time, a long time ago, it was thought that maybe an address family (what the "AF" in "AF_INET" stands for) 
			might support several protocols that were referred to by their protocol family (what the "PF" in "PF_INET" stands for).
			That didn't happen. And they all lived happily ever after, The End. So the most correct thing to do is to use AF_INET 
			in your struct sockaddr_in and PF_INET in your call to socket()

		* however, use the values from the results of the call to getaddrinfo(), and feed them into socket()::

			int s;
			struct addrinfo hints, *res;

			// do the lookup + pretend we already filled out the "hints" struct 
				(with hints.ai_family = AF_UNSPECT, hints.ai_socktype = SOCK_STREAM)
			getaddrinfo("www.example.com", "http", &hints, &res); // don't forget error checking

			s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

			socket() simply returns to you a socket descriptor that you can use in later system calls, or -1 on error. 
			The global variable errno is set to the error's value (see the errno man page for more details, 
			and a quick note on using errno in multithreaded programs.)

		* Important technical detail:
			* need to have both hints and pointer res to type addrinfo 
			* so that to copy the result of getaddrinfo into it

bind() - what port am I on?
^^^^^^^^^^^^^^^^^^^^^^^^^^^
Once you have a socket, you might have to associate that socket with a port on your local machine. 
This is commonly done if you're going to listen() for incoming connections on a specific port—multiplayer 
network games do this when they tell you to "connect to 192.168.5.10 port 3490". The port number is used 
by the kernel to match an incoming packet to a certain process's socket descriptor. Clients mostly connect(only)

Here is bind() system call::
	
	#include <sys/types.h>
	#include <sys/socket.h>

	int bind(int sockfd, struct sockaddr *my_addr, int addrlen);

	// sockfd  - socket file descriptor returned by socket()
	// my_addr - a pointer to a struct sockaddr that contains information about our address - port and IP
	// addrlen - the length in bytes of that address

Let's bind the socket to the port 3490 on the host the program is running on::

	struct addrinfo hints, *res;
	int sockfd;

	// first, load up address structs with getaddrinfo():
	memset(&hints, 0, sizeof hints); // free hints
	hints.ai_family = AF_UNSPEC;     // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;	 // use my IP

	getaddrinfo(NULL, "3490", &hints, &res); // domain/IP(if not my host's), port, address to addrinfo struct with some info, 
											 // address of a pointer to results
	// make a socket: 
	socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// bind it to the port we passed in to getaddrinfo();
	bind(sockfd, res->ai_addr, res->ai_addrlen);

	// By using the AI_PASSIVE flag, I'm telling the program to bind to the IP of the host it's running on. 
	// If you want to bind to a specific local IP address, drop the AI_PASSIVE and put an IP address in for 
	// the first argument to getaddrinfo().

	// bind() also returns -1 on error and sets errno to the error's value.

Old way to bind::
	
		// !!! THIS IS THE OLD WAY !!!

		int sockfd;
		struct sockaddr_in my_addr;

		sockfd = socket(PF_INET, SOCK_STREAM, 0);

		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(MYPORT);     					// short, network byte order
		my_addr.sin_addr.s_addr = inet_addr("10.12.110.57");    // could use INADDR_ANY for my IP
		memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);

		bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);

	* In the above code, you could also assign INADDR_ANY to the s_addr field if you wanted to bind to your local IP address (like the AI_PASSIVE flag, above.) 
	* The IPv6 version of INADDR_ANY is a global variable in6addr_any that is assigned into the sin6_addr field of your struct sockaddr_in6. 
	* There is also a macro IN6ADDR_ANY_INIT that you can use in a variable initializer

Another thing to watch out for when calling bind(): don't go underboard with your port numbers. 
All ports below 1024 are RESERVED (unless you're the superuser)! You can have any port number above that, 
right up to 65535 (provided they aren't already being used by another program.)

Sometimes, you might notice, you try to rerun a server and bind() fails, claiming "Address already in use." 
What does that mean? Well, a little bit of a socket that was connected is still hanging around in the kernel, 
and it's hogging the port. You can either wait for it to clear (a minute or so), or add code to your program 
allowing it to reuse the port, like this::

	int yes=1;
	//char yes='1'; // Solaris people use this

	// lose the pesky "Address already in use" error message
	if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
	    perror("setsockopt");
	    exit(1);
	} 

One small extra final note about bind(): there are times when you won't absolutely have to call it. 
If you are connect()ing to a remote machine and you don't care what your local port is (as is the case 
with telnet where you only care about the remote port), you can simply call connect(), it'll check to see 
if the socket is unbound, and will bind() it to an unused local port if necessary.


connect() - hey!
^^^^^^^^^^^^^^^^
Let's connect to "10.12.110.57" on port "23" (telnet)::
	
	#include <sys/types.h>
	#include <sys/socket.h>

	int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

	// sockfd - socket descriptor returned by the socket() system call
	// serv_addr - is pointer to a struct of type sockaddr, which contains the destination port/IP
	// addrlen - length in bytes of the server address structure

	// all of the above info comes from getaddrinfo()

Let's make a socket connection to "www.example.net" on port 3490::

	struct addrinfo hints, *res;
	int sockfd;

	// first, load up address structs with getaddrinfo()
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 	 // either IPv4/IPv6
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("www.example.com", "3490", &hints, &res); // get info about the remote server I want to 
														  // connect to on remote port 3490
	// make a socket
	socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// connect
	connect(sockfd, res->ai_addr, res->ai_addrlen);

	
	// Be sure to check the return value from connect()—it'll return -1 on error and set the variable errno.
	
	// Also, notice that we didn't call bind(). Basically, we don't care about our local port number; 
	// we only care where we're going (the remote port). The kernel will choose a local port for us, 
	// and the site we connect to will automatically get this information from us. No worries.

	
listen() - will somebody call me please?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
What if we don't really care to connect to remote hosts, but we only want to wait for incoming connections
and hanlde them in some way (web servers). The process is accomplished in two steps: listen() and accept()

Let's examine listen()::
	
	int listen(int sockfd, int backlog);

	// sockfd - socket file descriptor
	// backlog - number of connections allowed on the incoming queue
		// incoming connections are going to wait in a queue until we accept() them
		// there is a limit of ~20 and we could get away with 5-10
	// listen() - returns -1 and sets global errno on error

System calls summary::
	
	server: getaddrinfo() -> socket() -> bind() -> listen() -> accept()

				vs

	client: getaddrinfo() -> socket() -> connect()


accept() - thank you for calling port 3490
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
How does it work?
	* Someone will try to connect() to your machine on a port that you are listen()ing on. 
	* Their connection will be queued up waiting to be accept()ed. 
	* You call accept() and you tell it to get the pending connection. 
	* It'll return to you a brand new socket file descriptor to use for this single connection! 
	* The original socket is still listening for more new connections, and the newly created one is finally ready to send() and recv().

Let's examine accept()::

	#include <sys/types.h>
	#include <sys/socket.h>

	int accept(int sockfd, struct sockaddr * addr, socket_t * addrlen);

	// socketfd - is the listen()ing socket descriptor
	// addr - a pointer to alocal struct sockaddr_storage; this is where the information about 
	// 		  the incoming connection will go and with it you can determine which host is calling
	// 	      you from which port
	// addrlen - local integer variable that should be set to sizeof(struct sockaddr_storage)
	// 		     before its address is passed to accept(); accept() will not put more that that many bytes
	//	 		 into addr; if it puts fewer, it will change the value of addrlen to reflect that
	// accept() - return -1 and sets global errno if an error occurs


Let's examine accept() in more detials::

	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <neinet/in.h>

	#define MYPORT "3490" 	// the port users will be connecting to
	#define BACKLOG 10		// how many pending connections queue will hold

	int main(void) {
		struct sockaddr_storage their_addr; // whoever is connecting
		socklen_t addr_size;
		struct addrinfo hints, *res;
		int sockfd, new_fd;

		// don't forget error checking for the calls

		// first, load up address structs with getaddrinfo():
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC; 	// use IPv4 or IPv6
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE; 	// use my IP

		getaddrinfo(NULL, MYPORT, &hints, &res);

		// make a socket -> bind to it -> listen to it
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		bind(sockfd, res->ai_addr, res->ai_addrlen);
		listen(sockfd, BACKLOG);

		// now accept an incoming connection
		addr_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size); // accept what's comming; get info

		// ready to communicat of socke descriptor new_fd
	}

	// Note that we will use the socket descriptor new_fd for all send() and recv() calls. 
	// If you're only getting one single connection ever, you can close() the listening sockfd 
	// in order to prevent more incoming connections on the same port.


send() and recv() - talk to me
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
These two functions are for communicating over stream sockets or connected datagram sockets. 
If you want to use regular unconnected datagram sockets, you'll need to see the section on sendto() and recvfrom(), below.

Here is the send() system call::
	
	int send(int sockfd, const void * msg, int len, int flags);

	// sockfd - socket file descriptor we want to send data to 
	//          (remember: one is from socket() and the other is from accept() system call)
	// msg - a pointer to the data you want to send
	// len - the length of *msg in bytes (notice dereferencing)
	// flag - 0

Simple implementation::

	char * msg = "Hey there";
	int len, bytes_sent;

	len = strlen(msg);
	bytes_sent = send(sockfd, msg, len, 0); // returns # of bytes sent out - could be less than asked - boooo

	// send() returns the number of bytes actually sent out—this might be less than the number you told it to send
	// See, sometimes you tell it to send a whole gob of data and it just can't handle it. 
	// It'll fire off as much of the data as it can, and trust you to send the rest later. 
	// Remember, if the value returned by send() doesn't match the value in len, it's up to you to send the rest of the string. 
	// The good news is this: if the packet is small (less than 1K or so) it will probably manage 
	// to send the whole thing all in one go. 

	// Again, -1 is returned on error, and errno is set to the error number.

Here is recv() system call::

	int recv(int sockfd, void * buf, int len, int flags);

	// sockfd is the socket descriptor to read from
	// buf is the buffer to read the information into
	// len is the maximum length of the buffer
	// flags can again be set to 0. (See the recv() man page for flag information.)

	// recv() returns the number of bytes actually read into the buffer, 
	// or -1 on error (with errno set, accordingly.)

	// recv() can return 0 -> the remote side has closed the connection on you! 
	// A return value of 0 is recv()'s way of letting you know this has occurred.


sendto() and recvfrom() - talk to me, DGRAM
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
I will return to this, my brain is already about to explode. 


close() and shutdown() - that's enough!
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
After send()ing and recv()ing data to close the connection on your socket descriptor 
user regular Unix file descriptor close() function::

	close(sockfd);


getpeername() — Who are you?
^^^^^^^^^^^^^^^^^^^^^^^^^^^
The function getpeername() will tell you who is at the other end of a connected stream socket::

	#include <sys/socket.h>

	int getpeername(int sockfd, struct sockaddr * addr, int * addrlen);

	// sockfd - the descriptor of the connected stream socket
	// addr - a pointer to a struct sockaddr (or a struct sockaddr_in) that will hold the information 
	          about the other side of the connection
	// addrlen - a pointer to an int, that should be initialized to sizeof *addr or sizeof(struct sockaddr).
	// The function returns -1 on error and sets errno accordingly.
	// Once you have their address, you can use:
	// 	- inet_ntop(), getnameinfo(), or gethostbyaddr() to print or get more information 

gethostname() — Who am I?
^^^^^^^^^^^^^^^^^^^^^^^^^^^
It returns the name of the computer that your program is running on. The name can then be used by 
gethostbyname(), below, to determine the IP address of your local machine::
	
	#include <inistd.h>

	int gethostname(char * hostname, size_t size);

	// hostname - a pointer to an array of chars that will contain the hostname upon the function's return
	// size - is the length in bytes of the hostname array
	// The function returns 0 on successful completion, and -1 on error, setting errno as usual.


Client-Server Implementation
^^^^^^^^^^^^^^^^^^^^^^^^^^^
Just about everything on the network deals with client processes talking to server processes and vice-versa. 
Take telnet, for instance. When you connect to a remote host on port 23 with telnet (the client), 
a program on that host (called telnetd, the server) springs to life. It handles the incoming telnet connection, 
sets you up with a login prompt, etc.

Note that the client-server pair can speak SOCK_STREAM, SOCK_DGRAM, or anything else (as long as they're speaking the same thing.) 
Some good examples of client-server pairs are telnet/telnetd, ftp/ftpd, or Firefox/Apache. 
Every time you use ftp, there's a remote program, ftpd, that serves you.

Often, there will only be one server on a machine, and that server will handle multiple clients using fork(). 
The basic routine is: server will wait for a connection, accept() it, and fork() a child process to handle it. 
This is what our sample server does in the next section.

My project is to create a multi-threaded process, but I can still borrow some concepts from Beej!