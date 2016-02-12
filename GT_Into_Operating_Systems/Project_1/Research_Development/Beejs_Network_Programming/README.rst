The following code is borrowed and analyzed from:
http://beej.us/guide/bgnet/output/html/multipage/theory.html

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

We could use read() and write() calls to communication thorugh the socket, however, sen() and recv() offer greater control over data transmission.

Types of sockets:
	* DARPA Internet addresses (Internet Sockets)
	* Path names on a local node (Unix Sockets)
	* CCITT X.25 addresses (X.25 Sockets)

Two types of Internet sockets:
	* Stream Sockets -> "SOCK_STREAM"
	* Datagram Sockets -> "SOCK_DGRAM" == "connectionless sockets"

Stream sockets:
	* provide reliable two-way connected communication streams
	* if two items are output into the socket in order '1, 2',
	   they will arrive in that order on the opposite side
	* error-free communication (almost always) 

Who uses stream sockets:
	* telnet www.google.com "GET / HTTP/1.0"
	* web browsers use the HTTP protocol which uses stream sockets
	   to get pages

What stream sockets are using for such a high quality transmission:
	* stream sockets use TCP protocol
	* TCP protocol ensures sequential data arrival


Datagram Sockets:
	* connectionless sockets that use UDP
	* no need to maintain open connection: build a packet, 
	   add IP header with destination information and send
	* Used when dropped packts are not a big deal: tftp, dhcpcd,
	   multiplayer games streaming audio, video converencing


How tftp, dhcpcd and others retain data integrity if packets are lost?
	* tftp and similar programs have their own protocol on top of UDP. 
	   For example, the tftp protocol says that for each packet that gets sent, 
	   the recipient has to send back a packet that says, "I got it!" (an "ACK" packet). 
	   If the sender of the original packet gets no reply in, say, five seconds, 
	   he'll re-transmit the packet until he finally gets an ACK. This acknowledgment 
	   procedure is very important when implementing reliable SOCK_DGRAM applications.
	
	* It's way faster to fire-and-forget than it is to keep track of what has arrived 
	   safely and make sure it's in order and all that. If you're sending chat messages, 
	   TCP is great; if you're sending 40 positional updates per second of the players in the world, 
	   maybe it doesn't matter so much if one or two get dropped, and UDP is a good choice
