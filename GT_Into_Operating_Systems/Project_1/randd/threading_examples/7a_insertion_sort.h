/*
	7a_insertion_sort.h - Yevheniy Chuba - 03/02/2016
	Define new type callback - a pointer to a function that returns an int
	Define insertion_sort that accepts an array to be sorted, and a funciton pointer
	of type callback
*/

typedef int (*callback)(int, int);
void insertion_sort(int *array, int n, callback comparison);