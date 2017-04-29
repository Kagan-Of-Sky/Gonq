/*
File Name:     stable.c
Compiler:      MS Visual Studio 2013
Author:        Mark Kaganovsky, 040789903
Course:        CST 8152 - Compilers, Lab Section 012
Assignment:    3
Date:          March 30 2016
Professor:     Sv. Ranev
Purpose:       Implementation of the symbol table.

Function List: st_create
               st_install
               st_lookup
               st_update_type
               st_update_value
               st_get_type
               st_destroy
               st_print
               st_store
               st_setsize
               st_incoffset

               st_sort
               st_sort_compare_asc_lex
               st_sort_compare_desc_lex
               st_reorganize_lexemes
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "stable.h"


extern STD sym_table;


/* Local functions. */
static void st_setsize(void);
static void st_incoffset(void);

/* Functions related to bonus #1 and #2. */
static int st_sort_compare_asc_lex(const void *a, const void *b);
static int st_sort_compare_desc_lex(const void *a, const void *b);
static int st_reorganize_lexemes(STD *sym_table);




/*
PURPOSE:          Create a new, empty symbol table.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0

CALLED FUNCTIONS: malloc
                  b_create
                  free
                  
PARAMETERS:       int size - The number of symbol table records. Must be a number greater than 0.
                  
RETURN VALUE:     A symbol table descriptor. To find out whether this function suceeded or not,
                  you must check the value of st_size. If it is 0 then this function failed.
                  
ALGORITHM:        none
*/
STD st_create(int size){
	const short lexBufInitCapacity = 0; /* Initial capacity of the lexeme buffer. */
	const char  lexBufIncFactor    = 1; /* Increment factor of the lexeme buffer. */

	STD    symbolTable;
	size_t stvrStorageSize; /* Size of the STVR storage area in bytes. */

	/* Make sure the size is valid. */
	if (size <= 0){
		symbolTable.st_size = 0;
		return symbolTable;
	}

	symbolTable.st_offset = 0;
	symbolTable.st_size   = size;

	/* Calculate the number of bytes needed for the STVR storage area. */
	for (stvrStorageSize=0; size; --size){
		if ((stvrStorageSize + sizeof(STVR)) < stvrStorageSize){ /* Check for overflow. */
			symbolTable.st_size = 0;
			return symbolTable;
		}
		stvrStorageSize += sizeof(STVR);
	}

	/* Allocate memory for the STVRs. */
	symbolTable.pstvr = (STVR *)malloc(stvrStorageSize);
	if (NULL == symbolTable.pstvr){
		symbolTable.st_size = 0;
		return symbolTable;
	}

	/* Create the lexeme storage buffer. */
	symbolTable.plsBD = b_create(lexBufInitCapacity, lexBufIncFactor, B_MODE_ADDITIVE_ARG);
	if (NULL == symbolTable.plsBD){
		free(symbolTable.pstvr);
		symbolTable.st_size = 0;
		return symbolTable;
	}

	return symbolTable;
}




/*
PURPOSE:          Install a new VID record into a symbol table.
AUTHOR:           Mark Kaganovsky
VERSION:          1.3

CALLED FUNCTIONS: st_lookup
                  b_setmark
                  b_size
                  strlen
                  b_addc
                  b_rflag
                  st_incoffset
                  
PARAMETERS:       STD sym_table - The symbol table to install this VID into.
                  char *lexeme  - Pointer to null terminated name of the VID.
                  char type     - Type of the variable (Float, Integer, String).
                                  Use the STVR_TYPE_XXXXXX constants.
                  int line      - Line number of this VID.
                  
RETURN VALUE:     SUCCESS: A value >=0. This number can represent either an exisiting
                           record, or the position this new record was inserted in.
                           Check if sym_table.st_offset went up to find out which.
                  FAILURE: -1 The symbol table is full, or invalid.
                           -2 Lexeme could not be copied into the character buffer.
                           -3 Invalid type argument.

ALGORITHM:        Uses st_lookup() to check whether the lexeme exists already.
*/
int st_install(STD sym_table, char *lexeme, char type, int line){
	STVR *newRecord;
	int   lexLen;
	int   i;

	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -1;
	}

	/* Check if the lexmeme already exists. */
	i = st_lookup(sym_table, lexeme);
	if (i >= 0){
		return i;
	}

	/* Check if there is enough room. */
	if (sym_table.st_offset == sym_table.st_size){
		return -1;
	}

	/* Get a pointer to the new record. */
	newRecord = sym_table.pstvr + sym_table.st_offset;

	/* Set the line number. */
	newRecord->o_line = line;
	
	/* Set the status field and initial values. */
	newRecord->status_field = STVR_STATUS_MASK_RESERVED;
	switch (type){
		case STVR_TYPE_INTEGER:
			newRecord->status_field    |= STVR_STATUS_MASK_INTEGER;
			newRecord->i_value.int_val  = STVR_INIT_VALUE_INTEGER;
			break;
		case STVR_TYPE_FLOAT:
			newRecord->status_field    |= STVR_STATUS_MASK_FLOAT;
			newRecord->i_value.fpl_val  = STVR_INIT_VALUE_FLOAT;
			break;
		case STVR_TYPE_STRING:
			newRecord->status_field       |= STVR_STATUS_MASK_STRING;
			newRecord->status_field       |= STVR_STATUS_MASK_UPDATE; /* Turn on the update bit. */
			newRecord->i_value.str_offset  = STVR_INIT_VALUE_STRING;
			break;
		default:
			return -3;
	}

	/* Get pointer to lexeme start. */
	newRecord->plex = b_setmark(sym_table.plsBD, b_size(sym_table.plsBD));

	/* Copy the lexeme into the lexeme storage buffer. */
	for (i=0, lexLen=(int)strlen(lexeme);    i<=lexLen;    ++i, ++lexeme){
		if (!b_addc(sym_table.plsBD, *lexeme)){ /* Buffer is full. */
			return -2;
		}
		else if (b_rflag(sym_table.plsBD)){ /* Location of dynamic buffer array changed. */
			if (sym_table.st_offset > 0){ /* One or more records already exist. */
				STVR *stvr;
				char *oldBufferHead;
				char *newBufferHead;
				int   j;

				oldBufferHead = sym_table.pstvr->plex;
				newBufferHead = b_setmark(sym_table.plsBD, 0);

				/* For every record, including the new one (hence <= instead of just <), update the lexeme pointer. */
				for (j=0, stvr=sym_table.pstvr; j<=sym_table.st_offset; ++j, ++stvr){
					stvr->plex = newBufferHead + (stvr->plex - oldBufferHead);
				}
			}
			else{
				newRecord->plex = b_setmark(sym_table.plsBD, 0);
			}
		}
	}

	/* Increment the global symbol table offset. */
	st_incoffset();

	return sym_table.st_offset + 1;
}




/*
PURPOSE:          Search for a lexeme in a symbol table.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: strcmp
                  
PARAMETERS:       STD sym_table - Symbol table to search for the lexeme in.
                  char *lexeme  - Pointer to null terminated VID.
                  
RETURN VALUE:     SUCCESS: A value >= 0, representing the offset from the beginning
                           of the symbol table record storage.
                  FAILURE: -1, lexeme not found.
                           -2, Invalid symbol table.

ALGORITHM:        Linear search starting from the last element and working to the first.
*/
int st_lookup(STD sym_table, char *lexeme){
	int i;

	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -2;
	}

	/* Perform the search backwards. */
	for (i=sym_table.st_offset-1; i>=0; --i){
		if (!strcmp(lexeme, sym_table.pstvr[i].plex)){
			return i; /* Lexeme found. */
		}
	}

	/* Lexeme not found. */
	return -1;
}




/*
PURPOSE:          Update the type of a VID.
AUTHOR:           Mark Kaganovsky
VERSION:          1.1
CALLED FUNCTIONS: none
                  
PARAMETERS:       STD sym_table  - Symbol table containing this VID.
                  int vid_offset - Index that this VID record resides in sym_table.
                  char v_type    - The type to update this VID to.
                  
RETURN VALUE:     SUCCESS: vid_offset.
                  FAILURE: -1 Out of range vid_offset.
                           -2 Invalid symbol table.
ALGORITHM:        none
*/
int st_update_type(STD sym_table, int vid_offset, char v_type){
	STVR *stvr;

	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -2;
	}

	/* Make sure the offset is within valid range. */
	if (vid_offset < 0 || vid_offset >= sym_table.st_offset){
		return -1;
	}

	/* Get a pointer to the record. */
	stvr = sym_table.pstvr + vid_offset;

	/* Check if this record has already been updated. */
	if (stvr->status_field & STVR_STATUS_MASK_UPDATE){
		return -1;
	}

	/* Change the type of the VID. */
	switch (v_type){
		case STVR_TYPE_INTEGER:
			stvr->status_field = stvr->status_field & (~STVR_STATUS_MASK_TYPE) | STVR_STATUS_MASK_INTEGER;
			break;
		case STVR_TYPE_FLOAT:
			stvr->status_field = stvr->status_field & (~STVR_STATUS_MASK_TYPE) | STVR_STATUS_MASK_FLOAT;
			break;
		default:
			return -1;
	}
	
	/* Turn on update flag. */
	stvr->status_field |= STVR_STATUS_MASK_UPDATE;

	return vid_offset;
}




/*
PURPOSE:          Update the value of a VID.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: st_get_type
                  
PARAMETERS:       STD sym_table        - Symbol table containing this VID.
                  int vid_offset       - Index that this VID record resides in sym_table.
                  InitialValue i_value - The new value to change it to.
                  
RETURN VALUE:     SUCCESS: The value of vid_offset.
                  FAILURE: -1, Out of range vid_offset.
                           -2, Invalid sym_table.

ALGORITHM:        none
*/
int st_update_value(STD sym_table, int vid_offset, InitialValue i_value){
	STVR *stvr;

	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -2;
	}

	/* Make sure the offset is within valid range. */
	if (vid_offset < 0 || vid_offset >= sym_table.st_offset){
		return -1;
	}

	/* Get a pointer to the record to update. */
	stvr = sym_table.pstvr + vid_offset;

	/* Update initial value based on type. */
	switch (st_get_type(sym_table, vid_offset)){
		case STVR_TYPE_INTEGER:
			stvr->i_value.int_val = i_value.int_val;
			break;
		case STVR_TYPE_FLOAT:
			stvr->i_value.fpl_val = i_value.fpl_val;
			break;
		case STVR_TYPE_STRING:
			stvr->i_value.str_offset = i_value.str_offset;
			break;
		default:
			return -1;
	}

	return vid_offset;
}




/*
PURPOSE:          Determine the type of a VID.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: none
                  
PARAMETERS:       STD sym_table  - Symbol table containing this VID.
                  int vid_offset - Index that this VID resides in sym_table.
                  
RETURN VALUE:     SUCCESS: One of the constants STVR_TYPE_XXXXXXX
                  FAILURE: -1, Invalid vid_offset or invalid symbol record type.
                           -2, Invalid symbol table.
ALGORITHM:        none
*/
char st_get_type(STD sym_table, int vid_offset){
	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -2;
	}

	/* Make sure the offset is within valid range. */
	if (vid_offset < 0 || vid_offset >= sym_table.st_offset){
		return -1;
	}

	switch (sym_table.pstvr[vid_offset].status_field & STVR_STATUS_MASK_TYPE){
		case STVR_STATUS_MASK_INTEGER: return STVR_TYPE_INTEGER;
		case STVR_STATUS_MASK_FLOAT:   return STVR_TYPE_FLOAT;
		case STVR_STATUS_MASK_STRING:  return STVR_TYPE_STRING;

		default:
			return -1;
	}
}




/*
PURPOSE:          Free the memory occupied by a symbol table's dynamic areas and
                  sets the global sym_table.st_size to 0.

AUTHOR:           Mark Kaganovsky
VERSION:          1.0

CALLED FUNCTIONS: b_free
                  free
                  st_setsize
                  
PARAMETERS:       STD sym_table
                  
RETURN VALUE:     none
ALGORITHM:        none
*/
void st_destroy(STD sym_table){
	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return;
	}

	b_free(sym_table.plsBD);
	free(sym_table.pstvr);
	st_setsize();
}




/*
PURPOSE:          Prints the contents of the symbol table to the standard output.
AUTHOR:           Mark Kaganovsky
VERSION:          1.1

CALLED FUNCTIONS: puts
                  printf
                  
PARAMETERS:       STD sym_table - The symbol table to print.
                  
RETURN VALUE:     SUCCESS: The number of symbol table records printed (>= 0)
                  FAILURE: -1, Invalid symbol table.
ALGORITHM:        none
*/
int st_print(STD sym_table){
	STVR *stvr;
	int   i;
	int   maxLineNumber, columnWidth, numSpaces; /* These variables are used for aligning the output. */
	
	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -1;
	}

	/* Calculate the maximum line number. */
	for (i=0, maxLineNumber=0; i < sym_table.st_offset; ++i){
		stvr = &sym_table.pstvr[i];
		if (stvr->o_line > maxLineNumber){
			maxLineNumber = stvr->o_line;
		}
	}

	/* Calculate the number of digits the max line number is made up of. */
	for (columnWidth=0; maxLineNumber; maxLineNumber/=10){
		++columnWidth;
	}

	/* Print header. */
	puts("\nSymbol Table");
	puts("____________\n");
	puts("Line Number Variable Identifier");

	/* Print data. */
	numSpaces = 12 - columnWidth;
	for (i=sym_table.st_offset, stvr=sym_table.pstvr; i; --i, ++stvr){
		printf("%*d%*c%s\n", columnWidth, stvr->o_line, numSpaces, ' ', stvr->plex);
	}

	return sym_table.st_offset;
}




/*
PURPOSE:          Stores the symbol table into a file named $stable.ste. If the file
                  already exists, it is overriden.

AUTHOR:           Mark Kaganovsky
VERSION:          1.1

CALLED FUNCTIONS: fopen
                  fprintf
                  fclose
                  strlen
                  st_get_type
                  puts
                  
PARAMETERS:       STD sym_table - The symbol table to store into the file.
                  
RETURN VALUE:     SUCCESS: A number >= 0, representing the number of records written to the file.
                  FAILURE: -1  An IO error occured while trying to open the file, write to it, or 
                               when closing it.
                           -2  Invalid symbol table.

ALGORITHM:        none
*/
int st_store(STD sym_table){
	FILE *fp;
	int   i;
	int   ret; /* Return value of fprintf. */
	
	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -2;
	}

	/* Open file. */
	fp = fopen("$stable.ste", "w");
	if (NULL == fp){
		return -1;
	}
	
	/* Write the size of the symbol table. */
	if (fprintf(fp, "%d", sym_table.st_size) < 0){
		fclose(fp);
		return -1;
	}

	for (i=0; i<sym_table.st_offset; ++i){
		STVR *stvr;
		stvr = &sym_table.pstvr[i];

		/* Write status field, lexeme length, lexeme, and line number. */
		ret = fprintf(fp, " %X %lu %s %d ", stvr->status_field, (unsigned long)strlen(stvr->plex), stvr->plex, stvr->o_line);
		if (ret < 0){
			fclose(fp);
			return -1;
		}

		/* Write the initial value. */
		switch (st_get_type(sym_table,i)){
			case STVR_TYPE_INTEGER:
				ret = fprintf(fp, "%d", stvr->i_value.int_val);
				break;
			case STVR_TYPE_STRING:
				ret = fprintf(fp, "%d", stvr->i_value.str_offset);
				break;
			case STVR_TYPE_FLOAT:
				/* QUESTION: What if the following was written: iFloat = 0.003? Would we print only 0.00? */
				ret = fprintf(fp,"%.02f",stvr->i_value.fpl_val);
				break;
		}

		/* Error occured when writing initial value. */
		if (ret < 0){
			fclose(fp);
			return -1;
		}
	}

	/* Close file. */
	if (fclose(fp)){
		return -1;
	}

	puts("Symbol Table stored.");

	/* Return the number of records written. */
	return i;
}




/*
PURPOSE:          Set the st_size field in the global sym_table to 0.
                  Used by functions which do not have access to the global sym_table.

AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: none
PARAMETERS:       none
RETURN VALUE:     none
ALGORITHM:        none
*/
void st_setsize(void){
	sym_table.st_size = 0;
}




/*
PURPOSE:          Increment the st_offset field in the global sym_table by 1.
                  Used by functions which do not have access to the global sym_table.

AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: none
PARAMETERS:       none
RETURN VALUE:     none
ALGORITHM:        none
*/
void st_incoffset(void){
	++sym_table.st_offset;
}




/************************************************************************
FUNCTIONS RELATED TO BONUS #1 AND #2 BELOW
*************************************************************************/




/*
PURPOSE:          Sort a symbol table's STVR records.
AUTHOR:           Mark Kaganovsky
VERSION:          1.1
CALLED FUNCTIONS: none
                  
PARAMETERS:       STD  sym_table - The symbol table to sort.
                  char s_order   - The order to sort in. Use ST_SORT_XXXXXX constants.

RETURN VALUE:     SUCCESS:  1 sym_table was succesfully sorted.
                  FAILURE: -1 Invalid sort argument or invalid symbol table.
                           -2 Could not sort lexemes

ALGORITHM:        Uses the standard c library function qsort(), performance is:
                      Average: O(nlogn)
                      Worst:   O(n^2)
*/
int st_sort(STD sym_table, char s_order){
	/* Check for valid symbol table. */
	if (IS_INVALID_STD(sym_table)){
		return -1;
	}

	switch (s_order){
		case ST_SORT_LEX_ASC:
			qsort(sym_table.pstvr, (size_t)sym_table.st_offset, sizeof(STVR), st_sort_compare_asc_lex);
			break;

		case ST_SORT_LEX_DESC:
			qsort(sym_table.pstvr, (size_t)sym_table.st_offset, sizeof(STVR), st_sort_compare_desc_lex);
			break;

		/* Invalid sort order. */
		default:
			return -1;
	}

	/* Sort the lexeme character buffer. */
	if (st_reorganize_lexemes(&sym_table)){
		return -2;
	}

	return 1;
}




/*
PURPOSE:          Compare 2 lexemes when sorting in ascending order.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: strcmp
                  
PARAMETERS:       const void *stvr1 - Pointer to first stvr.
                  const void *stvr2 - Pointer to second lexeme.
                  
RETURN VALUE:     >0 stvr1 is larger than stvr2 (stvr2 would appear first in a dictionary).
                   0 stvr1 is equal to stvr2.
                  <0 stvr1 is less than stvr2 (stvr1 would appear first in a dictionary).
                  
ALGORITHM:        This comparator is used for the standard c function qsort().
*/
int st_sort_compare_asc_lex(const void *stvr1,const void *stvr2){
	return strcmp(((STVR *)stvr1)->plex, ((STVR *)stvr2)->plex);
}




/*
PURPOSE:          Compare 2 lexemes when sorting in descending order.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: strcmp
                  
PARAMETERS:       const void *stvr1 - Pointer to first lexeme.
                  const void *stvr2 - Pointer to second lexeme.
                  
RETURN VALUE:     <0 stvr1 is larger than stvr2 (stvr2 would appear first in a dictionary).
                   0 stvr1 is equal to stvr2.
                  >0 stvr1 is less than stvr2 (stvr1 would appear first in a dictionary).
                  
ALGORITHM:        This comparator is used for the standard c function qsort().
*/
int st_sort_compare_desc_lex(const void *stvr1,const void *stvr2){
	return strcmp(((STVR *)stvr2)->plex, ((STVR *)stvr1)->plex);
}




/*
PURPOSE:          Sort the lexemes in the character buffer to match the order which
                  they appear in in the symbol table.

AUTHOR:           Mark Kaganovsky
VERSION:          1.3

CALLED FUNCTIONS: b_incfactor
                  b_mode
                  b_create
                  b_capacity
                  b_addc
                  b_free
                  b_reset
                  b_setmark
                  b_size
                  
PARAMETERS:       STD *sym_table - The symbol table to sort the lexemes for.
                  
RETURN VALUE:     SUCCESS:  0, The lexemes in sym_table.plsBD are now in the
                               same order as the symbol table records in
                               sym_table.pstvr
                  FAILURE: -1, The new temporary buffer could not be created.
                               In this case, the original buffer is untouched.

ALGORITHM:        1. A new temporary buffer is created, this buffer has the same
                     properties as the buffer of the symbol table passed.

                  2. Going through every element in the symbol record array, the
                     lexeme (STVR.plex) is copied into the new temporary buffer.

                  3. The new temporary buffer is now a sorted version of the char
                     buffer (sym_table.plsBD).

                  4. The new temporary buffer is now copied into sym_table.plsBD,
                     the lexeme pointers in the symbol record array (STVR.plex)
                     are adjusted as well.

                  Runtime speed is: O(n) - One loop to copy strings into new sorted
                                           buffer, and one loop to copy the sorted
                                           buffer into sym_table.plsBD

                  Memory usage is   O(n) - New buffer needs to be created.
*/
int st_reorganize_lexemes(STD *sym_table){
	Buffer *tempSortedBuffer; /* Temporary buffer to hold sorted version of sym_table->plsBD */
	char    incFactorArg;     /* Increment factor of sym_table->plsBD, to be passed to b_create(). */
	char    mode;             /* Resize mode of sym_table->plsBD, to be passed to b_create(). */

	int     i;
	
	/* Get the buffer increment factor. */
	if (b_incfactor(sym_table->plsBD) == 256){
		return -1;
	}
	incFactorArg = (char)b_incfactor(sym_table->plsBD);

	/* Get the buffer mode. */
	switch (b_mode(sym_table->plsBD)){
		case B_MODE_ADDITIVE:
			mode = B_MODE_ADDITIVE_ARG;
			break;
		case B_MODE_MULTIPLICATIVE:
			mode = B_MODE_MULTIPLICATIVE_ARG;
			break;
		case B_MODE_FIXED_SIZE:
			mode = B_MODE_FIXED_SIZE_ARG;
			break;
		default:
			return -1;
	}

	/* Create a new buffer. */
	tempSortedBuffer = b_create(b_capacity(sym_table->plsBD), incFactorArg, mode);
	if (!tempSortedBuffer){
		return -1;
	}

	/* Add a single character to force the new buffer to allocate memory. */
	if (!b_addc(tempSortedBuffer,'a')){
		b_free(tempSortedBuffer);
		return -1;
	}
	b_reset(tempSortedBuffer);

	/* No need to check return values beyond this point, buffers are the same size. */

	/* Run through every symbol table record, copying its lexeme into the new buffer. */
	for (i=0; i < sym_table->st_offset; ++i){
		char   *oldLexeme;
		oldLexeme = sym_table->pstvr[i].plex;

		/* Copy lexeme into new buffer. */
		for (; *oldLexeme; ++oldLexeme){
			b_addc(tempSortedBuffer,*oldLexeme);
		}

		/* Terminate the lexeme. */
		b_addc(tempSortedBuffer, '\0');
	}

	b_reset(sym_table->plsBD);

	/* Copy the new sorted buffer back into the original character buffer. Adjusting pointers as needed. */
	for (i=0; i < sym_table->st_offset; ++i){
		char c;

		/* Point to start of lexeme. */
		sym_table->pstvr[i].plex = b_setmark(sym_table->plsBD, b_size(sym_table->plsBD));

		/* Copy lexeme from new buffer into old buffer. */
		for (c=b_getc(tempSortedBuffer);    c != '\0';    c=b_getc(tempSortedBuffer)){
			b_addc(sym_table->plsBD, c);
		}

		/* Terminate lexeme. */
		b_addc(sym_table->plsBD, '\0');
	}

	b_free(tempSortedBuffer);

	return 0;
}
