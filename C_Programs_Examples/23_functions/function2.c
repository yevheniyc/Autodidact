/*
	function2.c - Yevheniy Chuba - 01/27/2016
	Another infamous example of calculating the factorial
	of an integer.
*/

#include <stdio.h>

// function prototypes
int factorial(int num);

// main
main() {
	int n;

	printf("Enter an integer: ");
	scanf("%d", &n);
	printf("%d! = %d\n", n, factorial(n));
}

// functions
int factorial(int num) {
	int i, result = 1;

	for (i = 2; i <= num; i++)
		result *= i;

	return result;
}