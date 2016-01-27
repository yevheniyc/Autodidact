/*
	rubberband.c - Yevheniy Chuba - 01/26/2016
	calculation program to determine and verify target parameters...
	Compile with: gcc -o rubberband rubberband.c -lm
*/

#include <stdio.h>
#include <math.h>

#define target_distance 30.0 // professor is 30 feet away
#define target_height	5.75 // professor is 5'9"
#define BUFFER_SIZE		133

main() {
	double velocity, x_vel, y_vel, theta, time, pi, height;
	char buffer[BUFFER_SIZE];

	// Give target information and obtain attack parameters
	printf("Target distance is %.1f feet away\n", target_distance);
	printf("Target is %.2f feet tall\n\n", target_height);

	printf("Enter angle of elavation in degrees: ");
	scanf("%1f", &theta); // "%1f" is used to read in values of type double
	
	printf("Enter initial velocity in feet per second: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	scanf("%1f", &velocity);

	printf("Enter initial height in feet: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	scanf("%1f", &height);

	// Calculate x and y velocity components
	pi = 2.0 * asin(1.0);
	x_vel = velocity * cos( theta * pi / 180 );
	y_vel = velocity * sin( theta * pi / 180 );

	// Calculate time to target and height of rubber band at that time
	fgets(buffer, BUFFER_SIZE, stdin);
	printf("Target distance ====> %.1f\n", target_distance);
	time = target_distance / x_vel;
	printf("Time ====> %.1f\n", time);
	height = height + y_vel * time - 16.0 * time * time;

	/*
		Determine the results - professor has been hit if the height of the
		rubber band is between the professor's height and ground, assuming
		Jennyfur can shoot straight!
	*/

	if ((height > 0.0) && (height < target_height)) { // && is logical AND operator
		printf("You hit the professor with the rubber band!!!\n");
		printf("GOOD!");
	} else 
		printf("You missed!\n");

	printf("Height of the rubber band at target was %.2f feet.\n", height);
}