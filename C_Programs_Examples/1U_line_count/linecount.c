/*
	linecount.c - Yevheniy Chuba - 01/27/2016
	Sime demo of counting number of lines in an input stream
*/

#include <stdio.h>

main() {
	unsigned long int lines = 0;
	char ch;

	while ((ch = getchar()) != EOF)
		if (ch == '\n')
			lines++;

	printf("%d\n", lines);
}

/*
	wc -l file_name == linecount < file_name
*/