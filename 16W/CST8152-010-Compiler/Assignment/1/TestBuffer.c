/*  File name: platy_bt.c
 *  Purpose:This is the main program for Assignment #1, CST8152, Winter 16
 *  Version: 1.16.1
 *  Author: Svillen Ranev
 *  Date: 11 January 2016
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "buffer.h"

/* constant definitions */
long get_filesize(char *fname);
void err_fprintf(FILE *fp, char *fmt, ...);
void fdisplay(FILE *fp, Buffer *ptr_Buffer);

int main(int argc, char **argv){
	int numTests; /* The number of tests to perform (1 for each array element). All arrays must have the same number of elements. */
	int i;

	FILE *inputFile;
	FILE *outputFile;

	int loadsize = 0;
	pBuffer ptr_Buffer;

	short initialCapacities[] = { 200, 200, 200, 200, /* For ass1XXX.out files. */
	                              200, 200, SHRT_MAX, 200, 200, 200, (SHRT_MAX - 10), SHRT_MAX, 200, 200, 0, 0, 200, 0, -1 }; /* For bigfXXX files. */

	char incrementFactors[] = { 15, 15, 15, 15, /* For ass1XXX.out files. */
	                            15, 128, 15, 0, 128, 15, 9, 15, 0, 0, 15, 15, 128, 255, 255 }; /* For bigfXXX files. */

	char bufferModes[] = {'a', 'm', 'f', 'f',
	                      'a', 'a', 'a', 'f', 'f', 'm', 'm', 'm', 'a', 'm', 'a', 'm', 'm', 'f', 'x'};

	char *inputFiles[] = { "ass1.pls",
	                       "ass1.pls",
	                       "ass1.pls",
	                       "ass1e.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls",
	                       "bigf.pls"};
	
	char *outputFiles[] = { "TestOutputFiles/ass1ai.out",
	                        "TestOutputFiles/ass1mi.out",
	                        "TestOutputFiles/ass1fi.out",
	                        "TestOutputFiles/ass1e.out",
	                        "TestOutputFiles/bigfai.out",
	                        "TestOutputFiles/bigfai128.out", 
	                        "TestOutputFiles/bigfamax.out", 
	                        "TestOutputFiles/bigffi0.out", 
	                        "TestOutputFiles/bigffi128.out",
	                        "TestOutputFiles/bigfmi.out",
	                        "TestOutputFiles/bigfmi9.out",
	                        "TestOutputFiles/bigfmmax.out",
	                        "TestOutputFiles/bigfai0.out",
	                        "TestOutputFiles/bigfmi0.out",
	                        "TestOutputFiles/bigfac0.out", 
	                        "TestOutputFiles/bigfmc0.out",
	                        "TestOutputFiles/bigfmi128.out", 
	                        "TestOutputFiles/bigffc0.out", 
	                        "TestOutputFiles/bigfc-1.out"};

	numTests = 19;

	for(i=0; i<numTests; i++){
		putchar('\n');
		printf("Test %d:\n", i);
		printf("  Initial Capacity: %d\n", initialCapacities[i]);
		printf("  Increment Factor: %u\n", (unsigned char)incrementFactors[i]);
		printf("  Input File:       %s\n", inputFiles[i]);
		printf("  Output File:      %s\n", outputFiles[i]);

		/* Open input file. */
		inputFile = fopen(inputFiles[i], "r");
		if (inputFile == NULL){
			perror("  ERROR, could not open input file");
			continue;
		}

		/* Open output file. */
		outputFile = fopen(outputFiles[i], "w+");
		if (outputFile == NULL){
			perror("  ERROR, could not open output file");
			continue;
		}

		/* create buffer */
		ptr_Buffer = b_create(initialCapacities[i], incrementFactors[i], bufferModes[i]);
		if (ptr_Buffer == NULL){
			err_fprintf(outputFile, "%s%s%s", argv[0], ": ", "Could not create buffer.");
			continue;
		}

		/* load a source file into the input buffer  */
		fprintf(outputFile, "Reading file %s ....Please wait\n", inputFiles[i]);
		loadsize = b_load(inputFile, ptr_Buffer);

		if (loadsize == R_FAIL1){
			err_fprintf(outputFile, "%s%s%s", argv[0], ": ", "Error in loading buffer.");
			continue;
		}

		/* close the source file */
		fclose(inputFile);

		/* find the size of the file  */
		if (loadsize == LOAD_FAIL){
			fprintf(outputFile, "The input file %s %s\n", inputFiles[i], "is not completely loaded.");
			fprintf(outputFile, "Input file size: %ld\n", get_filesize(inputFiles[i]));
		}
		/* set a mark at the last char in the buffer*/
		b_setmark(ptr_Buffer, b_size(ptr_Buffer));

		/* display the contents of the input buffer */
		fdisplay(outputFile, ptr_Buffer);

		/* pack the buffer
		* if possible, add end-of-file character (EOF) to the buffer
		* display again
		*/
		if (b_pack(ptr_Buffer)){
			if (!b_addc(ptr_Buffer, EOF)){
				err_fprintf(outputFile, "%s%s%s", argv[0], ": ", "Error in writing to buffer.");
			}
			fdisplay(outputFile, ptr_Buffer);
		}
		else{
			puts("could not pack");
		}
		
		/* free the dynamic memory used by the buffer */
		fclose(outputFile);
		b_free(ptr_Buffer);
	}

	return EXIT_SUCCESS;
}

void err_fprintf(FILE *fp, char *fmt, ...){
	/*Initialize variable list */
	va_list ap;
	va_start(ap, fmt);

	(void)vfprintf(fp, fmt, ap);
	va_end(ap);

	/* Move to new line */
	if (strchr(fmt, '\n') == NULL)
		fprintf(fp, "\n");
}

void fdisplay(FILE *fp, Buffer *ptr_Buffer){
	char c;

	fprintf(fp, "\nPrinting buffer parameters:\n\n");
	fprintf(fp, "The capacity of the buffer is:  %d\n", b_capacity(ptr_Buffer));
	fprintf(fp, "The current size of the buffer is:  %d\n", b_size(ptr_Buffer));
	fprintf(fp, "The operational mode of the buffer is:   %d\n", b_mode(ptr_Buffer));
	fprintf(fp, "The increment factor of the buffer is:  %u\n", b_incfactor(ptr_Buffer));
	fprintf(fp, "The current mark of the buffer is:  %d\n", b_mark(ptr_Buffer));
	/*fprintf(fp, "The reallocation flag is:   %d\n",b_rflag(ptr_Buffer));*/
	fprintf(fp, "\nPrinting buffer contents:\n\n");

	/* Check if the buffer is empty. */
	if (b_isempty(ptr_Buffer)){
		fprintf(fp, "The buffer is empty.\n");
		return;
	}

	ptr_Buffer->getc_offset = 0;

	c = b_getc(ptr_Buffer);
	while (!b_eob(ptr_Buffer)){
		fputc(c, fp);
		c = b_getc(ptr_Buffer);
	}

	fputc('\n', fp);
}

long get_filesize(char  *fname){
	FILE *input;
	long flength;
	input = fopen(fname, "r");
	if (input == NULL){
		err_fprintf(stderr, "%s%s", "Cannot open file: ", fname);
		return 0;
	}
	fseek(input, 0L, SEEK_END);
	flength = ftell(input);
	fclose(input);
	return flength;
}

