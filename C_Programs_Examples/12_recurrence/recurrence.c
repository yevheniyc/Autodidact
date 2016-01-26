/*
	recurrence.c - Yevheniy Chuba - 01/26/2016
	demonstration program for a solved recurrence relation.

	compile: gcc -o recurrence recurrence.c -lm -> ("-lm" for math functions)

	Find recurrence relation for the number of ternary strings
	that do not contain two consecutive zeros.

	Recurrence relation: a[n] = 2a[n-1] + 2a[n-2], n >= 2
	Initial conditions:  a[0] = 1, a[1] = 3
*/

#include <stdio.h>
#include <math.h>
#include "iolib.h"

main() {
	double root1, root2, alpha1, alpha2, result;
	int n;

	// set up the constants
	root1 = 1.0 + sqrt(3.0);
	root2 = 1.0 - sqrt(3.0);

	alpha1 = ( 2.0 + sqrt(3.0) ) / ( 2 * sqrt(3.0) );
	alpha2 = ( sqrt(3.0) - 2.0 ) / ( 2 * sqrt(3.0) );

	// get the value of n
	n = get_bounded_integer(0, INT_MAX);

	// calculate the result and display answer
	result = alpha1 * pow(root1, (double) n) + alpha2 * pow(root2, (double) n);
	printf("f(%d) = %f\n", n, result);
}