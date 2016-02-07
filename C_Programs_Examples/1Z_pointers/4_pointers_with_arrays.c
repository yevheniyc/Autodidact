/*
	4_pointers_with_arrays.c - Yevheniy Chuba - 01/30/2016
	Demonstration of using pointers with arrays
*/

#include <stdio.h>
#define SIZE 6

// function prototypes
void get_integer(int *array, int index); // passing an array (table) is equivalent to passing an (&address)	
										 // passing starting address and offset
double average_values(int *array, int array_size);

// main function
main() {
	int i, table[SIZE];

	printf("It's the \"Average %d Integer Numbers\" program!!!\n", SIZE);

	for (i = 0; i < SIZE; i++)
		get_integer(table, i);

	printf("Average is %.4f\n", average_values(table, SIZE));
}

// functions
void get_integer(int *array, int index) {
	int valid_input = 0;
	char inbuf[133];

	while (valid_input < 1) {
		printf("Enter integer #%d: ", index + 1);
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", &array[index]); // array is a pointer to the first element in the array
														  // However, I need the address of an element inside array with index ==> index
	}
}

double average_values(int *array, int array_size) {
	double sum = 0.0;
	int i = 0;

	while (i < array_size) {
		// sum += array[i]; 	// Traditional way
		// i++;
			// or
		sum += *(array + i++); 	// Shortcut: derefference(pointer/array arithmetic + increment counter)
			//or
		// sum += *(array + i);	// same as above
		// i++;
	}

	return (sum / (double) array_size);
}

/* IMPORTANT:
	
This program references array elements using two similar methods.  The "traditional"
method, shown in the get_integer function, is array_name[index], where array_name
constitutes a base address and index provides an offset into the array that refers to the
desired element.  To access the element, the system must calculate the address of the
element by taking the base address and adding to it the value of the index times the size
in bytes of an array element.
The other method used is shown in the average_values function. Here we are explicitly showing the array address calculations by using the dereferencing operator on the address formed by adding the integer index to the base address. The act of adding an integer to an address will cause the system to multiply the integer value by the size of the data being reference by the base pointer prior to the addition being performed.
A faster method is to explicitly use pointers; an example would be:
   
double average_values(int *array, int array_size) {
	int *ptr, i;
	ptr = array;
	for (i = 0; i < array_size; i++) {
		sum += *(ptr++);
	}
}

This removes the need for multiplying by the data size, as the incrementing of a pointer 
variable is always by the size of the data being referred to. This concept concerning 
address arithmetic is why we make a distinction between pointers to different types, 
as it allows the system to know what the difference in bytes is between two consecutive elements.

*/