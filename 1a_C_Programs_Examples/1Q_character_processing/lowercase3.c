/*
	lowercase3.c - Yevheniy Chuba - 01/26
	Even better way of lowercase program - ctypes.h
*/

#include <stdio.h>
#include <ctype.h>

main() {
	char ch;

	while ((ch = getchar()) != EOF) 
		putchar(tolower(ch)); // if ch is not upper case, function returns ch
}