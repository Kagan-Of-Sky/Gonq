/* File Name:     parser.h
 * Compiler:      MS Visual Studio 2013
 * Author:        Mark Kaganovsky, 040789903
 * Course:        CST 8152 - Compilers, Lab Section 012
 * Assignment:    4
 * Date:          April 22 2016
 * Professor:     Sv. Ranev
 * Purpose:       Header file for the parser.
 * 
 * Function List: parser  match  syn_printe  syn_eh  gen_incode
 *                program  opt_statements  statement  statements  statements_p
 *                assignment_statement  selection_statement  iteration_statement  input_statement  output_statement
 *                assignment_expression  arithmetic_expression
 *                string_expression  string_expression_p  primary_string_expression
 *                conditional_expression
 *                variable_list  variable_list_p  variable_identifier
 *                output_list
 *                unary_arithmetic_expression  additive_arithmetic_expression  additive_arithmetic_expression_p
 *                multiplicative_arithmetic_expression  multiplicative_arithmetic_expression_p  primary_arithmetic_expression
 *                logical_or_expression  logical_or_expression_p  logical_and_expression  logical_and_expression_p
 *                relational_expression  primary_a_relational_expression  primary_s_relational_expression  comparison_operator
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "stable.h"
#include "token.h"
#include "buffer.h"




/****************************************************************************************************
 External Variable & Function Declarations
*****************************************************************************************************/
extern Token malar_next_token(Buffer * sc_buf);

extern int     line;       /* Line number */
extern char   *kw_table[]; /* Keyword table */
extern Buffer *str_LTBL;   /* String literal table */
extern STD     sym_table;  /* Symbol table */




/****************************************************************************************************
 Constants
*****************************************************************************************************/
#define NO_ATTR 0 /* A token which has no attribute associated with it (ex: Left brace, Right brace, etc.) */

/* This enum represents the indexes of keywords in the kw_table. */
enum {
	KWI_ELSE,     /* Keyword Index ELSE in kw_table */
	KWI_IF,       /* Keyword Index IF in kw_table */
	KWI_INPUT,    /* Keyword Index INPUT in kw_table */
	KWI_OUTPUT,   /* Keyword Index OUTPUT in kw_table */
	KWI_PLATYPUS, /* Keyword Index PLATYPUS in kw_table */
	KWI_REPEAT,   /* Keyword Index REPEAT in kw_table */
	KWI_THEN,     /* Keyword Index THEN in kw_table */
	KWI_USING     /* Keyword Index USING in kw_table */
};




/****************************************************************************************************
 Global Variable Declarations
*****************************************************************************************************/
int            synerrno;  /* Error count. */
static Token   lookahead; /* Lookahead token. */
static Buffer *sc_buf;    /* Buffer containing program source code. */




/****************************************************************************************************
 Function Prototypes below
*****************************************************************************************************/
void parser(Buffer *in_buf);
void match(int pr_token_code, int pr_token_attribute);
void syn_printe(void);
void syn_eh(int sync_token_code);
void gen_incode(char *s);

void program(void);

void opt_statements(void);
void statement(void);
void statements(void);
void statements_p(void);

void assignment_statement(void);
void selection_statement(void);
void iteration_statement(void);
void input_statement(void);
void output_statement(void);

void assignment_expression(void);
void arithmetic_expression(void);

void string_expression(void);
void string_expression_p(void);
void primary_string_expression(void);

void conditional_expression(void);

void variable_list(void);
void variable_list_p(void);
void variable_identifier(void);

void output_list(void);

void unary_arithmetic_expression(void);
void additive_arithmetic_expression(void);
void additive_arithmetic_expression_p(void);
void multiplicative_arithmetic_expression(void);
void multiplicative_arithmetic_expression_p(void);
void primary_arithmetic_expression(void);

void logical_or_expression(void);
void logical_or_expression_p(void);
void logical_and_expression(void);
void logical_and_expression_p(void);
void relational_expression(void);
void primary_a_relational_expression(void);
void primary_s_relational_expression(void);
void comparison_operator(void);

#endif
