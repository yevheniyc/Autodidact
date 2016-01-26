/*
	recurrence2.c - Yevheniy Chuba - 01/26/2016
	second demonstration program for a solved recurrence relations.
	Here we are using our arithmetic functions for complex numbers.

	Recurrence relation: a[n] = 2a[n-1] - 2a[n-2], n >= 2
	Initial conditions :  a[0] = 1, a[1] = 2
*/

#include <stdio.h>
#include "iolib.h"
#include "complexlib.h"

main() {
	complex root1, root2, alpha1, alpha2, result;
	complex partial1, partial2;
	int n;

	// set up constants
	root1.real = 1.0;
	root1.imag = 1.0;
	root2.real = 1.0;
	root2.imag = -1.0;

	alpha1.real = 0.5;
	alpha1.imag = -0.5;
	alpha2.real = 0.5;
	alpha2.imag = 0.5;

	// get the value of n with boundries
	n = get_bounded_integer(0, INT_MAX);

	// calculate the result
	partial1 = multiply(alpha1, power(root1, n));
	partial2 = multiply(alpha2, power(root2, n));
	result = add(partial1, partial2);

	// display answer
	printf("f(%d) = %s\n", n, print_complex(result)); 
}