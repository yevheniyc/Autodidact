/*
    helloworld.c - Yevheniy Chuba (adopted from John K. Estell) - 22 January 2016
    Illustrates main, void, int, printf and return.
*/

/*
    The following is a pre-processor instruction that is used to allow 
    us to access the I/O functions in the stdio header file.
*/

#include <stdio.h>

/*
    C programs always start their execution with the main() function.
*/

int main(void) {
    int num; /* declare a variable of type integer */
    num = 1; 

    /*
        Use printf to write to the standard output.
        The '\n' - represents the newline character.
        The '%d' - represents printing out of an integer value
    */

    printf("Hello world!!\n");
    printf("I think my department is #%d.\n", num);

    /*
        The return statement ends the function and returns the specified
        value to the calling routine. This statement can be left out in the 
        main(), but must appear in all other functions that return a value.
    */
    
    return 0;
}

