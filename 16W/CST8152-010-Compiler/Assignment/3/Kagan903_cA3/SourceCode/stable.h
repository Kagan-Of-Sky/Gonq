/* 
File Name:     stable.h
Compiler:      MS Visual Studio 2013
Author:        Mark Kaganovsky, 040789903
Course:        CST 8152 - Compilers, Lab Section 012
Assignment:    3
Date:          March 30 2016
Professor:     Sv. Ranev
Purpose:       Interface for the symbol table.

Function List: st_create
               st_install
               st_lookup
               st_update_type
               st_update_value
               st_get_type
               st_destroy
               st_print
               st_store
               st_sort
*/

#ifndef STABLE_H_
#define STABLE_H_




#include "buffer.h"




/****************************************************************************************************
 Type Definitions and related macros/constants below
*****************************************************************************************************/

/* Union to hold initial values of symbol table records. */
typedef union InitialValue {
	int   int_val;    /* Integer variable initial value. */
	float fpl_val;    /* Floating-point variable initial value. */
	int   str_offset; /* String variable initial value. */
} InitialValue;




/* Describes a single VID record. */
typedef struct SymbolTableVidRecord {
	/*
	Variable record status field.

	Going from the MSB to the LSB:
		+ First 13 bits - Not used, reserved for future use. All bits set to 1 and stay at 1 in this implementation.
		+ Next 2 bits   - Data type indicator.
		+ Last bit      - Update flag. Indicates that the default data type of a variable has changed.
	*/
	unsigned short  status_field;

	/* Masks to extract the bit fields from the status field. */
		#define STVR_STATUS_MASK_RESERVED 0xFFF8 /* Mask to extract the reserved bits. */
		#define STVR_STATUS_MASK_TYPE     0x0006 /* Mask to extract the type bits. */
		#define STVR_STATUS_MASK_UPDATE   0x0001 /* Mask to extract the update bit. */

		#define STVR_STATUS_MASK_DEFAULT  0x0000 /* Mask for the default type. */
		#define STVR_STATUS_MASK_FLOAT    0x0002 /* Mask for the float type. */
		#define STVR_STATUS_MASK_INTEGER  0x0004 /* Mask for the integer type. */
		#define STVR_STATUS_MASK_STRING   0x0006 /* Mask for the string type. */

	/* Constants which are used as return values and parameters to functions like st_get_type() and st_update_type(). */
		#define STVR_TYPE_STRING  'S' /* String type. */
		#define STVR_TYPE_FLOAT   'F' /* Float type. */
		#define STVR_TYPE_INTEGER 'I' /* Integer type */

	char *plex;     /* Pointer to lexeme (VID name) in character array (CA). */
	int   o_line;   /* Line of first occurance. */

	InitialValue  i_value;  /* Variable initial value. */
	/* Initial values for different types. */
		#define STVR_INIT_VALUE_INTEGER 0    /* Initial value for integers. */
		#define STVR_INIT_VALUE_FLOAT   0.0f /* Initial value for floats. */
		#define STVR_INIT_VALUE_STRING  -1   /* Initial value for strings. */

	void *reserved; /* Reserved for future use. */
} STVR;




/* Links the database elements together and stores data about different parameters of the database. */
typedef struct SymbolTableDescriptor {
	STVR   *pstvr;     /* Pointer to array of STVR. */
	int     st_size;   /* Size in number of STVR elements. */
	int     st_offset; /* Offset in number of STVR elements. */
	Buffer *plsBD;     /* Pointer to the lexeme storage buffer (referred to as character array or CA). */
} STD;




/*
Check if a symbol table is a valid symbol table.
Evaluates to 1 if the symbol table's size is less than or equal to zero.
Otherwise evaluates to 0.
*/
#define IS_INVALID_STD(sym_table) ((sym_table).st_size <= 0  ?  1  :  0)




/****************************************************************************************************
 Function Prototypes below
*****************************************************************************************************/
STD  st_create(int size);

int  st_install(STD sym_table, char *lexeme, char type, int line);

int  st_lookup(STD sym_table, char *lexeme);

int  st_update_type(STD sym_table, int vid_offset, char v_type);

int  st_update_value(STD sym_table, int vid_offset, InitialValue i_value);

char st_get_type(STD sym_table, int vid_offset);

void st_destroy(STD sym_table);

int  st_print(STD sym_table);

int  st_store(STD sym_table);

#define ST_SORT_LEX_ASC  'A' /* Constant for st_sort, sort in ascending lexeme order ("aaa", "aab", etc.). */
#define ST_SORT_LEX_DESC 'D' /* Constant for st_sort, sort in descending lexeme order ("zzz", "zzy", etc.). */
int st_sort(STD sym_table, char s_order);




#endif
