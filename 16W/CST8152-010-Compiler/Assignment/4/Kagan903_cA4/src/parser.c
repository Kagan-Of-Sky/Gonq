/* File Name:     parser.c
 * Compiler:      MS Visual Studio 2013
 * Author:        Mark Kaganovsky, 040789903
 * Course:        CST 8152 - Compilers, Lab Section 012
 * Assignment:    4
 * Date:          April 22 2016
 * Professor:     Sv. Ranev
 * Purpose:       Implementation of the parser.
 * 
 * Function List: parser  match  syn_printe  syn_eh  gen_incode
 *                
 *                program  opt_statements  statements  statement  statements_p
 *                
 *                assignment_statement  assignment_expression  selection_statement  iteration_statement
 *                input_statement  output_statement
 *                
 *                arithmetic_expression  unary_arithmetic_expression  additive_arithmetic_expression
 *                additive_arithmetic_expression_p  multiplicative_arithmetic_expression  multiplicative_arithmetic_expression_p
 *                primary_arithmetic_expression
 *                
 *                string_expression  string_expression_p  primary_string_expression
 *                
 *                conditional_expression  logical_or_expression  logical_or_expression_p
 *                logical_and_expression  logical_and_expression_p  relational_expression  comparison_operator
 *                primary_a_relational_expression  primary_s_relational_expression
 *                
 *                variable_list  variable_list_p  variable_identifier  output_list
 */
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"




/*
PURPOSE:          Starting point for the parser.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: malar_next_token , program , match , gen_incode
PARAMETERS:       Buffer *in_buf - Source code buffer which will be passed to the scanner.
*/
void parser(Buffer *in_buf){
	sc_buf = in_buf;
	lookahead = malar_next_token(sc_buf);
	program(); match(SEOF_T, NO_ATTR);
	gen_incode("PLATY: Source file parsed");
}




/*
PURPOSE:          Matches the lookahead token and the token required by the parser.
                  The token requires is represented by pr_token_code and pr_token_attribute.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: syn_eh , malar_next_token , syn_printe
                  
PARAMETERS:       int pr_token_code ------ Token code to match.
                  int pr_token_attribute - Token attribute to match. Only used if pr_token_code is one of the following:
                                           KW_T    LOG_OP_T    ART_OP_T    REL_OP_T
                  
ALGORITHM:        If the pr_token_code and lookahead.code match, then the pr_token_code is checked against
                  lookahead.attribute.get_int if needed. If a mismatch occurs then syn_eh is called with the pr_token_code.
                  If the pr_token_code is SEOF_T and lookahead.attribute.get_int matches this function returns.
                  After the match is made, the lookahead is advanced, if the new lookahead is an error token, then syn_printe
                  is called, synerrno is incremented, and the lookahead is advanced once more before returning.
*/
void match(int pr_token_code,int pr_token_attribute){
	/* Try to match token code, most of the time this match will be succesful. */
	if (lookahead.code == pr_token_code){
		/* Check if the token code is one which has an attribute associated with it. */
		switch (pr_token_code){
			case KW_T:
			case LOG_OP_T:
			case ART_OP_T:
			case REL_OP_T:
				if (lookahead.attribute.get_int != pr_token_attribute){
					syn_eh(pr_token_code);
					return;
				}
				break;

			case SEOF_T:
				return;
		}

		/* Advance lookahead. */
		lookahead = malar_next_token(sc_buf);

		/* Error token. */
		if (ERR_T == lookahead.code){
			syn_printe();
			++synerrno;
			lookahead = malar_next_token(sc_buf);
		}
		return;
	}
	/* lookahead token code did not match. */
	syn_eh(pr_token_code);
}




/*
PURPOSE:          Parser error printing function, Assignmet 4, W15
AUTHOR:           Svillen Ranev
VERSION:          1.0 ?
CALLED FUNCTIONS: printf
*/
void syn_printe(void){
	Token t = lookahead;
	
	printf("PLATY: Syntax error:  Line:%3d\n", line);
	printf("*****  Token code:%3d Attribute: ", t.code);

	switch(t.code){
		case ERR_T: /* ERR_T     0   Error token */
			printf("%s\n", t.attribute.err_lex);
			break;
		case SEOF_T: /*SEOF_T    1   Source end-of-file token */
			printf("NA\n" );
			break;
		case AVID_T: /* AVID_T    2   Arithmetic Variable identifier token */
		case SVID_T :/* SVID_T    3  String Variable identifier token */
			printf("%s\n", sym_table.pstvr[t.attribute.get_int].plex);
			break;
		case FPL_T: /* FPL_T     4  Floating point literal token */
			printf("%5.1f\n",t.attribute.flt_value);
			break;
		case INL_T: /* INL_T      5   Integer literal token */
			printf("%d\n",t.attribute.get_int);
			break;
		case STR_T: /* STR_T     6   String literal token */
			printf("%s\n", b_setmark(str_LTBL, t.attribute.str_offset));
			break;
		case SCC_OP_T: /* 7   String concatenation operator token */
			printf("NA\n" );
			break;
		case ASS_OP_T:/* ASS_OP_T  8   Assignment operator token */
			printf("NA\n" );
			break;
		case ART_OP_T:/* ART_OP_T  9   Arithmetic operator token */
			printf("%d\n",t.attribute.get_int);
			break;
		case REL_OP_T: /*REL_OP_T  10   Relational operator token */ 
			printf("%d\n",t.attribute.get_int);
			break;
		case LOG_OP_T:/*LOG_OP_T 11  Logical operator token */
			printf("%d\n",t.attribute.get_int);
			break;
		case LPR_T: /*LPR_T    12  Left parenthesis token */
			printf("NA\n" );
			break;
		case RPR_T: /*RPR_T    13  Right parenthesis token */
			printf("NA\n" );
			break;
		case LBR_T: /*    14   Left brace token */
			printf("NA\n" );
			break;
		case RBR_T: /*    15  Right brace token */
			printf("NA\n" );
			break;
		case KW_T: /*     16   Keyword token */
			printf("%s\n", kw_table [t.attribute.get_int]);
			break;
		case COM_T: /* 17   Comma token */
			printf("NA\n");
			break;
		case EOS_T: /*    18  End of statement *(semi - colon) */
			printf("NA\n" );
			break;
		default:
			printf("PLATY: Scanner error: invalid token code: %d\n", t.code);
	}
}




/*
PURPOSE:          Error handling function. Uses the simple "panic mode" error recovery.
AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: syn_printe , malar_next_token , exit
PARAMETERS:       int sync_token_code - The token code to synchronize on.
                  
ALGORITHM:        1. Prints out the error, increments error count.
                  2. Skips all input until a token with code 'sync_token_code' is found
                     If SEOF is encountered in this loop then this function calls exit().
                  3. If the 'sync_token_code' is not SEOF, then advance lookahead once more.
*/
void syn_eh(int sync_token_code){
	syn_printe();
	++synerrno;
	
	/* Eat tokens until a synchronizing token is found. YUM! */
	for (lookahead=malar_next_token(sc_buf); lookahead.code != sync_token_code; lookahead=malar_next_token(sc_buf)){
		if (SEOF_T == lookahead.code){
			exit(synerrno);
		}
	}
	/* Parser is now synchronized. */

	/* If the sync_token_code is not SEOF_T, advance the lookahead one more. */
	if (SEOF_T != sync_token_code){
		lookahead = malar_next_token(sc_buf);
	}
}




/*
PURPOSE:          Generate Intermediate Code.
                  In this implementation all it does is print its argument to stdout.

AUTHOR:           Mark Kaganovsky
VERSION:          1.0
CALLED FUNCTIONS: puts
PARAMETERS:       char *s - The string to print to stdout.
*/
void gen_incode(char *s){
	puts(s);
}




/****************************************************************************************************
 Production functions below.
*****************************************************************************************************/

/*
<program> -> PLATYPUS {<opt_statements>}

FIRST(<program>) = { PLATYPUS }
*/
void program(void){
	match(KW_T,KWI_PLATYPUS);  match(LBR_T, NO_ATTR);
		opt_statements();
	match(RBR_T, NO_ATTR);

	gen_incode("PLATY: Program parsed");
}




/*
<opt_statements> -> <statements> | E

FIRST(<opt_statements>) = {AVID_T , SVID_T , IF , USING , INPUT , OUTPUT , e}
*/
void opt_statements(void){
	switch (lookahead.code){
		case AVID_T:
		case SVID_T:
			statements();
			break;

		case KW_T:
			if (lookahead.attribute.kwt_idx != KWI_PLATYPUS &&
			    lookahead.attribute.kwt_idx != KWI_ELSE     &&
			    lookahead.attribute.kwt_idx != KWI_THEN     &&
			    lookahead.attribute.kwt_idx != KWI_REPEAT)
			{
				statements();
				break;
			}
		default:
			gen_incode("PLATY: Opt_statements parsed");
	}
}

/*
<statements> -> <statement> <statements'>

FIRST(<statements>) = {AVID_T , SVID_T , IF , USING , INPUT , OUTPUT}
*/
void statements(void){
	statement(); statements_p();
}

/*
<statement> ->
	  <assignment statement>
	| <selection statement>
	| <iteration statement>
	| <input statement>
	| <output statement>

FIRST(<statement>) = {AVID_T , SVID_T , IF , USING , INPUT , OUTPUT}
*/
void statement(void){
	switch (lookahead.code){
		case KW_T:
			switch (lookahead.attribute.kwt_idx){
				case KWI_IF:
					selection_statement();
					break;
				case KWI_USING:
					iteration_statement();
					break;
				case KWI_INPUT:
					input_statement();
					break;
				case KWI_OUTPUT:
					output_statement();
					break;
				default:
					syn_printe();
			}
			break;
		
		case AVID_T:
		case SVID_T:
			assignment_statement();
			break;
		
		default:
			syn_printe();
	}
}

/* 
<statements'> -> <statement> <statements'> | E

FIRST(<statements'>) = {AVID_T , SVID_T , IF , USING , INPUT , OUTPUT , e}
 */
void statements_p(void){
	switch (lookahead.code){
		case KW_T:
			switch (lookahead.attribute.kwt_idx){
				case KWI_IF:
				case KWI_USING:
				case KWI_INPUT:
				case KWI_OUTPUT:
					break;
				default:
					return;
			}
		case AVID_T:
		case SVID_T:
			statement();
			statements_p();
			break;
	}
}




/*
<assignment statement> -> <assignment expression> ;

FIRST(<assignment statement>) = {AVID_T , SVID_T}
*/
void assignment_statement(void){
	assignment_expression();  match(EOS_T,NO_ATTR);
	gen_incode("PLATY: Assignment statement parsed");
}

/*
<assignment expression> ->
	  AVID = <arithmetic expression>
	| SVID = <string expression>

FIRST(<assignment expression>) = {AVID_T , SVID_T}
*/
void assignment_expression(void){
	switch (lookahead.code){
		case AVID_T:
			match(AVID_T,NO_ATTR); match(ASS_OP_T,NO_ATTR); arithmetic_expression();
			gen_incode("PLATY: Assignment expression (arithmetic) parsed");
			break;
		case SVID_T:
			match(SVID_T,NO_ATTR); match(ASS_OP_T,NO_ATTR); string_expression();
			gen_incode("PLATY: Assignment expression (string) parsed");
			break;
		default:
			syn_printe();
	}
}




/*
<selection statement> ->
	IF (<conditional expression>) THEN
		<opt_statements>
	ELSE {
		<opt statements>
	};

FIRST(<selection statement>) = {IF}
*/
void selection_statement(void){
	match(KW_T,KWI_IF);  match(LPR_T,NO_ATTR);  conditional_expression();  match(RPR_T,NO_ATTR);  match(KW_T,KWI_THEN);
		opt_statements();
	match(KW_T,KWI_ELSE);  match(LBR_T,NO_ATTR);
		opt_statements();
	match(RBR_T,NO_ATTR);  match(EOS_T,NO_ATTR);

	gen_incode("PLATY: IF statement parsed");
}




/*
<iteration statement> ->
	USING (<assignment expression> , <conditional expression> , <assignment  expression>) REPEAT {
		<opt_statements>
	};

FIRST(<iteration statement>) = {USING}
*/
void iteration_statement(void){
	match(KW_T,KWI_USING); match(LPR_T,NO_ATTR);

	assignment_expression();  match(COM_T,NO_ATTR);
	conditional_expression(); match(COM_T,NO_ATTR);
	assignment_expression();  match(RPR_T,NO_ATTR);  match(KW_T,KWI_REPEAT);  match(LBR_T,NO_ATTR);
		opt_statements();
	match(RBR_T,NO_ATTR);  match(EOS_T,NO_ATTR);

	gen_incode("PLATY: USING statement parsed");
}




/*
<input statement> -> INPUT (<variable list>);

FIRST(<input statement>) = {INPUT}
*/
void input_statement(void){
	match(KW_T,KWI_INPUT);  match(LPR_T,NO_ATTR);  variable_list();  match(RPR_T,NO_ATTR);  match(EOS_T,NO_ATTR);
	gen_incode("PLATY: INPUT statement parsed");
}




/*
<output statement> -> OUTPUT(<output list>);

FIRST(<output statement>) = { OUTPUT }
*/
void output_statement(void){
	match(KW_T,KWI_OUTPUT);  match(LPR_T,NO_ATTR);  output_list();  match(RPR_T,NO_ATTR);  match(EOS_T, NO_ATTR);
	gen_incode("PLATY: OUTPUT statement parsed");
}




/*
<arithmetic expression> ->
	  <unary arithmetic expression>
	| <additive arithmetic expression>

FIRST(<arithmetic expression>) = { - , + , AVID_T , FPL_T , INL_T , ( }
*/
void arithmetic_expression(void){
	switch (lookahead.code){
		case AVID_T:
		case FPL_T:
		case INL_T:
		case LPR_T:
			additive_arithmetic_expression();
			break;
		
		case ART_OP_T:
			switch (lookahead.attribute.arr_op){
				case PLUS:
				case MINUS:
					unary_arithmetic_expression();
					break;
				default:
					syn_printe();
					return;
			}
			break;

		default:
			syn_printe();
			return;
	}
	gen_incode("PLATY: Arithmetic expression parsed");
}

/*
<unary arithmetic expression> ->
	  - <primary arithmetic expression>
	| + <primary arithmetic expression>

FIRST(<unary arithmetic expression>) = { - , + }
*/
void unary_arithmetic_expression(void){
	if (ART_OP_T==lookahead.code  &&  (MINUS==lookahead.attribute.arr_op || PLUS==lookahead.attribute.arr_op)){
		match(ART_OP_T, lookahead.attribute.arr_op);
		primary_arithmetic_expression();
		gen_incode("PLATY: Unary arithmetic expression parsed");
		return;
	}
	syn_printe();
}

/*
<additive arithmetic expression> -> <multiplicative arithmetic expression> <additive arithmetic expression'>

FIRST(<additive arithmetic expression>) = { AVID_T , FPL_T , INL_T , ( }
*/
void additive_arithmetic_expression(void){
	multiplicative_arithmetic_expression();  additive_arithmetic_expression_p();
}

/*
<additive arithmetic expression'> ->
	  + <multiplicative arithmetic expression> <additive arithmetic expression'>
	| - <multiplicative arithmetic expression> <additive arithmetic expression'>
	| e

FIRST(<additive arithmetic expression'>) = { + , - , e }
*/
void additive_arithmetic_expression_p(void){
	if (ART_OP_T==lookahead.code  &&  (MINUS==lookahead.attribute.arr_op || PLUS==lookahead.attribute.arr_op)){
		match(ART_OP_T,lookahead.attribute.arr_op);  multiplicative_arithmetic_expression();  additive_arithmetic_expression_p();
		gen_incode("PLATY: Additive arithmetic expression parsed");
	}
}

/*
<multiplicative arithmetic expression> -> <primary arithmetic expression> <multiplicative arithmetic expression'>

FIRST(<multiplicative arithmetic expression>) = { AVID_T , FPL_T , INL_T , ( }
*/
void multiplicative_arithmetic_expression(void){
	primary_arithmetic_expression();  multiplicative_arithmetic_expression_p();
}

/*
<multiplicative arithmetic expression'> ->
	  * <primary arithmetic expression> <multiplicative arithmetic expression'>
	| / <primary arithmetic expression> <multiplicative arithmetic expression'>
	| e

FIRST(<multiplicative arithmetic expression'>) = { * , / , e }
*/
void multiplicative_arithmetic_expression_p(void){
	if (ART_OP_T == lookahead.code && (MULT == lookahead.attribute.arr_op || DIV == lookahead.attribute.arr_op)){
		match(ART_OP_T,lookahead.attribute.arr_op);  primary_arithmetic_expression(); multiplicative_arithmetic_expression_p();
		gen_incode("PLATY: Multiplicative arithmetic expression parsed");
	}
}

/*
<primary arithmetic expression> ->
	  AVID_T
	| FPL_T
	| INL_T
	| (<arithmetic expression>)

FIRST(<primary arithmetic expression>) = { AVID_T , FPL_T , INL_T , ( }
*/
void primary_arithmetic_expression(void){
	switch (lookahead.code){
		case AVID_T:
		case FPL_T:
		case INL_T:
			match(lookahead.code, NO_ATTR);
			break;
		case LPR_T:
			match(LPR_T, NO_ATTR);  arithmetic_expression();  match(RPR_T, NO_ATTR);
			break;
		default:
			syn_printe();
			return;
	}
	gen_incode("PLATY: Primary arithmetic expression parsed");
}




/*
<string expression> -> <primary string expression> <string expression'>

FIRST(<string expression>) = {SVID_T , STR_T}
*/
void string_expression(void){
	primary_string_expression();  string_expression_p();
	gen_incode("PLATY: String expression parsed");
}

/*
<string expression'> ->
	  << <primary string expression> <string expression'>
	| e

FIRST(<string expression'>) = { << , e }
*/
void string_expression_p(void){
	if (SCC_OP_T == lookahead.code){
		match(SCC_OP_T, NO_ATTR);  primary_string_expression();  string_expression_p();
	}
}

/*
<primary string expression> ->
	  SVID_T
	| STR_T

FIRST(<primary string expression>) = { SVID_T , STR_T }
*/
void primary_string_expression(void){
	switch (lookahead.code){
		case SVID_T:
		case STR_T:
			match(lookahead.code, NO_ATTR);
			gen_incode("PLATY: Primary string expression parsed");
			break;
		default:
			syn_printe();
	}
}




/*
<conditional expression> -> <logical OR expression>

FIRST(<conditional expression>) = {AVID_T , FPL_T , INL_T , SVID_T , STR_T}
*/
void conditional_expression(void){
	logical_or_expression();
	gen_incode("PLATY: Conditional expression parsed");
}

/*
<logical OR expression> -> <logical AND expression> <logical OR expression'>

FIRST(<logical OR expression>) = {AVID_T , FPL_T , INL_T , SVID_T , STR_T}
*/
void logical_or_expression(void){
	logical_and_expression();  logical_or_expression_p();
}

/*
<logical OR expression'> ->
	  .OR. <logical AND expression> <logical OR expression'>
	| e

FIRST(<logical OR expression'>) = { .OR. , e }
*/
void logical_or_expression_p(void){
	if (LOG_OP_T == lookahead.code && OR == lookahead.attribute.log_op){
		match(LOG_OP_T,OR);  logical_and_expression();  logical_or_expression_p();
		gen_incode("PLATY: Logical OR expression parsed");
	}
}

/*
<logical AND expression> -> <relational expression> <logical AND expression'>

FIRST(<logical AND expression>) = {AVID_T , FPL_T , INL_T , SVID_T , STR_T}
*/
void logical_and_expression(void){
	relational_expression();  logical_and_expression_p();
}

/*
<logical AND expression'> ->
	  .AND. <relational expression> <logical AND expression'>
	| e

FIRST(<logical AND expression'>) = { .AND. , e }
*/
void logical_and_expression_p(void){
	if (LOG_OP_T == lookahead.code && AND == lookahead.attribute.log_op){
		match(LOG_OP_T, AND);  relational_expression();  logical_and_expression_p();
		gen_incode("PLATY: Logical AND expression parsed");
	}
}

/*
<relational expression> ->
	  <primary a_relational expression> <comparison operator> <primary a_relational expression>
	| <primary s_relational expression> <comparison operator> <primary s_relational expression>

FIRST(<relational expression>) = {AVID_T , FPL_T , INL_T, SVID_T , STR_T}
*/
void relational_expression(void){
	switch (lookahead.code){
		case AVID_T:
		case FPL_T:
		case INL_T:
			primary_a_relational_expression();  comparison_operator();  primary_a_relational_expression();
			break;
		case SVID_T:
		case STR_T:
			primary_s_relational_expression();  comparison_operator();  primary_s_relational_expression();
			break;
		default:
			syn_printe();
	}
	gen_incode("PLATY: Relational expression parsed");
}

/*
<comparison operator> -> == | <> | > | <

FIRST(<comparison operator>) = { == , <> , > , < }
*/
void comparison_operator(void){
	if (REL_OP_T == lookahead.code){
		switch (lookahead.attribute.rel_op){
			case EQ:
			case NE:
			case GT:
			case LT:
				match(REL_OP_T, lookahead.attribute.rel_op);
				return;
		}
	}
	syn_printe();
}

/*
<primary a_relational expression> -> AVID_T | FPL_T | INL_T

FIRST(<primary a_relational expression>) = {AVID_T , FPL_T , INL_T}
*/
void primary_a_relational_expression(void){
	switch (lookahead.code){
		case AVID_T:
		case FPL_T:
		case INL_T:
			match(lookahead.code, NO_ATTR);
			break;
		default:
			syn_printe();
	}
	gen_incode("PLATY: Primary a_relational expression parsed");
}

/*
<primary s_relational expression> -> <primary string expression>

FIRST(<primary s_relational expression>) = {SVID_T , STR_T}
*/
void primary_s_relational_expression(void){
	primary_string_expression();
	gen_incode("PLATY: Primary s_relational expression parsed");
}




/*
<variable list> -> <variable identifier> <variable list'>

FIRST(<variable list>) = { AVID_T , SVID_T }
*/
void variable_list(void){
	variable_identifier();  variable_list_p();
	gen_incode("PLATY: Variable list parsed");
}

/*
<variable list'> ->
	  , <variable identifier> <variable list'>
	| e

FIRST(<variable list'>) = { , , e }
*/
void variable_list_p(void){
	if (COM_T == lookahead.code){
		match(COM_T,NO_ATTR);  variable_identifier();  variable_list_p();
	}
}

/*
<variable identifier> -> AVID_T | SVID_T

FIRST(<variable identifier>) = { AVID_T , SVID_T }
*/
void variable_identifier(void){
	switch (lookahead.code){
		case AVID_T:
		case SVID_T:
			match(lookahead.code, NO_ATTR);
			break;
		default:
			syn_printe();
	}
}

/*
<output list> -> <variable list> | STR_T | e

FIRST(<output list>) = { AVID_T , SVID_T , STR_T , e }
*/
void output_list(void){
	switch (lookahead.code){
		case AVID_T:
		case SVID_T:
			variable_list();
			break;
		case STR_T:
			match(STR_T, NO_ATTR);
			gen_incode("PLATY: Output list (string literal) parsed");
			break;
		default:
			gen_incode("PLATY: Output list (empty) parsed");
	}
}