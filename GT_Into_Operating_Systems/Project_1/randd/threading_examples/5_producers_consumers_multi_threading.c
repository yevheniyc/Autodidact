/*
	5_producers_consumers_multi_threading - Yevheniy Chuba - 02/06/2016
	From: http://www.mario-konrad.ch/wiki/doku.php?id=programming:multithreading:tutorial-03

	Implementing Producers-Consumers model with multiple consumers and producers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define POOL_SIZE (3)

///////// GLOBALS //////////////
typedef struct {
	int data[POOL_SIZE];
	int start;
	int end;
	int count;
} pool_t;

int items_to_produce = 20;

pthread_mutex_t mtx;
pthread_mutex_t mtx_item_prod;
pthread_cond_t cond_nonempty;
pthread_cond_t cond_nonfull;
pool_t pool;
////////////////////////////////


///////// PROTOTYPES //////////
void init_pool(pool_t * pool);
void push(pool_t * pool, int value);
int pop(pool_t * pool);
int size(pool_t * pool);
int produce_one(void);
int has_more_to_produce(void);
void * producer(void * ptr);
void * consumer(void * ptr);
///////////////////////////////


///////// MAIN ////////////////
int main(int argc, char ** argv) {
	pthread_t cons0, cons1, cons2;	// three consumers
	pthread_t prod0, prod1; 		// two producers

	// initialize pseudo random generator
	srand((unsigned int)time(0));

	// initialize buffer related things
	init_pool(&pool);

	// initialize mutexes and conditional variables
	pthread_mutex_init(&mtx, 0);
	pthread_cond_init(&cond_nonempty, 0);
	pthread_cond_init(&cond_nonfull, 0);

	// create multiple consumers waiting for values
	pthread_create(&cons0, 0, consumer, (void *)0);
	pthread_create(&cons1, 0, consumer, (void *)1);
	pthread_create(&cons2, 0, consumer, (void *)2);

	// create multiple producers
	pthread_mutex_init(&mtx_item_prod, 0); // not sure why new mutex is needed?
	pthread_create(&prod0, 0, producer, (void *)0);
	pthread_create(&prod1, 0, producer, (void *)1);

	// wait for all threads to terminate
	pthread_join(prod0, 0);
	pthread_join(prod1, 0);

	// clean up buffer realated things
	pthread_cond_destroy(&cond_nonempty);
	pthread_cond_destroy(&cond_nonfull);
	pthread_mutex_destroy(&mtx);

	// consumers get automatically terminated in this example

	return 0;
}
///////////////////////////////


///////// FUNCTIONS ///////////
/* 
	init_pool() - Initialize pool struct of type pool_t with data
*/ 
void init_pool(pool_t * pool) {
	pool->start = 0;
	pool->end = -1;
	pool->count = 0;
}

/*
	push() - append value (value) to the end of the array pool->data[]

*/
void push(pool_t * pool, int value) {
	// lock the mutex
	pthread_mutex_lock(&mtx);
	while (pool->count >= POOL_SIZE)
		// wait for the items to be consumed(popped)
		// if pool->data is full (of size POOL_SIZE)
		pthread_cond_wait(&cond_nonfull, &mtx);
	// go to next and normalize with POOL_SIZE, so
	// to always have indices between/including 0-2
	pool->end = (pool->end + 1) % POOL_SIZE;
	pool->data[pool->end] = value;
	items_to_produce--;
	pool->count++;
	pthread_mutex_unlock(&mtx);
}

/*
	pop() - remove the 0th element in pool->data[] and return it
*/
int pop(pool_t * pool) {
	int value;
	// lock the mutex
	pthread_mutex_lock(&mtx);
	while (pool->count <= 0)
		pthread_cond_wait(&cond_nonempty, &mtx);
	// retrieve the value from pool->data[]
	value = pool->data[pool->start];
	// increment starting point of pool->data[] array
	pool->start = (pool->start + 1) % POOL_SIZE;
	pool->count--; // decrement the count
	pthread_mutex_unlock(&mtx); // lock the mutex

	return value;
}

/*
	size() - return the size of pool->data[] array stored in pool->count
*/
int size(pool_t * pool) {
	int result = 0;
	// lock mutex
	pthread_mutex_lock(&mtx);
	result = pool->count;
	pthread_mutex_unlock(&mtx);

	return result;
}

/*
	produce_one() - decrement items_to_produce global
*/
int produce_one(void) {
	int result = 0;
	pthread_mutex_lock(&mtx_item_prod);
	result = items_to_produce--; // assign and decrement
	pthread_mutex_unlock(&mtx_item_prod);

	return result;
}

/*
	has_more_to_produce() - boolean to check if items_to_produce is 0 or not
	If 0 then false, if > 0 then true is returned.
*/
int has_more_to_produce(void) {
	int result = 0;
	pthread_mutex_lock(&mtx_item_prod);
	result = (items_to_produce > 0);
	pthread_mutex_unlock(&mtx_item_prod);

	return result;
}

/*
	producer() - produce an item (using simple global counter items_to_produce)
			   - push that item into pool->data[] array
			   - pthread_cond_broadcast - broadcast conditional variable sigal that
			     pool->data[] array is not empty and can be consumed.
*/
void * producer(void * ptr) {
	int value;
	while (has_more_to_produce()) { // while items_to_produce is not zero
		value = produce_one(); // returns 10 and decrements items_to_produce--
		printf("producer %d: %d\n", (int)ptr, value); // cast ptr to int
		push(&pool, value);
		pthread_cond_broadcast(&cond_nonempty);
		usleep(500 + (rand() % 500)); // slow down for demonstration
	}

	pthread_exit(0); // terminate the thread
}

/*
	consumer() - pop the item from pool->data
			   - broadcast that the cond_nonfull signal
*/
void * consumer(void * ptr) {
	while (items_to_produce > 0 || size(&pool) > 0) {
		printf("consumer %d: %d\n", (int)ptr, pop(&pool));
		pthread_cond_broadcast(&cond_nonfull);
	}

	pthread_exit(0);
}
///////////////////////////////


///////// OUTPUT //////////////
/*
	Beautiful:
	
		producer 0: 20
		producer 1: 19
		consumer 0: 20
		consumer 0: 19
		producer 0: 16
		producer 1: 15
		consumer 2: 16
		consumer 0: 15
		producer 0: 12
		consumer 1: 12
		producer 1: 10
		consumer 0: 10
		producer 0: 8
		consumer 0: 8
		producer 1: 6
		consumer 2: 6
		producer 0: 4
		consumer 2: 4
		producer 1: 2
		consumer 0: 2
*/
///////////////////////////////