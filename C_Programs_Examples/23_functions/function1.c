/*
	function1.c - Yevheniy Chuba - 01/27/2016
	Demo of function use
*/

#include <stdio.h>

/*
	function prototypes: this is where all functions are declaread for late use
						 in the program. This is done in order to define the type
						 of what's returned by the functions as well as the number
						 and types of the parameters passed to the function. This
						 allows the compiler to protect the stack from improper
						 parameter passing.
*/

int digit_sum(int n); 	// parameters only require data types, but should include
						// variable name as well for documentation puposes
int get_integer(void);	// "void" is used here to indicate that nothin is being passed

main() {
	int x;

	printf("Digit sum - another exciting program\n");
	printf("   from Furball Enterprises, Inc.\n\n");
	x = get_integer();

	printf("Sum of the digits of %d is %d.\n", x, digit_sum(x));
}

// Functions //
/*
	get_integer() - used to get an integer input from the user.
	This routine will not return until a valid integer is entered
*/	

int get_integer(void) {
	int val;	// declare variables that are local to this function
	int valid_input;
	char inbuf[133];

	while (valid_input < 1) {
		printf("Enter an integer: ");
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", &val);
	}
	return val; // return an integer as the result of the function
}
/*
	digit_sum() - will take an integer passed to it and return the sum
	of all its digits.
*/

int digit_sum(int n) {
	int sum = 0;

	if (n < 0) // assuming that n != INT_MIN, as -INT_MIN = INT_MIN in 2's complement
		n = -n; // convert to positive, as this algorithm requires a positive numver

	while (n !=0 ) {
		sum += n % 10;
		n /=10;
	}

	return sum;
}