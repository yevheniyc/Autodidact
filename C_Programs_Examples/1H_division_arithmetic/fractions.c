/*
	fractions.c - Yevheniy Chuba - 01/25/2016
	Perform division, reporting the result as a mixed fraction
*/

#include <stdio.h>

main() {
	int divisor, dividend, quotient, remainder;
	int valid_input = 0;
	char inbuf[133];

	// get the dividend/divisor
	while (valid_input < 1) {
		printf("Enter the dividend: ");
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", &dividend);
	}

	valid_input = 0; // reset the flag

	while (valid_input < 1) {
		printf("Enter the divisor: ");
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", &divisor);

		// check for an attempt to divide by zero
		if (divisor == 0) {
			printf("Division by zero is not allowed\n");
			valid_input = 0; // resent to ask for the divisor again
		}
	}

	// perform the division
	quotient = dividend / divisor; // integer division yields only the quotient
	remainder = dividend % divisor; // yields the remainder

	// print the results
	printf("%d / %d = %d and %d/%d\n",
		    dividend, divisor, quotient, remainder, divisor);
}