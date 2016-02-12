Network Sockets
---------------

The following code is borrowed and analyzed from:
http://beej.us/guide/bgnet/output/html/multipage/theory.html


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
