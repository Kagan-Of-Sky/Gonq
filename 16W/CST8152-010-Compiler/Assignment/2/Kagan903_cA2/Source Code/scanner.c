/* File Name:     scanner.c
 * Compiler:      MS Visual Studio 2013
 * Author:        Mark Kaganovsky, 040789903
 * Course:        CST 8152 - Compilers, Lab Section 012
 * Assignment:    2
 * Date:          March 8 2016
 * Professor:     Sv. Ranev
 * 
 * Purpose:       Convert the source code of a PLATYPUS program which is stored
 *                in a buffer into a stream of tokens.
 * 
 * Function List: scanner_init
 *                malar_next_token
 *                get_next_state
 *                char_class
 *                aa_func02
 *                aa_func03
 *                aa_func05
 *                aa_func08
 *                aa_func11
 *                aa_func12
 *                atool
 *                atodl
 *                asciiToDouble
 *                iskeyword
 *                countConsumeNewLine
 */




#define _CRT_SECURE_NO_WARNINGS




#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/*#define NDEBUG        to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */
#include "buffer.h"
#include "token.h"
#include "table.h"




#define DEBUG  /* for conditional processing */
#undef  DEBUG




/* Global objects - variables */
extern Buffer *str_LTBL; /* String literal table, defined in platy_st.c */
int            line;     /* current line number of the source code */
extern int     scerrnum; /* defined in platy_st.c - run-time error number */

/* Local(file) global objects - variables */
static Buffer *lex_buf; /* pointer to temporary lexeme buffer */

/* No other global variable declarations/definitions are allowed */




/* scanner.c static(local) function  prototypes */ 
static int  char_class(char c);               /* character class function */
static int  get_next_state(int, char, int *); /* state machine function */
static int  iskeyword(char * kw_lexeme);      /* keywords lookup functuion */
static long atool(char * lexeme);             /* converts octal string to decimal value */

/* My functions. */
static int    countConsumeNewLine (Buffer *sc_buf, unsigned char c);
static long   atodl               (char *lexeme);
static double asciiToDouble       (char *lexeme);




/* PURPOSE:          Initialize the scanner.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: b_isempty
 *                   b_setmark
 *                   b_retract_to_mark
 *                   b_reset
 * 
 * PARAMETERS:       Buffer * sc_buf - A scanner containing the program source code.
 * 
 * RETURN VALUE:     SUCCESS: EXIT_SUCCESS
 *                   FAILURE: EXIT_FAILURE
 * 
 * ALGORITHM:        none
 */
int scanner_init(Buffer * sc_buf) {
  	if(b_isempty(sc_buf)) return EXIT_FAILURE;/*1*/
	/* in case the buffer has been read previously  */
	b_setmark(sc_buf, 0);
	b_retract_to_mark(sc_buf);
	b_reset(str_LTBL);
	line = 1;
	return EXIT_SUCCESS;/*0*/
/*   scerrnum = 0;  *//*no need - global ANSI C */
}




/* PURPOSE:          Read through the buffer pointed to by sc_buf and extract tokens from it.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.7
 * 
 * CALLED FUNCTIONS: b_getc
 *                   isspace
 *                   b_retract
 *                   b_setmark
 *                   b_getcoffset
 *                   b_retract_to_mark
 *                   b_addc
 *                   countConsumeNewLine
 *                   isalnum
 *                   get_next_state
 *                   b_create
 *                   b_free
 *                   The set of functions in the aa_table array.
 * 
 * PARAMETERS:       Buffer * sc_buf - A pointer to a buffer to recognize tokens from.
 * 
 * RETURN VALUE:     A Token struct representing the token found.
 * 
 * ALGORITHM:        The first half of this function uses token driving processing to identify
 *                   many of the symbols in the language (comma, whitespace, brackets, etc.).
 *                   Note that .AND. and .OR. are processed here in the first half, not in the
 *                   state machine.
 *                   
 *                   The second half uses finite automata, it processes all variable identifiers,
 *                   keywords, literal numbers (octal and decimal, as well as floating point)
 *                   and string literals.
 */
Token malar_next_token(Buffer * sc_buf) {
	unsigned char c;      /* input symbol */

	Token  t;              /* token to return after recognition */
	int    state  = 0;     /* initial state of the FSM */
	int    accept = NOAS;  /* type of state - initially not accepting */
	/*short  lexstart;*/       /* start offset of a lexeme in the input buffer */
	/*short  lexend;*/         /* end offset of a lexeme in the input buffer */

	/* DECLARE YOUR VARIABLES HERE IF NEEDED */
	int i              = 0; /* Generic int. */
	short stringLength = 0; /* Length of a string. */

	while (1){ /* endless loop broken by token returns it will generate a warning */
		c = b_getc(sc_buf);

		/* End of source encountered. */
		if (SEOF(c)){
			t.code = SEOF_T;
			return t;
		}

		/* Check if whitespace. */
		else if (isspace(c)){
			countConsumeNewLine(sc_buf, c);
			continue;
		}

		switch (c){
			/* Brackets. */
			case '{': {
				t.code = LBR_T;
				return t;
			}
			case '}': {
				t.code = RBR_T;
				return t;
			}
			case '(': {
				t.code = LPR_T;
				return t;
			}
			case ')': {
				t.code = RPR_T;
				return t;
			}
			
			/* End of statement. */
			case ';': {
				t.code = EOS_T;
				return t;
			}
			
			/* Arithmetic operators. */
			case '+': {
				t.code = ART_OP_T;
				t.attribute.arr_op = PLUS;
				return t;
			}
			case '-': {
				t.code = ART_OP_T;
				t.attribute.arr_op = MINUS;
				return t;
			}
			case '*': {
				t.code = ART_OP_T;
				t.attribute.arr_op = MULT;
				return t;
			}
			case '/': {
				t.code = ART_OP_T;
				t.attribute.arr_op = DIV;
				return t;
			}
			
			/* Comma. */
			case ',': {
				t.code = COM_T;
				return t;
			}
			
			/* Relational operators, assignment operators, and concatenation operators. */
			case '=': { /* Either equality or assigment operator. */
				c = b_getc(sc_buf);

				if ('=' == c){ /* Equality operator. */
					t.code = REL_OP_T;
					t.attribute.rel_op = EQ;
				}
				else{ /* Assignment operator. */
					t.code = ASS_OP_T;
					b_retract(sc_buf);
				}

				return t;
			}
			case '>': { /* The greater than operator. */
				t.code = REL_OP_T;
				t.attribute.rel_op = GT;
				return t;
			}
			case '<': { /* Either the less than operator (<), the not equal operator (<>), or the string append operator (<<) */
				c = b_getc(sc_buf);

				/* Determine whether this token is a not equal, string concatenation, or less than operator. */
				switch (c){
					/* Not equal to '<>' operator. */
					case '>': {
						t.code = REL_OP_T;
						t.attribute.rel_op = NE;
						break;
					}
					/* String concatenation operator '<<'. */
					case '<': {
						t.code = SCC_OP_T;
						break;
					}
					/* Less than '<' operator. */
					default: {
						t.code = REL_OP_T;
						t.attribute.rel_op = LT;
						b_retract(sc_buf);
						break;
					}
				}

				return t;
			}
			
			/* '.AND.' and '.OR.' */
			case '.': {
				/* Set the mark in case we need to retract back to it. */
				b_setmark(sc_buf, b_getcoffset(sc_buf));

				c = b_getc(sc_buf);

				if ('A' == c){ /* Possibly .AND. */
					if ('N' == b_getc(sc_buf)){
						if ('D' == b_getc(sc_buf)){
							if ('.' == b_getc(sc_buf)){ /* Succesfully matched ".AND." */
								t.code = LOG_OP_T;
								t.attribute.log_op = AND;
								return t;
							}
						}
					}
				}
				else if ('O' == c){ /* Possibly .OR. */
					if ('R' == b_getc(sc_buf)){
						if ('.' == b_getc(sc_buf)){ /* Succesfully matched ".OR." */
							t.code = LOG_OP_T;
							t.attribute.log_op = OR;
							return t;
						}
					}
				}

				/* Invalid Token. */
				b_retract_to_mark(sc_buf);

				t.code = ERR_T;
				t.attribute.err_lex[0] = '.';
				t.attribute.err_lex[1] = '\0';

				return t;
			}
			
			/* Comments. */
			case '!': {
				c = b_getc(sc_buf);
				if (SEOF(c)){ /* A single exlamation mark at the end of the file. */
					t.code = ERR_T;
					t.attribute.err_lex[0] = '!';
					t.attribute.err_lex[1] = '\0';
					return t;
				}

				t.code = !ERR_T; /* This is done so that later we know if we need to return the token or continue the loop. */

				/* Check if the '!' is followed by an invalid character. */
				if ('<' != c){
					t.code = ERR_T;
					t.attribute.err_lex[0] = '!';
					t.attribute.err_lex[1] = c;
					t.attribute.err_lex[2] = '\0';
				}

				/* Regardless of whether the comment is valid or not, skip the rest of it. */
				while (!SEOF(c) && !countConsumeNewLine(sc_buf, c)){
					c = b_getc(sc_buf);
				}

				/* Invalid comment, return error token. */
				if (ERR_T == t.code){
					return t;
				}

				/* Valid comment, simply continue the loop. */
				continue;
			}
			
			/* String literal. */
			case '\"': {
				b_setmark(sc_buf, b_getcoffset(sc_buf)); /* Remember the beginning of the string. */

				/* Read the string until the closing double quote (") is encountered, or the end of source is reached. */
				for (stringLength=0, c=b_getc(sc_buf); '\"' != c && !SEOF(c); ++stringLength){
					countConsumeNewLine(sc_buf, c);
					c = b_getc(sc_buf);
				}

				/* Rewind to the beginning of the string. */
				b_retract_to_mark(sc_buf);

				if ('\"' == c){ /* Valid string. */
					t.code = STR_T;
					t.attribute.str_offset = b_size(str_LTBL);

					/* Store the string in the string literal table. */
					for (; stringLength; --stringLength){
						b_addc(str_LTBL, b_getc(sc_buf)); /* No need to check SEOF, string length is already known. */
					}

					/* Terminate the string. */
					b_addc(str_LTBL, '\0');

					/* Skip the last closing double quote ("). */
					b_getc(sc_buf); /* No need to check SEOF, it is known that this string is terminated by a '\"'. */
				}
				else{ /* Invalid string. */
					t.code = ERR_T;

					/* Retract one character back to include opening double quote ("). */
					b_retract(sc_buf);
					++stringLength;

					/* Try to store the first 20 characters in token's err_lex field. */
					for (i=0; i<ERR_LEN && i<stringLength; ++i){
						c = b_getc(sc_buf); /* No need to check SEOF, string length is already known. */
						t.attribute.err_lex[i] = c;
					}
					
					/* Append 3 dots if string was too long. */
					if (i<stringLength){
						i = ERR_LEN-3;
						t.attribute.err_lex[i] = '.';
						++i;
						t.attribute.err_lex[i] = '.';
						++i;
						t.attribute.err_lex[i] = '.';
						++i;
					}
					
					/* Terminate the string. */
					t.attribute.err_lex[i] = '\0';

					/* Skip the rest of the buffer. */
					while (!SEOF(b_getc(sc_buf))){
						/* No body. */
					}
				}

				return t;
			}
		}

		/* Make sure that this character is either a digit [0-9], or an alphabetic character [a-zA-Z] before entering the state machine. */
		if (!isalnum(c)){
			t.code = ERR_T;
			t.attribute.err_lex[0] = c;
			t.attribute.err_lex[1] = '\0';
			
			return t;
		}




		/****************************************************************************************
		 * Process state transition table below.
		 ****************************************************************************************/




		/* Remember start of lexeme. */
		b_setmark(sc_buf, b_getcoffset(sc_buf)-1);
		
		b_retract(sc_buf); /* Retract one character to the start of the lexeme. */

		/* Enter state machine. */
		while (NOAS == accept){
			c     = b_getc(sc_buf);
			state = get_next_state(state, c, &accept);
		}
		
		/* Check if the buffer needs to be retracted. */
		if (ASWR == accept){
			b_retract(sc_buf);
		}
		
		/* Get the length of the lexeme. */
		stringLength = b_getcoffset(sc_buf) - b_retract_to_mark(sc_buf);

		/* Create temporary buffer for the lexeme. */
		lex_buf = b_create(stringLength+1, 0, B_MODE_FIXED_SIZE_ARG); /* Allocate fixed buffer big enough to hold the lexeme + '\0'. */
		if (NULL == lex_buf){
			scerrnum = 1;
			return (*aa_table[ES])("RUN TIME ERROR:");
		}

		/* Copy lexeme into temporary buffer. */
		for (; stringLength; --stringLength){
			if (!b_addc(lex_buf, b_getc(sc_buf))){ /* No need to check return value of b_getc(), length is already known. */
				scerrnum = 1;
				return (*aa_table[ES])("RUN TIME ERROR:");
			}
		}
		
		/* Terminate the lexeme in the temporary buffer. */
		if (!b_addc(lex_buf, '\0')){
			scerrnum = 1;
			return (*aa_table[ES])("RUN TIME ERROR:");
		}

		/* Call the appropriate accepting function for this token. */
		t = (*aa_table[state])(b_setmark(lex_buf, 0));

		/* Free the temporary lexeme buffer. */
		b_free(lex_buf);

		return t;
	} /* end while(1) */
}




/* PURPOSE:          Returns the next state based on the current state and the character passed.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: char_class
 *                   printf - Only when DEBUG is defined.
 * 
 * PARAMETERS:       int state   - The current state.
 *                   char c      - The character to get the next state for.
 *                   int *accept - Stores whether this state is accepting or not
 *                                 Values: NOAS, ASWR, ASNR
 * 
 * RETURN VALUE:     Index of the next state in the transition table.
 * ALGORITHM:        none
 */
int get_next_state(int state, char c, int *accept){
	int col;
	int next;

	col  = char_class(c);
	next = st_table[state][col];
	
	#ifdef DEBUG
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state,col,next);
	#endif
	
	assert(next != IS);
	
	#ifdef DEBUG
		if(next == IS){
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state,col);
			exit(1);
		}
	#endif
	
	*accept = as_table[next];
	return next;
}




/* PURPOSE:          Determine the column index in the transition table for a character.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: isalpha()
 * 
 * PARAMETERS:       char c - The character to get the column index for.
 * 
 * RETURN VALUE:     The column index into the transition table.
 * 
 * ALGORITHM:        none
 */
int char_class (char c){
	int column;
	
	if(isalpha(c)){
		column = 0;
	}
	else{
		switch (c){
			case '0': {
				column = 1;
				break;
			}
			
			/* Octal digits [1-7] */
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7': {
				column = 2;
				break;
			}
			
			/* Decimal digits [8-9] */
			case '8':
			case '9': {
				column = 3;
				break;
			}
			
			case '.': {
				column = 4;
				break;
			}
			
			case '#': {
				column = 5;
				break;
			}
			
			default: {
				column = 6;
				break;
			}
		}
	}

	return column;
}




/* PURPOSE:          Accepting function for AVIDs (arithmetic variable identifiers) and keywords.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: iskeyword
 * 
 * PARAMETERS:       char *lexeme - The lexeme which represents either an AVID or keyword.
 *                   
 * RETURN VALUE:     A token representing either a keyword or an AVID.
 * ALGORITHM:        none
 */
Token aa_func02(char *lexeme){
	Token t;
	int   i; /* Generic integer. */
	
	i = iskeyword(lexeme);

	if (i == -1){ /* Lexeme is not a keyword. */
		t.code = AVID_T;

		/* Copy lexeme into token. */
		for (i=0; *lexeme && i < VID_LEN; ++i, ++lexeme){
			t.attribute.vid_lex[i] = *lexeme;
		}

		/* Terminate string. */
		t.attribute.vid_lex[i] = '\0';
	}
	else{ /* lexeme is a keyword. */
		t.code = KW_T;
		t.attribute.kwt_idx = i;
	}

	return t;
}




/* PURPOSE:          Accepting function for string variable identifiers.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: none
 * 
 * PARAMETERS:       char *lexeme - The lexeme to store into the SVID token.
 * 
 * RETURN VALUE:     A SVID token.
 * ALGORITHM:        none
 */
Token aa_func03(char *lexeme){
	Token t;
	int   i;
	
	t.code = SVID_T;
	
	/* Copy lexeme into token. */
	for (i=0; *lexeme && i < VID_LEN-1; ++i, ++lexeme){
		t.attribute.vid_lex[i] = *lexeme;
	}

	/* Check if '#' is present. */
	if (t.attribute.vid_lex[i-1] != '#'){
		t.attribute.vid_lex[i] = '#';
		++i;
	}

	/* Terminate string. */
	t.attribute.vid_lex[i] = '\0';

	return t;
}




/* PURPOSE:          Accepting function for the decimal literal
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.2
 * CALLED FUNCTIONS: atodl
 *                   The ES accepting function in the aa_table.
 * 
 * PARAMETERS:       char *lexeme - A base 10 lexeme to parse and turn into an integer.
 * 
 * RETURN VALUE:     A token representing either an error or an integer literal.
 * ALGORITHM:        none
 */
Token aa_func05(char *lexeme){
	Token t;
	long  val; /* Return value of atodl(). */

	val = atodl(lexeme);

	if (val == -1 || val > P_2BSI_MAX){ /* Out of range octal literal. */
		return (*aa_table[ES])(lexeme);
	}
	
	/* Valid decimal literal */
	t.code = INL_T;
	t.attribute.int_value = (int)val;

	return t;
}




/* PURPOSE:          Accepting function for the floating point literal.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.3
 * CALLED FUNCTIONS: asciiToDouble
 *                   The ES accepting function in the aa_table.
 * 
 * PARAMETERS:       char *lexeme - A lexeme representing a floating point literal.
 * 
 * RETURN VALUE:     A token representing either an error or a float.
 * ALGORITHM:        none
 */
Token aa_func08(char *lexeme){
	Token  t;
	double d;

	d = asciiToDouble(lexeme);

	/* Check if out of range for float. */
	if (d != 0.0 && (d > FLT_MAX || d < FLT_MIN)){
		return (*aa_table[ES])(lexeme);
	}

	/* Within float range. */
	t.code = FPL_T;
	t.attribute.flt_value = (float)d;

	return t;
}




/* PURPOSE:          Accepting function for the octal literal.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.1
 * CALLED FUNCTIONS: atool
 *                   The ES accepting function in the aa_table.
 * 
 * PARAMETERS:       char *lexeme - An octal string to turn into an integer literal.
 * 
 * RETURN VALUE:     A token representing either an error or integer literal.
 * ALGORITHM:        none
 */
Token aa_func11(char *lexeme){
	Token t;
	long  val; /* Return value of atool(). */

	val = atool(lexeme + 1);

	if (val == -1 || val > P_2BSI_MAX){ /* Out of range. */
		return (*aa_table[ES])(lexeme);
	}
	
	/* Valid number. */
	t.code = INL_T;
	t.attribute.int_value = (int)val;

	return t;
}




/* PURPOSE:          Accepting function for an error token.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 * 
 * PARAMETERS:       char *lexeme - The lexeme to store in the err_lex field of an error token.
 * 
 * RETURN VALUE:     An error token containing lexeme as the err_lex.
 * ALGORITHM:        none
 */
Token aa_func12(char *lexeme){
	Token t; /* Token to return. */
	int   i; /* Iterator. */

	t.code = ERR_T;
	
	/* Copy lexeme into error string. */
	for (i=0; *lexeme && i < ERR_LEN; ++i, ++lexeme){
		t.attribute.err_lex[i] = *lexeme;
	}

	/* Terminate the string. */
	t.attribute.err_lex[i] = '\0';
	
	return t;
}




/* PURPOSE:          Convert an ascii string representing an octal constant into a base 10 integer value.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 * 
 * PARAMETERS:       char *lexeme - A string representing an octal constant (must begin with '0').
 *                                  Example: "00", "01", etc.
 * 
 * RETURN VALUE:     SUCCESS: A positive long integer representing the octal string.
 *                   FAILURE: -1, The number is too large.
 *
 * ALGORITHM:        none
 */
long atool(char *lexeme){
	int i;        /* Loop counter. */
	long val = 0; /* Value to return. lexeme converted to an integer number. */
	
	/* Skip leading '0'. */
	for (; *lexeme; ++lexeme){
		/* Can not use bit shifting or multiplying by 8 because it could produce incorrect results.
		 * 
		 * Example: val = 671088640;    or 0x28000000 in hex
		 *          val <<= 3;          or val *= 8;
		 *          val is now 1073741824 or 0x40000000, an incorrect value but impossible to detect.
		 */
		
		/* Multiply by 8 (number doubles every time, thats why "i < 3"). */
		for(i=0; i<3; ++i){
			val += val;
			if (val < 0){ return -1; }
		}
		
		/* Add next digit. */
		val += *lexeme & 0x0F; /* Same as: val += *lexeme - '0' */
		if (val < 0){ return -1; }
	}
	
	return val;
}








/***********************************************************************************
 * MY EXTRA FUNCTIONS BELOW.
 **********************************************************************************/








/* PURPOSE:          Convert an ascii string representing a decimal constant into a base 10 integer value.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: none
 *                   
 * PARAMETERS:       char *lexeme - A string representing a decimal constant.
 *                                  Example: "0", "1", "123", etc.
 *                   
 * RETURN VALUE:     SUCCESS: A positive long integer representing the decimal string.
 *                   FAILURE: -1, The number is too large.
 *
 * ALGORITHM:        none
 */
long atodl(char *lexeme){
	int  i;      /* Generic int. */
	long oldval; /* Store old value of val. */
	long val;    /* Store the integer value of lexeme. */

	for (val=0; *lexeme; ++lexeme){
		/* Multiply by 10, or 2 * 5 */

		/* Multiply by 2. */
		val <<= 1;
		if (val < 0){ return -1; }
		
		/* Multiply by 5 or "val+val+val+val+val" (i < 4 because val already contains the first term). */
		oldval = val;
		for(i=0; i<4; ++i){
			val += oldval;
			if (val < 0){ return -1; }
		}
		
		/* Add next digit. */
		val += *lexeme & 0x0F; /* Same as: val += *lexeme - '0' */
		if (val < 0){ return -1; }
	}
	
	return val;
}




/* PURPOSE:          Convert an ascii string representing a float into a double.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.2
 * CALLED FUNCTIONS: none
 * 
 * PARAMETERS:       char *lexeme - A string representing a rational number.
 *                                  Example: "0.123", "328947.", "1.2"
 * 
 * RETURN VALUE:     The string converted into a double.
 * 
 * ALGORITHM:        Step 1: Convert the whole part into a double
 *                           Example: "123.456" gets converted into 123.0
 *                   Step 2: Convert the fractional part into a double.
 *                           Example: ".456" gets converted into 456
 *                   Step 3: Shift decimal point to correct position.
 *                           Example: 456 gets converted into 0.456
 *                   Step 4: Add the whole part and fractional part together.
 *                           Example: 123.0 + 0.456 = 123.456
 */
double asciiToDouble(char *lexeme){
	int    i;   /* Generic int. */
	double d;   /* Generic double. */
	double val; /* The value to return. */
	
	/* Convert the whole part (everything before the decimal point) to a double. */
	for(val=0.0; *lexeme != '.'; ++lexeme){
		/* Multiply by 10, or 2 * 5 */
		
		/* Multiply by 2. */
		val += val;
		if (val < 0){ return -1; }
		
		/* Multiply by 5 or "val+val+val+val+val" (i<4 because val already contains the first term). */
		d = val;
		for(i=0; i<4; ++i){
			val += d;
			if (val < 0){ return -1; }
		}
		
		/* Add next digit. */
		val += *lexeme & 0x0F; /* Same as: val += *lexeme - '0' */
		if (val < 0){ return -1; }
	}
	
	/* Skip the dot */
	++lexeme;
	
	/* Convert the fractional part into a whole integer.
	 * 
	 * Example: The fractional part of "999.12345" gets converted into 12345.0
	 * 
	 * i represents power and d is used to store the fractional part.
	 */
	for(d=0.0, i=0; *lexeme; ++lexeme, ++i){
		d *= 10.0;
		d += *lexeme & 0x0F;
	}
	
	/* Shift the decimal to the proper place. */
	for(; i; --i){
		d /= 10.0;
	}
	
	return val + d; /* Add the whole part and fraction part together. */
}


/* PURPOSE:          Determine whether the string passed to it is a keyword.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: strcmp()
 * PARAMETERS:       char *kw_lexeme - The string to check for whether it is a keyword or not.
 * 
 * RETURN VALUE:     SUCCESS: A number >= 0 representing the index which kw_lexeme resides in in the keyword table.
 *                   FAILURE: -1, kw_lexeme is not a keyword.
 * 
 * ALGORITHM:        Uses a binary search to search through the keyword table. kw_table strings must be
 *                   in ascending order (dictionary order). This search is case sensitive.
 *                   In the future when more keywords are added to the language this search can greatly speed up performance.
 */
int iskeyword(char *kw_lexeme){
	int lower;  /* Lower index into kw_table. */
	int middle; /* Current index into kw_table. */
	int upper;  /* Upper index into kw_table. */
	int ret;    /* Return value of strcmp(). */

	lower = 0;
	upper = KWT_SIZE-1;

	/* Binary search into the keyword table. */
	while(lower <= upper){
		middle = (lower + upper) >> 1;
		
		ret = strcmp(kw_lexeme, kw_table[middle]);
		
		if (ret < 0)      { upper = middle - 1; } /* Decrease the upper bound. */
		else if (ret > 0) { lower = middle + 1; } /* Increase the lower bound. */
		else              { return middle; }      /* Found keyword. */
	}

	/* Lexeme not found. */
	return -1;
}




/* PURPOSE:          Provides a platform-independant way of counting and consuming new lines.
 * AUTHOR:           Mark Kaganovsky
 * VERSION:          1.0
 * CALLED FUNCTIONS: b_getc()
 *                   b_retract()
 *
 * PARAMETERS:       Buffer *sc_buf  - A buffer to read a character from.
 *                   unsigned char c - The last character read from the above buffer.
 *
 * RETURN VALUE:     >0: The number of characters this newline was made up of.
 *                    0: No newline was encounterd.
 *
 * ALGORITHM:        Character passed is a '\n': global 'line' is incremented and the
 *                                               function returns.
 *                                               
 *                   Character passed is a '\r': global 'line' is incremented, then a single
 *                                               character is read from sc_buf. If that
 *                                               character is not a '\n' then the buffer
 *                                               is retracted.
 *
 *                   If the character passed is not a 'r' or a '\n', then this function
 *                   does absolutely nothing.
 *
 * WARNING:          This function does not check for sc_buf == NULL as it is local to this
 *                   file and should never even recieve a NULL argument.
 */
int countConsumeNewLine(Buffer *sc_buf, unsigned char c){
	switch (c){
		case '\n': {
			++line;
			return 1;
		}
	}

	/* Not a newline character. */
	return 0;
}
