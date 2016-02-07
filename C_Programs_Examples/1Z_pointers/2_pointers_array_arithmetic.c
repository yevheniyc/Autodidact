/*
	2_pointers_array_arithmetic.c - Yevheniy Chuba - 01/30/2016
	Illustration of pointer arithmetic when using arrays
*/

#include <stdio.h>
#define SIZE 6

main() {
	// define variables and types
	int int_array[SIZE], *p_int, i;
	float float_array[SIZE], *p_float;
	char char_array[SIZE], *p_char;
	double double_array[SIZE], *p_double;

	// initalize pointers
	p_int = int_array;
	p_float = float_array;
	p_char = char_array;
	p_double = double_array;

	/* 
		print out hexadecimal address locations of the array elements - including 0
		Remember: to print decimal addresslocations, just cast to (long int)
	*/

	printf("  INDEX\t\t int_array\t float_array\t char_array\t double_array\n");
	for (i = 0; i < SIZE; i++)
		printf("p_type + %d: \t %0X \t %0X \t %0X \t %0X \n", // capital X -> show capital hex letters
				i, p_int + i, p_float + i, p_char + i, p_double + i);

	/*
		again, print out address locations of the array elements
	*/

	printf("\n");
	printf("  INDEX\t\t int_array\t float_array\t char_array\t double_array\n");
	for (i = 0; i < SIZE; i++)
		printf("p_type + %d: \t %0X \t %0X \t %0X \t %0X \n",
				i, p_int + i, p_float + i, p_char + i, p_double + i);

	/*
		Pointer arithmetics:
			- traverse arrays with pointers and simple position indication:
				
				// initialize int_array of size = SIZE and type integers
				int int_array[SIZE];
				// assign values to the array
				int_array = {1, 2, 5, 4}  // can assign more values until reaches size of SIZE:
				int_array[4] = 25		  // {1, 2, 5, 4, 25}
					OR
				int int_array[] = {1, 2, 5, 4} 	// cannot assign any additional values

				// create a pointer to type int
				int *p_int;
				// point the pointer to the first value in the array
				p_int = int_array;
				// traverse array with a pointer
				printf("%0X\n", p_int); 	// show hexadecimal representation of 0th array element's address -> F7FFEC78
				printf("%0X\n", p_int + 1); // show hexadecimal representation of 1st array element's address -> F7FFC7C (4 bytes from previous)
				printf("%0X\n", p_int + 2); // show hexadecimal representation of 2nd array element's address -> F7FFC80 (4 byptes from previous)
				// print pointer value
				printf("%d\n", *p_int or *(p_int + 1)); // show the value the pointer points to (dereferrencing) -> 5
	*/
}

/*
	NOTE:
		Note that on this particular machine, the difference between successive integer array 
		elements is 4 bytes; for floating point elements, 4 bytes; for character array elements, 
		1 byte; and for double-precision floating point elements, 8 bytes. 

		Also note the alignment of the addresses: the data types that are 4 bytes in size 
		have elements that start on addresses that are divisible by 4, and the double type 
		elements start on addresses divisible by 8. This alignment is required for efficient 
		use of the processor as all the bytes for a particular datum can be accessed in 
		a minimum number of memory reads or writes.

*/

///////////// OUTPUT FOR QUICK REFERENCE //////////////////////////
/*
  INDEX		 	int_array	 float_array	 char_array	 double_array
p_type + 0: 	 59239950 	 59239930 	 	592398DA 	 59239900 
p_type + 1: 	 59239954 	 59239934 	 	592398DB 	 59239908 
p_type + 2: 	 59239958 	 59239938 	 	592398DC 	 59239910 
p_type + 3: 	 5923995C 	 5923993C 	 	592398DD 	 59239918 
p_type + 4: 	 59239960 	 59239940 	 	592398DE 	 59239920 
p_type + 5: 	 59239964 	 59239944 	 	592398DF 	 59239928 

  INDEX		 	int_array	 float_array	 char_array	 double_array
p_type + 0: 	 59239950 	 59239930 	 	592398DA 	 59239900 
p_type + 1: 	 59239954 	 59239934 	 	592398DB 	 59239908 
p_type + 2: 	 59239958 	 59239938 	 	592398DC 	 59239910 
p_type + 3: 	 5923995C 	 5923993C 	 	592398DD 	 59239918 
p_type + 4: 	 59239960 	 59239940 	 	592398DE 	 59239920 
p_type + 5: 	 59239964 	 59239944 	 	592398DF 	 59239928 
*/