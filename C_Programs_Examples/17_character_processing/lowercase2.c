/*
	lowercase2.c - Yevheniy Chuba - 01/26/2016
	Use ctype.h functions
*/

#include <stdio.h>
#include <ctype.h>

main() {
	char ch;

	while ((ch = getchar()) != EOF) {
		if (isupper(ch)) 	  // return true if ch is upper case letter
			ch = tolower(ch); // converts upper case to lower case
		putchar(ch);
	}
}