/* File name:  platy_bt_params.c
 *
 * Compiler:   MS Visual Studio 2013
 *
 * Author:     Svillen Ranev
 *             Mark Kaganovsky 040-789-903
 *
 * Course:     CST 8152 - Compilers, Lab Section 012
 *
 * Assignment: 1
 *
 * Date:       Feb 1 2016
 *
 * Professor:  Sv. Ranev
 *
 * Purpose:    This is the main program for Assignment #1, CST8152, Winter 16
 *             This file was modified so that it accepts two more arguments:
 *                 The initial capacity (argv[3])
 *                 The increment factor (argv[4])
 *             It is intended to be used by the script testBuffer.bat
 *             Nothing was changed except for the main function.
 *
 * Version:    1.16.2
 */

/* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
* to suppress the warnings about using "unsafe" functions like fopen()
* and standard sting library functions defined in string.h.
* The define directive does not have any effect on other compiler projects (gcc, Borland).
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "buffer.h"

/*check for ANSI C compliancy */
#define ANSI_C 0
#if defined(__STDC__)
#undef ANSI_C
#define ANSI_C 1
#endif

/*  Declaration of an error printing function with
*  variable number of arguments
*/
void err_printf(char *fmt, ...);
/*  Declaration of a buffer contents display function */
void display(Buffer *ptr_Buffer);
long get_filesize(char *fname);

int strtoPositiveSignedInt(const char *str);

int main(int argc, char **argv){

	pBuffer ptr_Buffer;   /* pointer to Buffer structure */
	FILE *fi;             /* input file handle */
	int loadsize = 0;     /*the size of the file loaded in the buffer */
	int ansi_c = !ANSI_C; /* ANSI C compliancy flag */

	int initialCapacity; /* Initial capacity of the buffer. */
	int incrementFactor; /* Increment factory of the buffer. */

	/* Check if the compiler option is set to compile ANSI C */
	/* __DATE__, __TIME__, __LINE__, __FILE__, __STDC__ are predefined preprocessor macros*/
	if (ansi_c){
		err_printf("Date: %s  Time: %s", __DATE__, __TIME__);
		err_printf("ERROR: Compiler is not ANSI C compliant!\n");
		exit(1);
	}

	/* missing file name or/and mode parameter */
	if (argc <= 4){
		err_printf("\nDate: %s  Time: %s", __DATE__, __TIME__);
		err_printf("\nRuntime error at line %d in file %s\n", __LINE__, __FILE__);
		err_printf("%s\b\b\b\b%s%s", argv[0], ": ", "Missing parameters.");
		err_printf("Usage: platybt  source_file_name  mode  initialCapacity  incrementFactor"); 
		exit(1);
	}




	/* Convert the initial capacity argument to an int. */
	initialCapacity = strtoPositiveSignedInt(argv[3]);
	if (initialCapacity == -1){
		err_printf("ERROR: Initial capacity contains invalid charcters.");
		exit(1);
	}
	else if (initialCapacity == -2 || initialCapacity > SHRT_MAX){ /* Make sure it is in the valid range of short values. */
		err_printf("ERROR: Initial capacity is too large.");
		exit(1);
	}

	incrementFactor = strtoPositiveSignedInt(argv[4]);
	if (incrementFactor == -1){
		err_printf("ERROR: invcrement factor contains invalid charcters.");
		exit(1);
	}
	else if (incrementFactor == -2 || incrementFactor > UCHAR_MAX){ /* Make sure it is in the valid range of char values. */
		err_printf("ERROR: Increment factor is too large.");
		exit(1);
	}

	/*
		printf("initialCapacity: %d\n", (short)initialCapacity);
		printf("incrementFactor: %d\n", (char)incrementFactor);
	*/




	/* create a source code input buffer */
	switch (*argv[2]){
		case 'f': case 'a': case 'm': break;
		default:
			err_printf("%s%s%s", argv[0], ": ", "Wrong mode parameter.");
			exit(1);
	}
	/*create the input buffer */
	ptr_Buffer = b_create((short)initialCapacity, (char)incrementFactor, *argv[2]);
	if (ptr_Buffer == NULL){
		err_printf("%s%s%s", argv[0], ": ", "Could not create buffer.");
		exit(1);
	}

	/* open the source file */
	if ((fi = fopen(argv[1], "r")) == NULL){
		err_printf("%s%s%s%s", argv[0], ": ", "Cannot open file: ", argv[1]);
		exit(1);
	}

	/* load a source file into the input buffer  */
	printf("Reading file %s ....Please wait\n", argv[1]);
	loadsize = b_load(fi, ptr_Buffer);
	if (loadsize == R_FAIL1)
		err_printf("%s%s%s", argv[0], ": ", "Error in loading buffer.");

	/* close the source file */
	fclose(fi);
	/*find the size of the file  */
	if (loadsize == LOAD_FAIL){
		printf("The input file %s %s\n", argv[1], "is not completely loaded.");
		printf("Input file size: %ld\n", get_filesize(argv[1]));
	}
	/* set a mark at the last char in the buffer*/
	b_setmark(ptr_Buffer, b_size(ptr_Buffer));

	/* display the contents of the input buffer */
	display(ptr_Buffer);

	/* pack the buffer
	* if possible, add end-of-file character (EOF) to the buffer
	* display again
	*/
	if (b_pack(ptr_Buffer)){
		if (!b_addc(ptr_Buffer, EOF))
			err_printf("%s%s%s", argv[0], ": ", "Error in writing to buffer.");
		display(ptr_Buffer);
	}


	/* free the dynamic memory used by the buffer */
	b_free(ptr_Buffer);
	/* make the buffer invalid
	It is not necessary here because the function terminates anyway,
	but will prevent run-time errors and crashes in future expansions
	*/
	ptr_Buffer = NULL;
	/*return success */
	return (0);
}

/* PURPOSE:          Convert a string to a positive signed integer.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *
 * PARAMETERS:       const char *str: The string to parse.
 *
 * RETURN VALUE:     SUCCESS: A number >= 0
 *                   FAILURE: -1, The string contained invalid charcters.
 *                            -2, The string contained a number which was too large for an int.
 *
 * ALGORITHM:        none
 */
int strtoPositiveSignedInt(const char *str){
	int  num;
	char digit;

	num = 0;
	while (*str && num>=0){
		digit = *str - '0';

		if (digit < 0 || digit > 9){
			return -1;
		}

		num = num * 10 + digit;

		str++;
	}

	if (num < 0){
		return -2;
	}

	return num;
}

/* error printing function with variable number of arguments*/
void err_printf(char *fmt, ...){
	/*Initialize variable list */
	va_list ap;
	va_start(ap, fmt);

	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);

	/* Move to new line */
	if (strchr(fmt, '\n') == NULL)
		fprintf(stderr, "\n");
}

void display(Buffer *ptr_Buffer){
	printf("\nPrinting buffer parameters:\n\n");
	printf("The capacity of the buffer is:  %d\n", b_capacity(ptr_Buffer));
	printf("The current size of the buffer is:  %d\n", b_size(ptr_Buffer));
	printf("The operational mode of the buffer is:   %d\n", b_mode(ptr_Buffer));
	printf("The increment factor of the buffer is:  %u\n", b_incfactor(ptr_Buffer));
	printf("The current mark of the buffer is:  %d\n", b_mark(ptr_Buffer));
	/*printf("The reallocation flag is:   %d\n",b_rflag(ptr_Buffer));*/
	printf("\nPrinting buffer contents:\n\n");
	b_print(ptr_Buffer);
}

long get_filesize(char  *fname){
	FILE *input;
	long flength;
	input = fopen(fname, "r");
	if (input == NULL){
		err_printf("%s%s", "Cannot open file: ", fname);
		return 0;
	}
	fseek(input, 0L, SEEK_END);
	flength = ftell(input);
	fclose(input);
	return flength;
}

