/*
	reverse.c - Yevheniy Chuba - 01/26/2016
	Given integer input, this will print out the 
	reverse of the number (e.g. 321 -> 123)
*/

#include <stdio.h>

main() {
	int num, rev = 0;
	int valid_input = 0;
	char inbuf[133];

	// get an integer from the user - use gets/sscanf in case of error input
	while (valid_input < 1) {
		printf("Enter an integer: ");
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", &num);
	}

	/*
		Reverse the number: 
			- multiply rev by 10 to shift digits to the left,
			- add the units digit from num
			- then integer divide num by 10 to shift digits to the right 
	*/

	while (num != 0) {
		rev *= 10;
		rev += num % 10;
		num /= 10;
	}

	// Print out the results
	printf("Reverse number is %d\n", rev);
}