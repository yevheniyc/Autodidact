/*
	input1.c - Yevheniy Chuba - 01/25/2016
	Demo for what can go wrong with scanf
*/

#include <stdio.h>

main() {
	int val; 
	int status = 0;

	// the scanf below return one of the following:
	//		-1 -> if nothing is entered
	//		 0 -> if entry is not "correctly spelled"
	// 		 1 -> if an integer
	while (status < 1) {
		printf("Enter an integer: ");
		status = scanf("%d", &val);

		if (status == 0) 
			printf("That was not an integer!\n");
	}

	printf("The integer entered was %d.\n", val);
}

/*
	Problems with scanf:
		- scanf skips over leading whitespace
		- scanf uses whitespace as a delimiter
		- scanf will stop once a non-integer character is encountered
		- scanf fails - input is left in the system input buffer
			- Note: when using script this actually resulted in an infinite loop! 
				When not in script the control-C did stop the runaway output.

*/

/* 
	Example output that shows issues with scanf:
	
	me> 7_scanf_problems whitehat$ ./a.out 
		Enter an integer: 24
	The integer entered was 24.
	me> 7_scanf_problems whitehat$ ./a.out 
		Enter an integer: 

			45
	The integer entered was 45.
	me> 7_scanf_problems whitehat$ ./a.out 
		Enter an integer:   34  wd
	The integer entered was 34.
	me> 7_scanf_problems whitehat$ ./a.out 
		Enter an integer: 56moo
	The integer entered was 56.
	me> 7_scanf_problems whitehat$ ./a.out 
		Enter an integer: hi
	That was not an integer!
	Enter an integer: That was not an integer!
	Enter an integer: That was not an integer!
	Enter an integer: That was not an integer!
	Enter an integer: That was not an integer!
	Enter an integer: That was not an integer!
	Enter an integer: Tha....control-C 
*/