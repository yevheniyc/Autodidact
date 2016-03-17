/*
	charcount.c - Yevheniy Chuba - 01/27/2016
	Simple demo of counting number of characters in an input stream
*/

#include <stdio.h>

main() {
	unsigned long int characters = 0;

	while (getchar() != EOF)
		characters++;

	printf("%d\n", characters);
}

/*
	wc -c file_name == charcount < file_name
*/