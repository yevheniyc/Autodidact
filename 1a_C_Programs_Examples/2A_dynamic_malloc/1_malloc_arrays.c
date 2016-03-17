/*
	1_malloc_arrays.c - Yevheniy Chuba - 01/30/2016
	Demo of a function using a pointer to a dynamically allocated array
*/

#include <stdio.h>
#include <stdlib.h>

// function prototypes
double average_numbers(int *array, int n);

// main function
main() {
	int *table, i, n;

	printf("Average some integer numbers\n");
	printf("How many integers? ");
	scanf("%d", &n);

	/*
		malloc allocates bytes - to get enough space for storing data
		once must multiply number of items by the size of said item,
		in this case n * sizeof(int).

		Use a cast to properly set the type for the output of malloc
		from "pointer to void" to "pointer to int", than check to make
		sure that you obtained the requested memory.
	*/

	table = (int *) malloc(n * sizeof(int)); // allocate enough memory for n number of integers 
											 // to enter into the pointer "table", which is now the same as an array; 
	// check if the requested memory has been provided
	if (table == NULL) {
		fprintf(stderr, "Insufficient memory.\n");
		exit(1); // exit the program on fatal error - return non-zero value on failure
	}

	/*
		table now points to the first element in the dynamically
		allocated integer array.
	*/

	for (i = 0; i < n; i++) {
		printf("Enter integer #%d: ", i + 1);
		scanf("%d", &table[i]); // scanf requires the address of an element
	}

	printf("Average is %.12f\n", average_numbers(table, n)); // address of array, which is a pointer already
}

// functions

/*
	average_numbers - returns the average of a list of integer elements.
		input: address of array, size of array
		output: average (of type double) of the elements in the array
*/

double average_numbers(int *array, int array_size) {
	double sum;
	int i;
	int* p;
	p = array;

	// Use one of the bellow examples to sum items inside an array
	for (i = 0; i < array_size; i++)
		sum += (double) *p++; // derefference the pointer to reach the ith value in the array; and increment the pointer

	// or nicely with while and pointer/array arithmetics
	// while (p < array + array_size) // while pointer is not pointing to the end of array
	// 	sum += (double) *p++;
	
	return sum / (double) array_size;
}