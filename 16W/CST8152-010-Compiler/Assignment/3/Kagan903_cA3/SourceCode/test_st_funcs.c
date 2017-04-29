/*
File Name:     test_st_funcs.c
Compiler:      MS Visual Studio 2013
Author:        Mark Kaganovsky, 040789903
Course:        CST 8152 - Compilers, Lab Section 012
Assignment:    3
Date:          30 March 2016
Professor:     Sv. Ranev
Purpose:       Test the interface functions of the symbol table. 

Function List: main
               printSymbolTableDetailed
*/

#include <stdio.h>
#include <stdlib.h> /* Constants for calls to exit()*/

#include "buffer.h"
#include "stable.h" /* Do not remove this line. SiR */
#include "stable.h" /* Do not remove this line. SiR */




/* Function prototypes. */
static void printSymbolTableDetailed(void);




/* Global objects - variables */
static Buffer *sc_buf;    /* For linking to succeed. */
Buffer        *str_LTBL;  /* For linking to succeed. */
int            scerrnum;  /* For linking to succeed. */

STD            sym_table; /* Symbol Table Descriptor */




/*
PURPOSE:          Manually fill a symbol table with symbol table records and test
                  various functions.

AUTHOR:           Mark Kaganovsky
VERSION:          1.2

CALLED FUNCTIONS: puts
                  st_destroy
                  st_get_type
                  st_install
                  st_lookup
                  st_print
                  st_sort
                  st_store
                  st_update_type
                  st_update_value
                  exit
                  printSymbolTableDetailed
                  
PARAMETERS:       none
                  
RETURN VALUE:     SUCCESS: 0, tests suceeded.
                  FAILURE: 1, One or more tests failed.

ALGORITHM:        none
*/
int main(void){
	int testsSucceeded = 0; /* Return value for main. 0 if the tests succeeded, 1 if one or more tests failed. */

	InitialValue i_value;   /* For st_update_value */

	char *lexeme0 = "int1";
	char *lexeme1 = "int2";
	char *lexeme2 = "float1";
	char *lexeme3 = "float2";
	char *lexeme4 = "str1#";
	const int numlexemes = 5;

	puts("--------IMPORTANT--------\n"
	     "  These tests will only display something if the test fails.\n"
	     "  If nothing is displayed then the test has succeeded.\n\n");

	/* Test all functions with an invalid symbol table. */
	puts("Testing invalid symbol table:");
	sym_table.st_size = 0;

	st_destroy(sym_table); /* Check for crash. */

	if (st_get_type(sym_table,0) != -2){
		puts("FAIL: st_get_type"); testsSucceeded = 1;
	}
	if (st_install(sym_table,"test", STVR_TYPE_INTEGER, 0) != -1){
		puts("FAIL: st_install"); testsSucceeded = 1;
	}
	if (st_lookup(sym_table,"test") != -2){
		puts("FAIL: st_lookup"); testsSucceeded = 1;
	}
	if (st_print(sym_table) != -1){
		puts("FAIL: st_print"); testsSucceeded = 1;
	}
	if (st_sort(sym_table, ST_SORT_LEX_ASC) != -1){
		puts("FAIL: st_sort"); testsSucceeded = 1;
	}
	if (st_store(sym_table) != -2){
		puts("FAIL: st_store"); testsSucceeded = 1;
	}
	if (st_update_type(sym_table, 0, STVR_TYPE_FLOAT) != -2 ){
		puts("FAIL: st_update_type"); testsSucceeded = 1;
	}
	i_value.fpl_val = 0.0f;
	if (st_update_value(sym_table, 0, i_value) != -2){
		puts("FAIL: st_update_value"); testsSucceeded = 1;
	}
	puts("\n\n");

	/* Create symbol table */
	puts("Filling up symbol table:");
	sym_table = st_create(numlexemes);

	if (0 == sym_table.st_size){
		puts("ERROR: Could not create symbol table.");
		testsSucceeded = 1;
		exit(testsSucceeded);
	}

	/* Install lexemes */
	st_install(sym_table, lexeme0, STVR_TYPE_INTEGER, 0);
	st_install(sym_table, lexeme1, STVR_TYPE_INTEGER, 1);
	st_install(sym_table, lexeme2, STVR_TYPE_FLOAT, 2);
	st_install(sym_table, lexeme3, STVR_TYPE_FLOAT, 3);
	st_install(sym_table, lexeme4, STVR_TYPE_STRING, 4);

	if (sym_table.st_offset != numlexemes){
		puts("ERROR: Could not install one of the lexemes.");
		testsSucceeded = 1;
		st_destroy(sym_table);
		exit(testsSucceeded);
	}
	puts("Symbol table after installing symbols:");
	printSymbolTableDetailed();

	/* Testing updating types */
	puts("Testing type updating:");
	if (st_update_type(sym_table,0,STVR_TYPE_STRING) == 0){
		puts("0: FAIL: int -> string succeeded."); testsSucceeded = 1;
	}
	if (st_update_type(sym_table,1,STVR_TYPE_FLOAT) != 1){
		puts("1: FAIL: int -> float failed."); testsSucceeded = 1;
	}
	if (st_update_type(sym_table,2,STVR_TYPE_STRING) == 2){
		puts("2: FAIL: float -> string succeeded."); testsSucceeded = 1;
	}
	if (st_update_type(sym_table,3,STVR_TYPE_INTEGER) != 3){
		puts("3: FAIL: float -> int failed."); testsSucceeded = 1;
	}
	if (st_update_type(sym_table,4,STVR_TYPE_INTEGER) == 4){
		puts("4: FAIL: string -> int succeeded."); testsSucceeded = 1;
	}
	puts("\n\n");

	/* Test updating a type more than once. */
	puts("Testing updating type more than once:");
	if (st_update_type(sym_table,1,STVR_TYPE_INTEGER) == 1){
		puts("1: FAIL: int -> float -> int succeeded."); testsSucceeded = 1;
	}
	puts("Symbol table after updating types:");
	printSymbolTableDetailed();

	/* Test invalid ranges. */
	puts("Testing invalid ranges:");
	if (st_update_type(sym_table,-1,STVR_TYPE_INTEGER) != -1){
		puts("FAIL: negative vid_offset succeeded"); testsSucceeded = 1;
	}
	if (st_update_type(sym_table,sym_table.st_offset,STVR_TYPE_INTEGER) != -1){
		puts("FAIL: st_offset succeeded"); testsSucceeded = 1;
	}
	puts("\n\n");

	/* Test update value. */
	puts("Testing update value:");
	
	i_value.int_val = 123;
	st_update_value(sym_table, 0, i_value);
	if (sym_table.pstvr[0].i_value.int_val != i_value.int_val){
		puts("0: FAIL: Update value failed."); testsSucceeded = 1;
	}

	i_value.fpl_val = 2.34f;
	st_update_value(sym_table, 2, i_value);
	if (sym_table.pstvr[2].i_value.fpl_val != i_value.fpl_val){
		puts("2: FAIL: Update value failed."); testsSucceeded = 1;
	}

	i_value.str_offset = 789;
	st_update_value(sym_table, 4, i_value);
	if (sym_table.pstvr[4].i_value.str_offset != i_value.str_offset){
		puts("4: FAIL: Update value failed."); testsSucceeded = 1;
	}
	puts("\n\n");

	st_destroy(sym_table);
	return (testsSucceeded);
}




/*
PURPOSE:          Print out the symbol table to the standard output in the following format:
                      LINE    PLEX    STATUS_FIELD

AUTHOR:           Mark Kaganovsky
VERSION:          1.1
CALLED FUNCTIONS: printf
                  puts

PARAMETERS:       none
RETURN VALUE:     none
ALGORITHM:        none
*/
void printSymbolTableDetailed(void){
	int i;

	printf("%4s  %8s  STATUS_FIELD\n", "LINE", "PLEX");
	for (i = 0; i < sym_table.st_offset; ++i){
		STVR *stvr;
		stvr = &sym_table.pstvr[i];

		printf("%4d  %8s  %X\n", stvr->o_line, stvr->plex, stvr->status_field);
	}

	puts("\n\n");
}
