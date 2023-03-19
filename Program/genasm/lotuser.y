%{
/* ******************************************* */
/* 	Project 5 of Compilers:                */
/* 	Implementation of a Code Generator     */
/* 	Student No.: 893410010                 */
/* 	Authore:     Chuang-Chieh Lin          */
/* 	Email:       lincc@cs.ccu.edu.tw       */
/* ******************************************* */

/*  --- C declarations --- */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include "newtree.h"
#include "symtab.h"
#include "typecheck.c"
#include "asmgenerator.c"

extern FILE *yyin;
int parse = 0, funcpos;
%}

/* 
 * Bison declarations.                   
 * Tokens, nonterminals, precedence and   
 * associativity are defined here         
 */

%locations
%union {
	char *name;
	int value;
	struct tree *Tnode;
}
%token <name> IDENTIFIER
%token <value> INTEGER
%token <value> ',' ';' '(' ')' '{' '}'
%token <value> ELSE EXIT INT IF READ RETURN WHILE WRITE
%type <Tnode> program
%type <Tnode> variable_declarations
%type <Tnode> variable_declaration
%type <Tnode> function_definitions
%type <Tnode> function_definition
%type <Tnode> parameters
%type <Tnode> parameter_list
%type <Tnode> function_body
%type <Tnode> statements
%type <Tnode> statement
%type <Tnode> assignment_statement
%type <Tnode> if_statement
%type <Tnode> while_statement
%type <Tnode> return_statement
%type <Tnode> exit_statement
%type <Tnode> read_statement
%type <Tnode> write_statement
%type <Tnode> compound_statement
%type <Tnode> bool_expression
%type <Tnode> bool_term
%type <Tnode> bool_factor
%type <Tnode> bool_primary
%type <Tnode> arith_expressions
%type <Tnode> arith_expression_list
%type <Tnode> arith_expression
%type <Tnode> arith_term
%type <Tnode> arith_factor
%type <Tnode> arith_primary

%right <value> '!'
%left <value> '='
%nonassoc <value> '<' '>' EQ NEQ GE LE AND OR
%left <value> '+' '-'
%left <value> '*' '/' '%'
%left <value> UMINUS 			/* Negation--unary minus */

%expect 1
%start program
%%

/* Productions and semantic rules are as follows. */

program : variable_declarations function_definitions
		{ 
			$$ = build_program($1, $2);
			syntax_tree = $$;
		}
	;
variable_declarations : /* empty production */
                { 
			$$ = NULL;
		}
  	| variable_declarations variable_declaration
	        { 
			$$ = build_list($1, $2);
		}
   	;
variable_declaration : INT IDENTIFIER ';'
                { 
			$$ = build_id($2, yylloc.first_line);
		}
	;
function_definitions : function_definition
                { 
			$$ = build_list(NULL, $1);
		}
	| function_definitions function_definition
		{ 
			$$ = build_list($1, $2);
		}
	;
function_definition : INT IDENTIFIER '(' parameters ')' function_body
		{ 
			
			$$ = build_function($2, $4, $6, funcpos);
		}
	;
parameters : /* empty production */ 
		{ 
			$$ = NULL;
			funcpos = yylloc.first_line;
		}
	| parameter_list
		{ 
			$$ = $1;
			funcpos = yylloc.first_line;
		}
	;
parameter_list : INT IDENTIFIER 
		{ 
			$$ = build_list(NULL, build_id($2, yylloc.first_line));
		}
	| parameter_list ',' INT IDENTIFIER
		{ 
			$$ = build_list($1, build_id($4, yylloc.first_line));
		}
	;
function_body : '{' variable_declarations statements '}'
		{ 
			$$ = build_body($2, $3);
		}
	;
statements : /* empty production */
		{ 
			$$ = NULL;
		}
	| statements statement
		{ 
			$$ = build_list($1, $2);
		}
	;
statement : assignment_statement 
		{ 
			$$ = $1;
		}
	| compound_statement 
		{ 
			$$ = $1;
		}
	| if_statement 
		{ 
			$$ = $1;
		}
	| while_statement 
		{ 
			$$ = $1;
		}
	| return_statement 
		{ 
			$$ = $1;
		}
	| exit_statement 
		{ 
			$$ = $1;
		}
	| read_statement 
		{ 
			$$ = $1;
		}
	| write_statement
		{ 
			$$ = $1;
		}
	;
assignment_statement : IDENTIFIER '=' arith_expression ';'
		{ 
			$$ = build_assign($1, $3, yylloc.first_line);
		}
	;
compound_statement : '{' statements '}'
		{ 
			$$ = build_body(NULL, $2);
		}
	;
if_statement : IF '(' bool_expression ')' statement 
		{ 
			$$ = build_if($3, $5, NULL);
		}
	| IF '(' bool_expression ')' statement ELSE statement
		{ 
			$$ = build_if($3, $5, $7);
		}
	;
while_statement : WHILE '(' bool_expression ')' statement
		{ 
			$$ = build_while($3, $5);
		}
	;
return_statement : RETURN arith_expression ';'
		{ 
			$$ = build_return($2);
		}
	;
exit_statement : EXIT ';'
		{ 
			$$ = build_exit();
		}
	;
read_statement : READ IDENTIFIER ';'
		{ 
			$$ = build_read($2, yylloc.first_line);
		}
	;
write_statement : WRITE arith_expression ';'
		{ 
			$$ = build_write($2);
		}
	;
bool_expression : bool_term 
		{ 
			$$ = $1;
		}
	| bool_expression OR bool_term
		{ 
			$$ = build_expr($2, $1, $3);
		}
	;
bool_term : bool_factor  
		{ 
			$$ = $1;
		}
	| bool_term AND bool_factor
		{ 
			$$ = build_expr($2, $1, $3);
		}
	;
bool_factor : bool_primary  
		{ 
			$$ = $1;
		}
	| '!' bool_primary
		{ 
			$$ = build_expr($1, NULL, $2);
		}
	;
bool_primary : arith_expression EQ arith_expression
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression NEQ arith_expression
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression '>' arith_expression
		{
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression GE arith_expression
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression '<' arith_expression
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression LE arith_expression
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| '(' bool_expression ')'
		{ 
			$$ = build_call(NULL, $2, yylloc.first_line);
		}
	;
arith_expressions : /* empty production */ 
		{ 
			$$ = NULL;
		}
	| arith_expression_list
		{ 
			$$ = $1;
		}
	;
arith_expression_list : arith_expression 
		{ 
			$$ = build_list(NULL, $1);
		}
	| arith_expression_list ',' arith_expression
		{ 
			$$ = build_list($1, $3);
		}
	;
arith_expression : arith_term 
		{ 
			$$ = $1;
		}
	| arith_expression '+' arith_term
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_expression '-' arith_term
		{ 
			$$ = build_expr($2, $1, $3);
		}
	;
arith_term : arith_factor
		{ 
			$$ = $1;
		}
	| arith_term '*' arith_factor
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_term '/' arith_factor
		{ 
			$$ = build_expr($2, $1, $3);
		}
	| arith_term '%' arith_factor
		{ 
			$$ = build_expr($2, $1, $3);
		}
	;
arith_factor : arith_primary
		{ 
			$$ = $1;
		}
	| '-' arith_primary %prec UMINUS
		{
			$$ = build_expr($1, NULL, $2);
		}
	;
arith_primary : INTEGER
		{ 
			$$ = build_intcon($1);
		}
	| IDENTIFIER
		{ 
			$$ = build_id($1, yylloc.first_line);
		}
	| IDENTIFIER '(' arith_expressions ')' 
		{ 
			$$ = build_call($1, $3, yylloc.first_line);
		}
	| '(' arith_expression ')'
		{ 
			$$ = build_call(NULL, $2, yylloc.first_line);
		}
	;
%%

/*
 * Additional C codes
 * yyparse will deal with errors  
 */

yyerror (char *s)  
{
	fprintf(stderr, "****** %s!! ",s);
	fprintf(stderr, "It occurs on line: %d ****** \n", yylloc.first_line);  /* error record */
}

/* main function is right here */

main (argc, argv)  
int argc;
char **argv;
{
	++argv, --argc;  /* skip over the program name */
        yylloc.first_line = yylloc.last_line = 1;
        yylloc.first_column = yylloc.last_column = 0;
	
	yyin = stdin;
	parse = yyparse();
	if (!parse) { // parsing succeeded.
		tycheck = chktype(syntax_tree);
		if (!tycheck) { // type checking succeeded.
			GenCode(syntax_tree);
		}
	}
}

