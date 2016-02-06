/*
	1_simple_multi_threading.c - Yevheniy Chuba - 02/05/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-01
	
	Simple thread review:

		Advantages:
			- run concurretly
			- have no separate address space; all use the context of the surrounding process
			- thread switches are very fast because cpu don't have to switch the entire context of the process

		Disadvantages:
			- our reponsibility to start, terminate threads and take care of the access to shared memory

		Two types of threads:
			- usermode threads - run bound to one cpu
			- kernelmode threads - run distributed over all cpus in the system, if you have SMP system


	Simple illustration of multi-threading with pthreads:
		- create threads: pthread_create(address to thread ID of pthread_t type, 
										 n/a, 
										 address to function that returns pointer to function, 
										 parameters to function)
		- exit threads: pthread_exit(0) - terminate the current thread properly 
										  after the body of a funciton is complete
		- wait for threads to terminate and exit main: pthread_join(thread ID)
		- proper thread termination:
			- pthread_exit - wait for the created thread to terminate (i.e. for a function to complete)
			- pthread_detach - detach the threads
		- int usleep(useconds_t useconds) - suspend thread execution for an inteval measured in microseconds
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep on mac

/////// PROTOTYPES //////////////
void * work(void * thr);
/////////////////////////////////


/////// MAIN ////////////////////
int main(int argc, char ** argv) {
	pthread_t t1, t2; // thread IDs
	// create/run threads and pass 0 and 1 to see which one is executed
	pthread_create(&t1, 0, work, (void *) 0);
	pthread_create(&t2, 0, work, (void *) 1);
	// terminate threads after function work is complete
	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return 0;
}
/////////////////////////////////


/////// FUNCTIONS //////////////
void * work(void * thr) {
	int i;
	for (i = 0; i < 10; i++) {
		printf("Executed thread: %d\n", (int) thr); // cast pointer to void to an integer type
		usleep(1000); 			 // sleep for a second
	}

	pthread_exit(0); // wait for the function in thread to complete and exit the thread
}
////////////////////////////////

/*
	NOTE:
		- pthread_create - parameters to the function must be pointers
						 - the function variable should be functions' address, which is "word"
/*

///////// OUTPUT ///////////////
/*
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 1	-> out of order
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 1
	Executed thread: 0
	Executed thread: 0	-> out of order
	Executed thread: 1
/*
///////////////////////////////