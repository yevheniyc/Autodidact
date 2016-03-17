/*
    dbxdemo.c - Yevheniy Chuba (adopted from Estell) - 23 January 2016
    Demonstrating dbx debugging facility. To use the debugger, use the
    -g option when compiling:

        {dudette} gcc -g -o dbxdemo dbxdemo.c

    Before debugging, good practice to show line numbers:

        {dude} cat -n dbxdemo.c
*/

#include <stdio.h>

/* Variables can be initialized during declaration */
main() {
    int count = 0, sum = 0, value;
    char ch;
    float average;
    
    /* read in value until a zero is entered, then print average  */
    while (1) {
        printf("Enter integer: ");
        scanf("%d", &value); /* terminal input function */
        if (value == 0) 
            break; /* exit the loop */
        sum = sum + value;
        count++;
    }

    average = sum / count; /* note that this gives a truncated answer  */
    printf("The average of the values is %f\n", average);
    
    /* get a character and print out its ASCII value  */
    
    printf("Enter an integer from 32 to 127: ");
    scanf("%d", &value);
    ch = (char) value; /* cast to char */
    printf("The ASCIII value for '%c' is %d.\n", ch, ch); /* the error was here! */
}



