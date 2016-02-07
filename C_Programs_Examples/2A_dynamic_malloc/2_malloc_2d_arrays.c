/*
	2_malloc_2d_arrays.c - Yevheniy Chuba - 01/30/2016
	Example of how to declare and use a two-dimensional array that can be
	passed to a function. For a trully dynamic implementation, replace ROW
	and COL with variables...
*/

#include <stdio.h>
#include <stdlib.h>

#define ROW 10
#define COL 12

// function prototypes
int sum(int *a[]);
void build_array_positions(int **a);

// main
main() {
	int **arrays; // declare an array of pointers - at this point - a pointer to a pointer of type int
	int i, j;

	// (int **) - cast to an array of pointers to type int
	arrays = (int **) malloc(ROW * sizeof(int *));

	// for each pointer dynamically allocate a row having correct number of columns
	for (i = 0; i < ROW; i++)
		arrays[i] = (int *) malloc(COL * sizeof(int)); // point to allocated storage for row

	/* 
		So far we have allocated enough memory to build 2D structure:
			- array -> {pointer-1(first-int), pointer-2(first-int), ...pointer-10(first-int}
				- where first-int is the first element (int) in the array representing the columns
			- pointer-1 -> {int-1(4 bytes), int-2(4 bytes), ...int-12(4 bytes)}
				- int-1 == first-int pointed by pointer-1
			- pointer-2 -> {int-1(4 bytes), int-2(4 bytes), ...int-12(4 bytes)}
				- int-1 == first-int pointed by pointer-2
	*/

	// let's put some values inside the 2D array
	// the value in each position is: row * col
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			arrays[i][j] = i * j; // note that we can access elements normally

	printf("sum = %d\n\n\n", sum(arrays)); // here we pass the array
	
	/*
		Print more information about 2D array positions
	*/
	printf("========= check array positions below: ==========\n\n");
	build_array_positions(arrays);
}

/*
	sum: sums the contents of the array passed to it
*/
int sum(int *a[]) {
	int i, j;
	int sum = 0;

	// loop through each item in the 2D array, sum it and 
	// show what we stored in each position (which is multiplication of i and j)
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			sum += a[i][j];
			printf("%4d", a[i][j]);
		}
		printf("\n");
	}

	return sum;
}

/*
	build_array_positions: array representation with the i and j positions
*/
void build_array_positions(int **a) {
	int i, j;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			printf("%4d,%d", i, j);
		}
		printf("\n");
	}
}

/*
	NOTE: int sum(int *a[]) == int sum(int **a) -> after all a[] == *a

*/