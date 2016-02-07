/*
	7b_insertion_sort.c - Yevheniy Chuba - 02/03/2016
	Implementation of the sort algorithm using callbacks with 
	function pointers.
*/

#include "7a_insertion_sort.h"

/*
	insertion_void:
		- returns - void
		- params - array, a function pointer of type callback (defined in insertion_sort.h)
*/

void insertion_sort(int *array, int n, callback comparison) {
	int i, j, key;
	for (j = 1; j <= n - 1; j++) {
		key = array[j];
		i = j - 1;
		while (i >= 0 && comparison(array[i], key)) {
			array[i + 1] = array[i];
			i = i - 1;
		}
		array[i + 1] = key;
	}
}