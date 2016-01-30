/*
	calculator.c - Yevheniy Chuba - 01/30/2016
	Simple calculator program to demonstrate functions
	and parsing using scanf.
	Uses infix notation - input format: operand1 operator operand2
	Compile with: gcc -o calculator calculator.c -lm
*/

#include <stdio.h>
#include <math.h>

// function prototypes
double add(double x, double y);			// addition operations
double subtract(double x, double y);	// subtraction operations
double multiply(double x, double y); 	// multiplication operations
double divide(double x, double y); 		// division operations

// main program
main() {
	int valid_input = 1; 	// flag for keeping track of valid input
	double x, y, result;	// operands and result for operations
	char op;				// operator
	char inbuf[133];			// input buffer

	// display program information
	printf("Simple calculator - format is number operator number\n");
	printf("Supported operations:\n");
	printf("    + (add)  - (subt)  * (mult)  - (div)  ^ (power)\n\n");

	/*
		obtain input from the user:
			- "%lf" for double-precision floating point,
			- "%c" to read next non-whitespace character.
	*/

	printf("Enter equation: ");
	gets(inbuf); // everything entered into stdin from now on goes into input buffer!
	if (sscanf(inbuf, "%lf %c %lf", &x, &op, &y) != 3) // 1 -> good; -1 -> not entered; 0 -> wrong
		valid_input = 0;

	// process the operator and perform the indicated operation
	switch (op) {
		case '+': result = add(x, y); 		break;
		case '-': result = subtract(x, y); 	break;
		case '*': result = multiply(x, y);	break;
		case '/': result = divide(x, y); 	break;
		case '^': result = pow(x, y); 		break;	// using function in math.h
		default	: valid_input = 0; 			break;
	}

	// display the result
	if (valid_input) // input 1 (true) than show the result
		printf("%lf %c %lf = %lf\n", x, op, y, result);
	else // otherwise show the error
		fprintf(stderr, "Error.\n"); // writing error messages to the standard error devide
}

// functions
double add(double x, double y) {
	return x + y; // evaluate the expression and then return the result
}

double subtract(double x, double y) {
	return x - y;
}

double multiply(double x, double y) {
	return x * y;
}

double divide(double x, double y) {
	return x / y;
}