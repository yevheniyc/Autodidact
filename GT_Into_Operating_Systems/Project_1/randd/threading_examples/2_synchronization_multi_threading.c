/*
	2_synchronization_multi_threading.c - Yevheniy Chuba - 02/05/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-02

	Synchronization Review:
		- when threads have to share resources concurrently, conflicts arise abut who uses and
		  when the shared resources are used. 
		- synchronization of threads allows us (programmers) control access to resources, which
		  keeps programs stable and reliable - mutual exclusion (mutex) is a technique used to 
		  provide exactly this outcome.
		- assuming that mutial exclusion is garanteed, we still have to address 2 problems:
			-> Deadlock
				- a situation in which all threads are blocked and waiting for a resource
				
				- example: 
					
					The thread X holds the resouce A, the thread Y holds the resource B. 
					Now the thread X wants to take the resource B and get blocked, 
					because thread Y is already using it. How comes, thread Y likes to get 
					the resource A as well and get blocked too, because thread X already holds it. 
					This is a deadlock situation, because neither thread X nor thread Y is able to continue its work.
				
				- to avoid deadlock:

					One possibility to avoid deadlock is to synchronize the threads and let them fetch the resources 
					using timeouts instead of blocking. This means that the thread which likes to get the resource will 
					fail after an amount of time. This means of course a good exception/error handling.
			
			-> Indefinite Suspension:
				- Indefinite suspension can occur if one thread is of lower priority than another and the scheduler 
				  always runs the thread with the highest priority (not all schedulers do so). If the high priority thread 
				  has a big workload, the lower priority thread does not get CPU time any more, for an indefinite amount of time.
				
				- To avoid this, use a good logical design. 
		
		- mutial exclusion (mutex):
			-> a mechanism to encapsulate a part of the programmed called "critical section".
			-> mutexes make sure that only one thread can be inside of a critical secition.
			-> if threare several "critical sections", each guarded by an independent mutext, it is 
			   possible to have a thread X in the section A and another thread Y in the section B.
			-> if a thread is within the critical section guarded by a mutex, it is 
			   called: "The thread is holding the mutex"
			-> as a result of the mutual exclusion mechanism, a programmer should keep the critical
			   section as short and simple as possible. Ignoring this rule will result in the loss of performance.
			-> mainly there are three operations on a mutex, which are used for daily business
				- lock the mutext
				- unlock the mutext
				- trylock which tries to lock the mutext:
					- if the mutext is already locked (another thread is holding the mutex), the
					  trylock function will return with an error code - this is a "non-blocking" function 
					- "blocked" thread - is a thread that is suspended/paused until a currently active thread frees a mutex
					- "non-blocking" function means that thread_1, which is trying to lock a mutex, will not be blocked 
					   by thread_2 which is holding that mutex; thread_1 will only receive an error and can proceed in whichever
					   what a programmer decides
					- "blocking" function will suspend thread_1, until thread_2, the thread currently holding the mutext, is freed!
			-> usually, it is useful to encapsulate the critical section within a separte function, for clarity

	Illustrating multi-threading synchronization with mutaxes:
		- "thread safe" code (http://www.thegeekstuff.com/2012/07/c-thread-safe-and-reentrant/):
			-> As the name suggests, a piece of code is thread safe when more than one thread can execute the same code 
			   without causing synchronization problems. Lets look at the following code snippet:
					...

					char arr[10];
					int index=0;

					int func(char c)
					{
					    int i=0;
					    if(index >= sizeof(arr))
					    {
					        printf("\n No storage\n");
					        return -1;
					    }
					    arr[index] = c;
					    index++;
					    return index;
					}

					...
			-> The above function populates the array ‘arr’ with the character value passed to it as argument and 
			   then updates the ‘index’ variable so that subsequent calls to this function write on the updated index 
			   of the array.
			-> Suppose this function is being used by two threads. Now, lets assume that thread one calls this function 
			   and updates the array index with value ‘c’. Now, before updating the ‘index’ suppose second thread gets 
			   the execution control and it also calls this function. Now since the index was not updated by thread one , 
			   so this thread writes on the same index and hence overwrites the value written by thread one. So we see 
			   that lack of synchronization between the threads was the root cause of this problem.
			-> Now, lets make this function thread safe:
					...
					char arr[10];
					int index=0;

					int func(char c)
					{
					    int i=0;
					    if(index >= sizeof(arr))
					    {
					        printf("\n No storage\n");
					        return -1;
					    }

				       ...
				       Lock a mutex here
				       ...

					    arr[index] = c;
					    index++;

				       ...
				       unlock the mutex here
				       ...
					    
					    return index;
					}
					...
			-> What we did above is that we made the array and index updates an atomic operation using the mutex locks. 
			   Now even if multiple threads are trying to use this function, there would be no synchronization problems 
			   as any thread which acquires the mutex will complete both operations (array and index update) 
			   before any other thread acquires the mutex. So now the above piece of code becomes thread-safe.

		- in 1_simple_multi_threading.c, the "printf" in the "work" function is not "thread safe", 
		  so we need to hanlde it ourselves with mutexes
		  
		- if we had another function we wanted to make "thread safe", we should just define/initiate/destory another mutex:
			-> pthread_mutex_t mtx2
			-> pthread_mutex_init(&mtx2, 0)
			-> pthread_mutex_lock(&mtx2)
			-> pthread_mutex_unlock(&mtx2, 0)
			-> pthread_mutex_destroy(&mtx2)
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // for usleep on mac

////////// GLOBALS //////////
pthread_mutex_t mtx; // define mutex variable
/////////////////////////////


//////// PROTOTYPES //////////
void * work(void * ptr);
void print(int thread, int i);
//////////////////////////////


///////// MAIN ///////////////
int main(int argc, char ** argv) {
	pthread_t t0, t1;

	pthread_mutex_init(&mtx, 0); // init the mutex variable
	pthread_create(&t0, 0, work, (void *)0);
	pthread_create(&t1, 0, work, (void *)1);

	pthread_join(t0, 0);
	pthread_join(t1, 0);

	pthread_mutex_destroy(&mtx); // destroy the mutex
	return 0;
}
//////////////////////////////


///////// FUNCTIONS //////////
void * work(void * ptr) {
	int i;
	for (i = 0; i < 10; i++) {
		print((int)ptr, i);
		usleep(1000);
	}

	pthread_exit(0); // terminate thread
}

void print(int thread, int i) {
	pthread_mutex_lock(&mtx);
	printf("thread %d: %d\n", thread, i); // critical section protected by lock/unlock mutex
	pthread_mutex_unlock(&mtx);
}
//////////////////////////////


////////// OUTPUT ////////////
/* Notice how nicely they are synchronized!
	thread 0: 0
	thread 1: 0
	thread 0: 1
	thread 1: 1
	thread 0: 2
	thread 1: 2
	thread 0: 3
	thread 1: 3
	thread 0: 4
	thread 1: 4
	thread 0: 5
	thread 1: 5
	thread 0: 6
	thread 1: 6
	thread 0: 7
	thread 1: 7
	thread 0: 8
	thread 1: 8
	thread 0: 9
	thread 1: 9
*/
//////////////////////////////