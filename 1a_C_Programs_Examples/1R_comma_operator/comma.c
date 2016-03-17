/*
	comma.c - Yevheniy Chuba - 01/27/2016
	Demo of the comma operator through the exercise of averaging an input
	stream of floating point numbers. Can also be considered an example
	of a bad programming style.
*/

#include <stdio.h>

main() {
	float num, sum = 0.0;
	int n = 0;

	// Tell the user what to do
	printf("Let's average numbers\n");
	printf("Enter 'quit' to terminate\n");

	/*
		Use comma expression within the while loop expression to prompt,
		then read, the data. The scanf() function will return 1 if the input is
		a floating-point, and will return either 0 or -1 if the input is not.
		Assuming correct input.
	*/

	while (printf("Enter value #%d: ", n + 1), scanf("%f", &num) == 1) {
		sum += num;
		n++;
	}

	// Display the result
	printf("Averate is %f\n", sum / (float) n);
}

/*
	A better solution would be to specify an infinite while loop, then test to see if scanf
	returns a value other than one.  If so, then break out of the while loop.
*/