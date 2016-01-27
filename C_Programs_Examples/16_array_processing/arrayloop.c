/*
	arrayloop.c - Yevheniy Chuba - 01/26/2016
	Demostration of using loops to process an array
*/	

#include <stdio.h>

/*
	The following constant (SIZE) is used to declare the size of the 
	integer array. If the size later changes, then only the define statement
	needs to be edited instead of going all throughout the source code.
*/

#define SIZE 10

main() {
	int i,
		sum = 0,
		numbers[SIZE]; // note that the array index range is from 0 to SIZE-1
	char letters[99] = "The average of the integers entered is "; // legal only here
	float result;

	// get some numbers for the array
	printf("Let's average %d itegers, shall we?\n\n", SIZE);
	for (i = 0; i < SIZE; i++) {
		printf("Enter integer #%d: ", i+1); // execute statement body if it is true
		scanf("%d", &numbers[i]); // add in stdin and add to numbers array
	}

	// calculate the average
	for (i=0; i < SIZE; i++)
		sum += numbers[i];

	result = (float) sum / (float) SIZE;

	// print out the text string the hard way, then display the result
	i = 0;
	while (letters[i]) // I belive the last character in the letters is or should be '\0' -> False
		printf("%c", letters[i++]); // move to the next character in the string

	printf("%f\n", result);
}