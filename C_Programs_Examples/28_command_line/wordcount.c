/*
	wordcount.c - Yevheniy Chuba - 01/31/2016
	Unix wc "workalike" program, complete with files and flags.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YES 1
#define NO 0
#define UsageMesg "Usage: %s [-lwc] [filelist]\n"
#define OpenMesg  "%s: %s: No such file or directory\n"

main(int argc, char *argv[]) {
	int characters, words, lines; // count per file
	int tcharacters = 0, twords = 0, tlines = 0; // count for all files
	int ch, in_word, index, j, fileptr;
	int cflag = YES, wflag = YES, lflag = YES; // default settings
	FILE *fp;

	fp = stdin; // default input
	fileptr = argc; // assuming no filenames as arguments

	/*
		check for passed arguments - assume all flags appear before filelist
	*/
	if (argc > 1) {
		if (argv[1][0] == '-') { // any flags?
			cflag = NO; // if flag arguments have been passed then enable only
			wflag = NO; // those options that have been selected
			lflag = NO;
		}

		for (index = 1; index < argc; index++) // go through passed arguments
			if (argv[index][0] == '-') { // look to see if it is a flag
				// process the flag by looping through non-dash portion of the flag
				for (j = 1; j < strlen(argv[index]); j++)
					switch (argv[index][j]) {
						case 'l': lflag = YES; break; // output line count
						case 'w': wflag = YES; break; // output word count
						case 'c': cflag = YES; break; // output character count
						default : fprintf(stderr, UsageMesg, argv[0]);
								  exit(1);
					}
			} else {
				// if no dash workcount -c -c filaname1 filename2 - remaining arguments are filenames
				fileptr = index;
				break;
			}
	} else { // if only a single argument was passed (the executable name), than exit with usage and error
		fprintf(stderr, UsageMesg, argv[0]);
		exit(1);
	}

	/*
		perform actual counts of lines, words, and characters
	*/
	while (index < argc) {
		/*
			if file(s) have been specified, check to see if they'are
			available and open the file if it is there.
			SKIP THIS if stdin is being used!
		*/

		if (fileptr != argc)
			if ((fp = fopen(argv[index], "r")) == NULL) {
				fprintf(stderr, OpenMesg, argv[0], argv[index++]); // can't read file
				continue;
			}

		characters = words = lines = 0; // zero counters and flag
		in_word = NO;

		while ((ch = getc(fp)) != EOF) { // process the current file
			characters++;	// increment character count

			if (ch == '\n')	// increment line count
				lines++;

			/* Simple logical workthrough:
					"Hello     world!\n
					I am a new\tline"
				1. ch == 'H' -> in_word == NO - True -> in_word = YES -> words == 1
				2. ... until ' '
				3. ch == ' ' - True -> in_word == NO
				4. ch == ' ' - True -> in_word == NO
				This algorithm and in_word flag makes sure that repeated whitespaces are 
				handles properly without adding new words where trailing whitespaces are present

			*/
			if ((ch == ' ') || (ch == '\t') || (ch == '\n')) // have whitespace
				in_word = NO;
			else if (in_word == NO) { // increment word count
				in_word = YES;
				words++;
			}
		}

		/*
			output current file results - print only what was spcified
		*/
		if (lflag) printf(" %7d", lines);
		if (wflag) printf(" %7d", words);
		if (cflag) printf(" %7d", characters);

		if (argc != fileptr)
			printf(" %s\n", argv[index]); // print filename
		else
			printf("\n");

		// clean up and do updates
		fclose(fp);	// close current input file
		tcharacters += characters; // update total counts for all files
		twords += words;
		tlines += lines;
		index++;
	}

	/*
		output totals if more than one file was processed
	*/
	if (argc - fileptr > 1) { // then have two or more files, so print out total counts(s)
		if (lflag) printf(" %7d", tlines);
		if (wflag) printf(" %7d", twords);
		if (cflag) printf(" %7d", tcharacters);
		printf("total\n");
	}

	exit(0); // exit program - return status normal: successful execution
}

/*
	Note that, while this is a workalike program, this is not the most efficient implementation 
	possible for this code. For example, the character count can be more readily obtained by using 
	an advanced system function that will return the attributes for a specified file. 
	Things that are not being requested by the user could be skipped, thereby saving additional time.
*/