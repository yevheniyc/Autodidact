/*
	math.c - Yevheniy Chuba - 01/26/2016
	Show off different methods of using math functions.
	Note that all floating-point math functions use
	the "double" floating-point type.

	Compile with: gcc -o math math.c -lm
	The -lm will tell gcc to link in the math library when
	forming the executable
*/

#include <stdio.h>
#include <math.h>

main() {
	int		int_value;
	float 	float_value;
	double 	dbl_value;
	char 	inbuf[133];

	/*
		make up some excuse to obtain input from the user
		assuming correct input for purposes of this example;
		not something to do in the real program!
	*/

	printf("\nPlease enter a positive integer: ");
	gets(inbuf);
	sscanf(inbuf, "%d", &int_value);

	printf("Please enter a value between 0 and 1: ");
	gets(inbuf);
	sscanf(inbuf, "%f", &float_value);

	/*
		now do some number crunching - M_PI is a constant
		defined in math.h; 
		To see what constants are available, check out:
		/usr/include/math.h
	*/

	dbl_value = asin( (double) float_value ); // arguments are usually of type double
	dbl_value *= 180.0 / M_PI; 				// converting from radians to degrees

	// print some things out
	printf("\n");
	printf("The square root of %d is %f\n", int_value, sqrt( (double) int_value )); // cast int_value to double
	printf("The arcsine of %.3f is %.1f degrees\n", float_value, dbl_value);
	printf("1.0 divided by 0.0 is %f\n", (1.0 / 0.0));
	printf("-1.0 divided by 0.0 is %f\n", (-1.0 / 0.0));
	printf("0.0 divided by 0.0 is %f\n", (0.0 / 0.0));
}

/*
	Please enter a positive integer: 2
	Please enter a value between 0 and 1: 0.707

	The square root of 2 is 1.414214
	The arcsine of 0.707 is 45.0 degrees
	1.0 divided by 0.0 is inf 			   -> infinity
	-1.0 divided by 0.0 is -inf
	0.0 divided by 0.0 is nan              -> mathematically undefined values
*/