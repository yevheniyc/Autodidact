/*
	iolib.h - Yevheniy Chuba - 01/26/2016
	Library of personal I/O routines:
		- get an integer max/min-bound
*/

#include <limits.h>

#define BUFFER_SIZE 133

int get_bounded_integer(int lower_bound, int upper_bound);

int get_bounded_integer(int lower_bound, int upper_bound) {
	int user_input;
	int flag = 0;
	char buffer[BUFFER_SIZE];

	while (flag < 1) {
		printf("Enter and integer: ");
		// just like gets(), but with additional buffer size parameter for security
		fgets(buffer, BUFFER_SIZE, stdin);
		flag = sscanf(buffer, "%d", &user_input);

		if (flag == -1) // nothing was entered
			printf("Please enter an integer\n");
		else if (flag == 0)
			printf("That's is not an integer - please enter an integer\n");
		else {
			if (user_input < lower_bound) {
				printf("Please enter an integer >= %d\n", lower_bound);
				flag = 0;
			} else if (user_input > upper_bound) {
				printf("Please enter an integer <= %d\n", upper_bound);
				flag = 0;
			}
		}
	}

	return user_input;
}