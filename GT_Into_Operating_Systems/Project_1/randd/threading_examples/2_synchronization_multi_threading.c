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
		- "thread safe" - 
		- in 1_simple_multi_threading.c, the "printf" in the "work" function is not "thread safe", so we need to hanlde it ourselves



*/