/*
	wordcount_wrong.c - Yevheiy Chuba - 01/27/2016
	Simple demo of trying to count the number of words in an
	input stream by counting the numver of whitespace characters.
*/

#include <stdio.h>

main() {
	unsigned long int words = 0;
	char ch;

	while ((ch = getchar()) != EOF)
		if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
			words++;

	printf("%d\n", words);
}

/*
	wc -w file_name == workdcount < file_name

	NOTE: 
		This program contains a logic error.  The erroneous assumption is that whitespace
		characters can be counted to determine the number of words present.  Unfortunately, this
		doesn’t handle the cases where a sequence of whitespace characters are encountered....
*/