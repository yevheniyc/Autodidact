/*
	wordcount_correct.c - Yevheniy Chuba - 01/27/2016
	Better demo of trying to count the numver of words in an 
	input stream by keeping track of whether or not we'are within a word.
*/

#include <stdio.h>

#define NO 	0
#define YES 1

main() {
	unsigned long int words = 0;
	char ch;
	int in_word = NO;

	while ((ch = getchar()) != EOF)
		if ((ch == ' ') || (ch == '\t') || (ch == '\n')) {
			if (in_word) {
				words++;
				in_word = NO;
			}
		} else
			in_word = YES; // if it is not a whitespace then it's a word
						   // covers cases of multiple whitespaces
	printf("%d\n", words);
}

/*
	wc -w file_name == wordcount_correct < text
	
	NOTE:
		proper way to count the number of words is to count 
		the number of non-whitespace character to whitespace character 
		transitions in the data stream. To do this we must somehow examine 
		all two-character sequences in the stream. Simple solution is 
		to use a flag variable to keep track of whether or not we’re 
		currently in a word. When the flag is set and whitespace is encountered 
		then increment the word count and reset the flag. The flag will be set 
		every time a non-whitespace character is encountered.
*/