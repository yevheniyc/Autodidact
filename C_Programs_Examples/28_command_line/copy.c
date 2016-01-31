/*
	copy.c - Yevheniy Chuba - 01/31/2016
	Demonstration of file handling
*/

#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 512

int main(int argc, char *argv[]) {
	char buffer[BUFFER_SIZE];
	FILE *fpin, *fpout;

	if (argc != 3) { 	// check number of arguments
		fprintf(stderr, "Usage: %s sourcefile destination\n", argv[0]);
		exit(1);
	}

	// open files
	fpin = fopen(argv[1], "r"); // open filename (sourcefile) specified in command line for reading
	if (fpin == NULL) {			// fopen returns NULL upon error in opening the file
		fprintf(stderr, "%s: can't open %s for input\n", argv[0], argv[1]);
		exit(1);
	}

	fpout = fopen(argv[2], "w"); // open filename (destination) specified in command line for writing
	if (fpout == NULL) {		 // fopen returns NULL upon error in opening the file
		fprintf(stderr, "%s: can't open %s for input\n", argv[0], argv[1]);
		exit(1);
	}

	/* 
		Copy the sourcefile into destionation: fpin -> fpout
			- fgets: take whatever is in the input file (fpin) and put it in the buffer
					 do this until we get to the end of the file, when fgets will return NULL
			- fputs: take whatever is in the buffer and put it in the output file (fpout)
			- fclose: closes the files
	*/
	while (fgets(buffer, sizeof(buffer), fpin) != NULL) // while we haven't reached the end of the input file
		fputs(buffer, fpout); // put what 

	// close files
	if (fclose(fpin) != 0) { // not zero means an error when closing
		fprintf(stderr, "%s: unable to close %s\n", argv[0], argv[1]);
		exit(1);
	}

	if (fclose(fpout)) {
		fprintf(stderr, "%s: unable to close %s\n", argv[0], argv[1]);
		exit(1);
	}
	return 0;
}