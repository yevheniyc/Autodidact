/*
	flags.c - Yevheniy Chuba - 01/31/2016
	wordcount program that uses command line arguments for determining
	output parameters. All passed parameters must be flags; input is 
	still from standard input.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YES 1
#define NO 0

// function prototypes
void report_fatal_error(char *pgm_name, char *param, char *error_msg);

/*
	main:
		- argc = number of arguments passed
		- argv = array of argument strings
*/

int main(int argc, char *argv[]) { // probably array of pointers to strings (?)
	int characters = 0;
	int words = 0;
	int lines = 0;
	int in_word = NO;
	int i, j;
	// default settings
	int cflag = YES;
	int wflag = YES;
	int lflag = YES;

	char ch;

	// check to see if any arguments were passed
	if (argc > 1) {
		// if arguments have been passed then enable only 
		// those options that have been passed
		cflag = NO;
		wflag = NO;
		lflag = NO;

		/*
			- go through passed arguments
			- check first character of each argument to see
			  if it is a flag argument
		*/

		for (i = 1; i < argc; i++)
			if (argv[i][0] != '-') // if first character of i-th entry is not a dash...
				report_fatal_error(argv[0], argv[i], "is not a flag"); // argv[0] => ./flags
			else
				for (j = 1; j < strlen(argv[i]); j++) // process the flag
					switch(argv[i][j]) { // go through each character in the passed string
						case 'l': lflag = YES; break;
						case 'w': wflag = YES; break;
						case 'c': cflag = YES; break;
						default : report_fatal_error(argv[0], argv[i], // argv[0] => ./flags
													 "is not a legal flag");
					}
	}

	// process the characters
	while ((ch = getchar()) != EOF) {
		characters++; // increment character count passed into stdin
		// go through each character and test for: '\n', '\t', ' ', if none
		// then use default which means we are inside a word, so set the flat!
		switch(ch) {
			case '\n': lines++; 			// on newline increment line count
			case '\t': 						// i guess ignore
			case ' ' : if (in_word == YES) { // if a whitespace, we just left a word
							words++;		// so increment a word
							in_word = NO;   // and say we are in the whitespace, in case there are many
						}
						break;
			default  : in_word = YES;		// we are inside a word
		}
	}

	// print out needed information (which is counted independ of either the flags were passed or not)
	if (lflag) printf("%8d", lines);
	if (wflag) printf("%8d", words);
	if (cflag) printf("%8d", characters);
	printf("\n");
	exit(0); // exit program - successful execution
}

/*
	report_fatal_error: display error message to the stderr
*/
void report_fatal_error(char *pgm_name, char *param, char *error_msg) { // *pgm_name = argv[0] => ./flags
	fprintf(stderr, "%s: ERROR - \"%s\" %s\n", pgm_name, param, error_msg);
	fprintf(stderr, "Usage is: %s [-l] [-w] [-c] <textfile\n", pgm_name);
	exit(1); // exit program - unsuccessful completion
}