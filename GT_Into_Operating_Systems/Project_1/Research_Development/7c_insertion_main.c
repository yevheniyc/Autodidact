/*
	3_insertion_main - Yevheniy Chuba - 02/03/2016
	Example Implementation of callback functions for insertion sort algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
#include "7a_insertion_sort.h"


///// PROTOTYPES /////////////////////
int ascending(int a, int b);
int descending(int a, int b);
//////////////////////////////////////

/////// MAIN /////////////////////////
int main(void) {
	int i; // counter
	int choice; // chosen callback
	int array[10] = {22,66,55,11,99,33,44,77,88,0};

	// ask for which callback to execute
	printf("ascending: 1\ndescending: 2\n\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	// check for choices
	switch (choice) {
		// insertion sort is defined in insertion_sort.h
		// and implemented in insertion_sort.c
		case 1: insertion_sort(array, 10, ascending);
				break;
		case 2: insertion_sort(array, 10, descending);
				break;
		default: printf("no such option!\n");
	}

	// print results
	printf("After insertion_sort:\n");
	for (i = 0; i < 10; i++)
		printf("%d\t", array[i]);
	printf("\n");
	return 0;
}
//////////////////////////////////////

/////// FUNCTIONS ///////////////////
int ascending(int a, int b) {
	return a > b;
}

int descending(int a, int b) {
	return a < b;
}
/////////////////////////////////////