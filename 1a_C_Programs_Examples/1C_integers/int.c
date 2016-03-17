/*
	int.c - Yevheniy Chuba (adopted from Estell) - 23 January 2016
	Integer examples.
*/

#include <stdio.h>

main() {
	int num1;
	int num2 = 2;

	printf("num1 = %d num2 = %d\n\n", num1, num2);

	printf("Enter num1: ");
	scanf("%d", &num1);
	printf("num1 = %d\n\n", num1);

	// 2 and 5 between "%" and "d" represent spaces
	printf("2^%2d = %5d\n", 3, 8);
	printf("2^%2d = %5d\n", 4, 16);
	printf("2^%2d = %5d\n", 6, 64);
	printf("2^%2d = %5d\n", 8, 256);
	printf("2^%2d = %5d\n", 10, 1024);
	printf("2^%2d = %5d\n", 16, 65536);
}