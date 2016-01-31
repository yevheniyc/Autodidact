/*
	buserror.c - Yevheniy Chuba - 01/30/2016
	THIS PROGRAM HAS A DELIBERATE ERROR

	This program will illustrate a condition that will cause
	a "bus error" when attempting to execute the program.
	The program will read in ten integers and calculate the average.
*/

#include <stdio.h>
#define SIZE 10

main() {
	int sum = 0;
	int valid_input;	// the flag that is used to test against (not for); 
						// reason: sscanf's returned -1 is still true
	char inbuf[133];
	char values[SIZE];
	int i;

	for (i = 0; i < SIZE; i++) {
		valid_input = 0;

		while (!valid_input) { // while valid_input is NOT true == IS 0;
			printf("Enter integer #%d: ", i + 1); 
			gets(inbuf);

			/*
				let's examine current address and the next address in the values array
				where an int will be put at: Let's modify the buserror program to print out 
				the address where the read in value is to be stored:
			*/
			printf("i=%d &values = %p &values[i] = %p\n", i, values, values + 1); // walk in array using address, just like with pointers

			valid_input = sscanf(inbuf, "%d", &values[i]); // address of i's element in the array

			/*
				test for valid_input: 
					-> -1 (whitespace + Enter)
					-> 0 (text or some other, but int, data type entered)
			*/
			switch(valid_input) {
				case -1:
					printf("Please enter an integer.\n\n");
					valid_input = 0;	// as -1 is interpreted as true and need to continue "while"
					break;
				case 0:
					printf("That was not an integer - please try again.\n\n");
			}
		}
	}

	// get the sum
	for (i = 0; i < SIZE; i++)
		sum += values[i];

	printf("Averate is %.1f\n", (float) sum / (float) SIZE);
}

/*
	NOTE:
		Now we can see the problem! On this (and many other) systems, 
		integers have to be stored on a "longword" boundary - in simple terms, 
		the address has to be divisible by 4. (To know the reason why this is 
		so you'd have to know something about computer architecture.) 
		In line 18 we accidently declared our values array to be of type char instead of type int. 
		The first store was performed as we were aligned on a longword. The second store, however, 
		caused an error as the address value was incremented by one (which is appropriate for a character array) 
		instead of by four (which is appropriate for an integer array). 
		Therefore, when you encounter a bus error, it means that your program tried 
		to save a value to a memory location that is not properly aligned for the given data type.
*/

/////// OUTPUT ///////////////////////
/*
	Didn't get the bus error, but got a warning and my output was funky for larger ints:

	Enter integer #1: 12
	i=0 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #2: 23
	i=1 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #3: 5555
	i=2 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #4: 545454
	i=3 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #5: 454
	i=4 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #6: 54454
	i=5 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #7: 5454545445
	i=6 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #8: 454545454
	i=7 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #9: 455454545454
	i=8 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Enter integer #10: 454545454454
	i=9 &values = 0x7fff5795a8d6 &values[i] = 0x7fff5795a8d7
	Averate is -0.9 =======> weird - in the example showed "Bus error", but here this.
*/