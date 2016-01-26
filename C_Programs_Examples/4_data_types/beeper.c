/*
 beeper.c - Yevheniy Chuba (adopted from Estell) - 25 January 2016
 Demonstration of data types
*/

 #include <stdio.h>

 main() {
 	float speed, distance, time; // floating-point variable declaration
 	char beep; 					 // character variable declaration

 	// note that a character is enclosed within single quotes
 	beep = '\a'; // define beep to be the "audible alert" character

 	/*
		tell the user about the program.
		note that strings are enclosed within double quotes.
 	*/
	printf("    ACME Software Development Company\n");
	printf("Road Runner Apprehension Probability Calculator\n");

	// get information from the user
	printf("\n");
	printf("Distance in meters to the Road Runner: ");
	scanf("%f", &distance);

	printf("Maximum speed in km/h of your Foyt-Coyote engine: ");
	scanf("%f", &speed);

	// calculate the best-case time for reaching the coyote chow
	speed = 1000.0 * speed / 3600.0; // convert from km/h -> m/s
	time = distance / speed;

	// print out the results
	printf("Time to reach Road Runner's position is %.2f seconds.\n", time);
	printf("... but he'll be gone!!! %c%c\n", beep, beep);
	printf("Probability of having Road Runner Stew is %d%%.\n", 0);
 }