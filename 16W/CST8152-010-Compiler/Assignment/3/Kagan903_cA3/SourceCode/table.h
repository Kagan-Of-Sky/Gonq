/* File Name:     table.h
 * Compiler:      MS Visual Studio 2013
 * Author:        Mark Kaganovsky, 040789903
 * Course:        CST 8152 - Compilers, Lab Section 012
 * Assignment:    2
 * Date:          March 8 2016
 * Professor:     Sv. Ranev
 * Purpose:       The transtion table as well as other data structures
 *                related to it are defined here (accepting state table,
 *                accepting function array, keyword table).
 * 
 * Function List: aa_func02
 *                aa_func03
 *                aa_func05
 *                aa_func08
 *                aa_func11
 *                aa_func12
 */

#ifndef  TABLE_H_
#define  TABLE_H_ 




#ifndef BUFFER_H_
	#include "buffer.h"
#endif

#ifndef NULL
	#include <_null.h> /* NULL pointer constant is defined there */
#endif




/* Source end-of-file (SEOF) sentinel symbol: '\0' or only one of the folowing constants: 255, 0xFF , EOF */
#define    SEOF(c)    ('\0' == (c) || EOF == (char)(c))








/* Single-lexeme tokens processed separately one by one
 * in the token-driven part of the scanner:
 * 
 * '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' ,
 *        ^
 *        |
 *      space
 * 
 * !<comment , ',' , '"' , ';' , '-' , '+' , '*' , '/', << ,
 * .AND., .OR. , SEOF, 'wrong symbol'
 */

#define    ES    12    /* Error state */
#define    IS    -1    /* Invalid state */

#define    TABLE_ROWS       14    /* Number of rows in the transition table. */
#define    TABLE_COLUMNS    7     /* Number of columns in the transition table. */

/* Transition table - type of states defined in separate table */
int  st_table[TABLE_ROWS][TABLE_COLUMNS] = {
	/*  a-zA-Z   0     1-7    8-9     .      #    other  */

	{     1,     6,     4,     4,    IS,    IS,    IS    },    /* State 0  - NOAS */
	{     1,     1,     1,     1,     2,     3,     2    },    /* State 1  - NOAS */
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 2  - AVID/KW */
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 3  - SVID */
	{    ES,     4,     4,     4,     7,     5,     5    },    /* State 4  - NOAS */
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 5  - DIL */

	{    ES,    10,     9,    ES,     7,    ES,     5    },    /* State 6  - NOAS */
	{     8,     7,     7,     7,     8,     8,     8    },    /* State 7  - NOAS */

	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 8  - FPL */

	{    ES,     9,     9,    ES,    ES,    ES,    11    },    /* State 9  - NOAS */
	{    ES,    ES,    ES,    ES,    11,    ES,    11    },    /* State 10 - NOAS */

	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 11 - OIL */
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    },    /* State 12 - ES */
	{    IS,    IS,    IS,    IS,    IS,    IS,    IS    }     /* State 13 - ESWR */
};








/* Accepting state table definition */
#define    ASWR    1    /* Accepting state with retract */
#define    ASNR    2    /* Accepting state with no retract */
#define    NOAS    3    /* Not accepting state */

int as_table[TABLE_ROWS] = {
	NOAS,
	NOAS,
	ASWR,
	ASNR,
	NOAS,
	ASWR,
	NOAS,
	NOAS,
	ASWR,
	NOAS,
	NOAS,
	ASWR,
	ASNR,
	ASWR
};








/* Accepting action function declarations */
Token aa_func02(char *lexeme);
Token aa_func03(char *lexeme);
Token aa_func05(char *lexeme);
Token aa_func08(char *lexeme);
Token aa_func11(char *lexeme);
Token aa_func12(char *lexeme);

/* defining a new type: pointer to function (of one char * argument) returning Token */  
typedef Token (*PTR_AAF)(char *lexeme);

/* Accepting function (action) callback table (array) definition */
PTR_AAF aa_table[TABLE_ROWS] = {
	NULL,
	NULL,
	aa_func02,
	aa_func03,
	NULL,
	aa_func05,
	NULL,
	NULL,
	aa_func08,
	NULL,
	NULL,
	aa_func11,
	aa_func12,
	NULL
};








/* Keyword lookup table (.AND. and .OR. are not keywords)
 * 
 * Keep this table alphabetical since iskeyword() uses a binary search.
 */
#define KWT_SIZE 8

char * kw_table[] = {
	"ELSE",
	"IF",
	"INPUT",
	"OUTPUT",
	"PLATYPUS",
	"REPEAT",
	"THEN",
	"USING"
};




/* Other constants. */
#define  P_2BSI_MAX  32767  /* Platypus_2_Byte_Signed_Integer_Max */




#endif
