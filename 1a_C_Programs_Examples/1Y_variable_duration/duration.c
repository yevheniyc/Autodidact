/*
	duration.c - Yevheniy Chuba - 01/30/2016
	Examine duration of a variable
*/

#include <stdio.h>

// global variables - to be declared outside of all functions
int i = 0;

// function prototypes
int f(int x);
int g(int x);
int h(int x);

// main function
main() {
	int k;

	printf("The initial value for i is %d.\n\n", i);

	for (k = 0; k < 5; k++)
		printf("f(%d) = %d\n", k, f(k));
	printf("\n");
	for (k = 0; k < 5; k++)
		printf("g(%d) = %d\n", k, g(k));
	printf("\n");
	for (k = 0; k < 5; k++)
		printf("h(%d) = %d\n", k, h(k));
	printf("\n");
	printf("The final value for i is %d.\n", i);
}

// functions

/*
	f() - function using automatic storage duration: any value placed
		  within variable will cease to exist once the function is exited.
		  No initial value can be assumed.
*/

int f(int x) {
	int j = 0;
	j += x;
	return j;
}

/*
	g() - function using globally defined variable as a method for static
		  storage duration: any value placed within variable will exist as
		  long as the program excutes. The global variable can be used within
		  any function.
*/

int g(int x) { // global i continues to iterate when function is called again
	i += x;
	return i;
}

/*
	h() - function explicitly using static storage duration: any value placed
		  within variable will exist as long as the program executes, regardless
		  of the numver of times that the function is executed. The initial value
		  specified is valid only for the first time the function is executed.
		  The scope of the variable is limited to the funciton.
*/

int h(int x) { // static j continues to iterate when function is called again
			   // as long as the program exists - kind of like global but in local scope :)
	static int j = 0; // j = 0 only the first time the funciton is used, then will vary...
	j += x;
	return j;
}



//////// OUTPUT FOR QUICK REFERENCE /////////////////
/*

The initial value for i is 0.

f(0) = 0
f(1) = 1
f(2) = 2
f(3) = 3
f(4) = 4

g(0) = 0
g(1) = 1
g(2) = 3 // global i = 1 + new k = 2 value
g(3) = 6
g(4) = 10

h(0) = 0
h(1) = 1
h(2) = 3 // static j = 1 + new k = 2 value - static remembers variables within a function
h(3) = 6
h(4) = 10

The final value for i is 10.

*/