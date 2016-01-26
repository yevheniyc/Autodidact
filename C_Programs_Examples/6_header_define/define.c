/*
	define.c - Yevheniy Chuba - 01/25/2016
	Simple example of the use of the define pre-processor statement.
	All define statements are in the define.h header file, to 
	demonstrate how to include your won files. 

	Both define.c and define.h must be in the same working directory
	when compiled.
*/

#include <stdio.h>   // include system header file "/usr/include/stdio.h" 
#include "define.h"  // include user's header file "./define.h"

main() {
	float radius, area, volume, cost;

	// Tell the user who and what we are, then get the appropriate info
	output("Pie in the Face Corporation");
	output("Let's us calculate what size pie you need!");
	newline;
	inquiry("Enter radius (in inches) of the victim's face: ", radius);

	// Perform the calculations
	area = PI * radius * radius;
	volume = PIE_TIN_DEPTH * area;
	cost = UNIT_VOLUME_COST * volume;

	// Display the results: %.2f - rounded to two decimal places
	newline;
	output("*** RESULTS ***");
	newline;
	output("Yes! We can make a pie for You!");
	newline;
	printf("The area of the pie is %.2f square inches\n", area);
	printf("The volume of the pie is %.2f cubic inches\n", volume);
	printf("The cream filling costs $%.2f/in^3\n", UNIT_VOLUME_COST);
	printf("Your cost is $%.2f\n", cost);
	newline;
}