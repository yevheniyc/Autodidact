/*
	function0.c - Yevheniy Chuba - 01/27/2016
	Trivial example of using a function in C.
*/

#include <stdio.h>

// ***function prototypes - explained in the next program***
void line_char(char ch, int length);

// main
main() {
	int num;

	printf("Enter a positive integer: ");
	scanf("%d", &num);

	line_char('*', num);
	printf("The value of the integer is no %d.\n", num);
}

// functions - all parameters are passed by value
void line_char(char ch, int length) {
	while (length--)
		putchar(ch); // just stdout the character passed in 'num' of times
	putchar('\n');
}