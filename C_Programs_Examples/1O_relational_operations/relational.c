/*
	relational.c - Yevheniy Chuba - 01/26/2016
	Perform relation tests for two values
*/

#include <stdio.h>

main() {
	int a, b;

	// get the inputs
	printf("Enter the value for the integer a: ");
	scanf("%d", &a);

	printf("Enter the value for the integer b: ");
	scanf("%d", &b);

	// display comparative results
	printf("a < b = %d\n", a < b); // less then
	printf("a <= b = %d\n", a <= b);
	printf("a > b = %d\n", a > b);
	printf("a >= b = %d\n", a >= b);
	printf("a == b = %d\n", a == b);
	printf("a != b = %d\n", a != b);
	printf("    !a = %d\n", !a);
	printf("    !b = %d\n", !b);
}

/*
	NOTE: non-zero == True, 0 == False
*/