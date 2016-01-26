/*
	input2.c - Yevhniy Chuba - 01/25/2016
	Demo of using gets() and sscanf() to 
	avoid scanf() problems

	Addition information could be found here:
	http://www.drpaulcarter.com/cs/common-c-errors.php
*/

#include <stdio.h>

main() {
	int val;
	int status = 0;
	char inbuf[133];

	while (status < 1) {
		printf("Enter and integer: ");
		gets(inbuf); // reads in one line of characters from stdin
					 // be careful as buffer size is static and can be exploited
		status = sscanf(inbuf, "%d", &val); // uses string as input to scanf-type functions

		if (status == 0)
			printf("That was not an integer!\n");
	}

	printf("The integer entered was %d.\n", val);
}

/*
	OK - got it! When entering a non-integer, the while loop continues to run,
	however, now there is the previous non-integer input in the buffer. To
	clear it, consume a single line of characters (of arbitrary size of 133)
	with gets. That way the next sscanf will have a cleared stdin. 

	gets() - has been depricated because it has been exploited a lot:
		- one way to exploit it is to overwrite the passed variable to scanf (not sscanf)
		- that way we can execute malicious code
		- here, however, the auther limits that buffer to 133
*/