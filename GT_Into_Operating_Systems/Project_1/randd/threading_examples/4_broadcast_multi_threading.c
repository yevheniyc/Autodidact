/*
	4_circular_buffer_multi_threading.c - Yevheniy Chuba - 02/05/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-03

	Implement a Producer-Consumer model using a circular buffer (queue)
	with more than one space.

	Implemented algorithm:
		1. main creates consumer and producer threads
		2. the consumer thread:
			- checks if num_of_items || pool->count > 0
			- yes, and before printing consumer calls pop(&pool)
		3. inside the pop function:
			- the consumer thread &cons locks the mutex
			- &cons checks if pool->count <= 0
			- it is, so the thread is waiting now for the signal with conditional variable "cond_nonempty"
		4. the producer thread 
			- checks if the num_of_items > 0
			- yes, now producer calls for the push function
		5. inside the push function:
			- &prod thread locks the mutex
			- checks if pool-count > POOL_SIZE
			- no, (pool-count == 0 at this point and pool-end == -1), 
			  then increment the pool-end (from -1 -> 0)
			- now insert into data[pool-end] == data[0] the value of num_of_items == 10
			- increment pool->count to 1
			- unlock the mutex
			- push returns
		6. in producer:
			- num_of_items is decremented to 9
			- nonempty conditional variable is broadcasted
		7. inside the pop function:
			- the &cons thread was waiting for the "nonempty" signal
			- it receives the signal, and the while statement is executed one more time
			  checking if pool->count <= 0
			- no, pool->count is at least 1 now
			- pop proceeds with removing the first (0th) element
			- decrements pool->count
			- unlocks the mutex and ready for the &cons thread to start working again
		8. in consumer:
			- after pop is executed, "nonfull" conditional variable is signaled/broadcasted
			- consumer sleeps
		9. push is executed when the signal is received
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define POOL_SIZE 3

///////// GLOBALS //////////////
typedef struct {
	int data[POOL_SIZE];
	int start;
	int end;
	int count;
} pool_t;

int num_of_items = 10;
pthread_mutex_t mtx;
pthread_cond_t cond_nonempty;
pthread_cond_t cond_nonfull;
pool_t pool;
////////////////////////////////


///////// PROTOTYPES //////////
void init_pool(pool_t * pool);
void push(pool_t * pool, int data);
int pop(pool_t * pool);
void * producer(void * ptr);
void * consumer(void * ptr);
///////////////////////////////


///////// MAIN ////////////////
int main(int argc, char ** argv) {
	pthread_t cons, prod;

	init_pool(&pool);
	
	pthread_mutex_init(&mtx, 0);
	pthread_cond_init(&cond_nonempty, 0);
	pthread_cond_init(&cond_nonfull, 0);

	pthread_create(&cons, 0, consumer, 0);
	pthread_create(&prod, 0, producer, 0);

	pthread_join(prod, 0);
	pthread_join(cons, 0);

	pthread_cond_destroy(&cond_nonempty);
	pthread_cond_destroy(&cond_nonfull);
	pthread_mutex_destroy(&mtx);

	return 0;
}
///////////////////////////////


///////// FUNCTIONS ///////////

/*
	Nice way to initiate and use global stucts
*/
void init_pool(pool_t * pool) {
	pool->start = 0;
	pool->end = -1;
	pool->count = 0;
}

/*
	- push's job is to add items to the end of data array
	  inside the pool_t struct.
	- if it is full, it waits for the &cond_nonfull conditional
	  variable to resume it
*/
void push(pool_t * pool, int data) {
	pthread_mutex_lock(&mtx);
	// if pool->count is larger than POOL_SIZE, then we are full; 
	// wait for the nonfull condition variable and wait with pushing
	while (pool->count >= POOL_SIZE) {
		pthread_cond_wait(&cond_nonfull, &mtx);
	}
	pool->end = (pool->end + 1) % POOL_SIZE; // add 1 to pool->end
	pool->data[pool->end] = data; // add data/number to the end of data array
	pool->count++; // increment the count
	pthread_mutex_unlock(&mtx);
}

/*
	- pop's job is to return and remove the first item from data arraym
*/
int pop(pool_t * pool) {
	int data = 0;
	pthread_mutex_lock(&mtx);
	// if pool-count is <= than 0, than wait until cond_nonempty or
	// the non-empty array signal arrives, than we can pop
	while (pool->count <= 0) {
		pthread_cond_wait(&cond_nonempty, &mtx);
	}
	// once the cond_nonempty signal arrives
	data = pool->data[pool->start]; // data is the first item of the array
	pool->start = (pool->start + 1) % POOL_SIZE; // pool start is now is next element
	pool->count--; // decrement count
	pthread_mutex_unlock(&mtx);

	return data;
}

void * producer(void * ptr) {
	while (num_of_items > 0) {
		push(&pool, num_of_items);
		printf("producer: %d\n", num_of_items);
		num_of_items--;
		// send cond_nonempty conditional variable to everyone who is listening
		pthread_cond_broadcast(&cond_nonempty);
	}

	pthread_exit(0);
}

void * consumer(void * ptr) {
	while (num_of_items > 0 || pool.count > 0) {
		printf("consumer: %d\n", pop(&pool));
		pthread_cond_broadcast(&cond_nonfull);
		usleep(500000);
	}

	pthread_exit(0);
}
///////////////////////////////


///////// OUTPUT //////////////
/*
	producer: 10
	producer: 9
	producer: 8
	consumer: 10
	producer: 7
	consumer: 9
	producer: 6
	consumer: 8
	producer: 5
	consumer: 7
	producer: 4
	consumer: 6
	producer: 3
	consumer: 5
	producer: 2
	consumer: 4
	producer: 1
	consumer: 3
	consumer: 2
	consumer: 1
*/
///////////////////////////////