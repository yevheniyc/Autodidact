/*
	3_conditional_variables_multi_threading.c - Yevheniy Chuba - 02/05/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-03

	Conditional variables:
		- Condition variables are a very elegant way to do some synchronisation. 
		  A thread can wait for a condition becoming true to continue and 
		  a thread can also make a condition come true. Since a thread is an active part, 
		  it can wait for or make a condition which others are waiting for.

	Producer-Consumer:
		- The following program is a very simple producer-consumer demo. It shows two threads, 
		  one that produces some numbers, the second that consumes them. The demo is simple 
		  because we only use one place as buffer between those threads. So every time the producer 
		  has an item, it has to wait for the consumer to take it. To tell the consumer (sending a signal), that an item is ready we use the condition variable.

		- As soon as the ten items are produced and consumed, the threads will stop and the demo will end.
*/

#include <stdio.h>
#include <pthread.h>

///////// GLOBALS //////////////
pthread_mutex_t mtx; // define mutex variable
pthread_cond_t cond; // define conditional variable

int how_many = 10;
int pool = 0;
////////////////////////////////


///////// PROTOTYPES //////////
void * producer(void * ptr);
void * consumer(void * ptr);
///////////////////////////////


///////// MAIN ////////////////
int main(int argc, char ** argv) {
	pthread_t prod, cons; // two threads: a producer and consumer
	
	pthread_mutex_init(&mtx, 0); // init the mutex variable
	pthread_cond_init(&cond, 0); // init the conditional variable
	// create threads: run consumer first so it can consume as soon as items are ready
	pthread_create(&cons, 0, consumer, 0);
	pthread_create(&prod, 0, producer, 0);
	// terminate threads
	pthread_join(prod, 0);
	pthread_join(cons, 0);
	// destroy conditional and mutex variables
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);

	return 0;
}
///////////////////////////////


///////// FUNCTIONS ///////////
void * producer(void * ptr) {
	while (how_many > 0) {
		pthread_mutex_lock(&mtx);
		printf("producer: %d\n", how_many);
		pool = how_many; // assign a new value to global pool variable
		how_many--;
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cond);
	}

	pthread_exit(0);
}

void * consumer(void * ptr) {
	while (how_many > 0) {
		pthread_mutex_lock(&mtx); // lock the mutex when a thread comes here
		pthread_cond_wait(&cond, &mtx);  // now wait for the signal from producer,
										 // but until then keep the mutex unlocked; there is no timeout!
										 // once the signal is sent, the thread continues into the critical section
		printf("consumer: %d\n", pool);
		pool = 0; // re-assign 0 to the global pool; could've ignored this statement
				  // as pool is overwritten with a new variable in producer
		pthread_mutex_unlock(&mtx);
	}

	pthread_exit(0);
}
///////////////////////////////


///////// OUTPUT //////////////
/*
	The output should be different than what I get:
		producer: 10
		producer: 9
		producer: 8
		producer: 7
		producer: 6
		producer: 5
		producer: 4
		producer: 3
		producer: 2
		producer: 1
		consumer: 1

	The producer/consumer should interchange and decrement.
*/
///////////////////////////////