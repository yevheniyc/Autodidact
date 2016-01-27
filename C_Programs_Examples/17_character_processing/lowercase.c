/*
	lowercase.c - Yevheniy Chuba - 01/26/2016
	read input (preferably redirected) from standard input, 
	convert all upper case characters to lower case, then
	print out the results.
*/

#include <stdio.h>

main() {
	char ch;

	/*
		while loop uses getchar() to read in one character from the
		standard input (stdin). EOF is the pre-defined constant for 
		End Of File - so as long as one doesn't read in the EOF value 
		you are processing valid input.

		Please note that there are functions available for checking
		characters for certain properties in the ctype.h header file,
		which will be used in later examples.
	*/

	while ( (ch = getchar()) != EOF ) { // make assignment, then compare value against EOF
		if ((ch >= 'A') && (ch <= 'Z')) // check for uppercase character
			ch += 'a' - 'A';			// convert to lowercase the hard way - simple arithmetics
		putchar(ch);					// write character to stout
	}
}

/*
	In this program we had to use redirection of the standard input (>> lowercase < text)
	in order to process a file. Eventually we’ll learn how to properly 
	specify a file name on the command line and open it for processing.
*/