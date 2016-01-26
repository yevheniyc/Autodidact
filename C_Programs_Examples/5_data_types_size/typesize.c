/*
	typesize.c - Yevheniy Chuba (adopted from Estell -> C Primer Plus book)
	Prints out type sizes.
	
	Please note that there are many uses for the sizeof() function, since
	data types are machine specific. The ability to obtain the actual size
	allows programs to be portable.

	This program will report different results on different systems!
*/

#include <stdio.h>

main() {
	printf("Type short int has a size of %d bytes.\n", sizeof(short int)); // 2
	printf("Type int has a size of %d bytes.\n", sizeof(int)); 			   // 4
	printf("Type long int has a size of %d bytes.\n", sizeof(long int));   // 8
	printf("Type char has a size of %d bytes.\n", sizeof(char)); 		   // 1
	printf("Type float has a size of %d bytes.\n", sizeof(float)); 		   // 4
	printf("Type double has a size of %d bytes.\n", sizeof(double)); 	   // 8
}