/*
	wordcount_wc_version.c - Yevheniy Chuba - 01/27/2016
	Primitive version of UNIX's 'wc' program. Input is from
	standard input only in this version. Output displays the
	numver of lines, words, characters in that order.
	Note that the are no extra lines or text in the output, for
	that would violate the philosophy of UNIX with respect to piping
	information to another program.
*/

#include <stdio.h>

#define YES 1
#define NO  0

main() {
	unsigned long int characters = 0, words = 0, lines = 0;
	int in_word = NO;
	char ch;

	while ((ch = getchar()) != EOF) {
		characters++; 			// increment character count

		switch(ch) {
			case '\n':	lines++; // fall through as newline requires end of word test

			case '\t':	
			case ' ': 	if (in_word) {
							words++;
							in_word = NO;
						}
						break;
			default: 	in_word = YES;
		}
	}

	printf("%7d %7d %7d\n", lines, words, characters);
}