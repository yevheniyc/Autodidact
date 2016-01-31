/*
	1_pointer_with_function.c - Yevheniy Chuba - 01/30/2016
	Demonstration of using pointers with functions.
*/

#include <stdio.h>

// function prototypes
int digit_sum(int n);
void get_integer(char *prompt, int *value); // must pass addresses as parameters

// main function
main() {
	int x;

	printf("Digit sum - another exciting program\n");
	printf("    from Furball Enterprises, Inc,\n");
	printf("*** The new and improved version! ***\n\n");

	get_integer("Enter and integer: ", &x); // literal string is treated as an address

	/*
		What is happening here, ignoring the string stuff?
		1. Pass the address of x to get_integer(string_address, address_to_type_int) function
		2. Inside get_integer, pointer "value" to type int gets the address of x (address_to_type_int)
		3. The address of x does not hold any value yet, so pointer "value" holds the address of x, but no value
		4. sscanf(input buffer, address) -> pointer "value" already holds the address to value inside the x
		4. So as soon as we enter an int into prompt, the pointer "value" assigns that value at the address it points to,
		   which is the address of x. Now the address of x holds the integer value entered in the prompt.
		5. Below we refer to "x" which is the value we entered in the prompt!
	*/

	printf("Sum of the digits of %d is %d.\n", x, digit_sum(x));
}

// functions

/*
	get_integer() - used to get an integer input from the user.
	This routine will not return until a valid integer is entered.
*/

void get_integer(char *prompt, int *value) {
	// declare variables that are local to this function
	int valid_input = 0;
	char inbuf[133];

	while (valid_input < 1) {
		printf(prompt);	// name of an array acts as pointer to first elment of that array
		gets(inbuf);
		valid_input = sscanf(inbuf, "%d", value); // value is already an address
	}
}

/*
	digit_sum() - will take the integer passed to it and return
	the sum of all of its digits.
*/
int digit_sum(int n) {
	int sum = 0;

	if (n < 0)  // assume that n != INT_MIN */
		n = -n;	// algorithm requires a positive numver

	while (n != 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}