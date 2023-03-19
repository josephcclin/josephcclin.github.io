%{
/* =============================================================== */
/* Project 2 of Compilers:                                         */
/* Implementation of an LALR(1) parser for Lotus language          */
/* Student No. 893410010                                           */
/* Authore: Chuang-Chieh Lin                                        */
/* Email address: lincc@cs.ccu.edu.tw                              */
/* =============================================================== */

/*  --- C declarations --- */

//#define YYSTYPE double
#include <math.h>
#include <stdio.h>
char *opt = "-p";
int action = 0;
extern FILE *yyin;

%}

/* Bison declarations 
   Tokens, precedence and associativity are defined here */

%token ELSE EXIT INT IF READ RETURN WHILE WRITE
%token EQ NEQ GE LE AND OR
%token IDENTIFIER INTEGER
%locations
%right '!'
%right '='
%nonassoc '<' '>' EQ NEQ LE GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS

%expect 1
%start program
%%

/* Grammar rules (productions) are as follows. */

program : variable_declarations function_definitions
		{ 
			if (action)
				fprintf(stdout, "program -> variable_declarations function_definitions \n"); 
		  	else { /* don't print message */ }
		}
	;
variable_declarations : /* empty production */
                { 
			if (action)
				fprintf(stdout, "variable_declarations -> empty \n"); 
			else { /* don't print message */ }
		}
  	| variable_declarations variable_declaration
	        { 
			if (action)
				fprintf(stdout, "variable_declarations -> variable_declarations variable_declaration \n"); 
			else { /* don't print message */ }
		}
   	;
variable_declaration : INT IDENTIFIER ';'
                { 
			if (action)
				fprintf(stdout, "variable_declaration -> int Identifier ; \n"); 
			else { /* don't print message */ }
		}
	;
function_definitions : function_definition
                { 
			if (action)
				fprintf(stdout, "function_definitions -> function_definition \n"); 
			else { /* don't print message */ }
		}
	| function_definitions function_definition
		{ 
			if (action)
				fprintf(stdout, "function_definitions -> function_definitions function_definition \n");
			else { /* don't print message */ }
		}
	;
function_definition : INT IDENTIFIER '(' parameters ')' function_body
		{ 
			if (action)
				fprintf(stdout, "function_definition -> int Identifier ( parameters ) function_body \n"); 
			else { /* don't print message */ }
		}
	;
parameters : /* empty production */ 
		{ 
			if (action)
				fprintf(stdout, "parameters -> empty\n"); 
			else { /* don't print message */ }
		}
	| parameter_list
		{
			if (action) 
				fprintf(stdout, "parameters -> parameter_list \n"); 
			else { /* don't print message */ }
		}
		  
	;
parameter_list : INT IDENTIFIER 
		{ 
			if (action)
				fprintf(stdout, "parameter_list -> int Identifier \n"); 
			else { /* don't print message */ }
		}
	| parameter_list ',' INT IDENTIFIER
		{ 
			if (action)
				fprintf(stdout, "parameter_list -> int Identifier \n"); 
			else { /* don't print message */ }
		}
	;
function_body : '{' variable_declarations statements '}'
		{ 
			if (action)
				fprintf(stdout, "function_body -> { variable_declarations statements } \n"); 
			else { /* don't print message */ }
		}
	;
statements : /* empty production */
		{ 
			if (action)
				fprintf(stdout, "statements -> empty \n"); 
			else { /* don't print message */ }
		}
	| statements statement
		{ 
			if (action)
				fprintf(stdout, "statements -> statements statement \n"); 
			else { /* don't print message */ }
		}
	;
statement : assignment_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> assignment_statement \n"); 
			else { /* don't print message */ }
		}
	| compound_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> compound_statement \n"); 
			else { /* don't print message */ }
		}
	| if_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> if_statement \n"); 
			else { /* don't print message */ }
		}
	| while_statement 
		{ 
			if (action) 
				fprintf(stdout, "statement -> while_statement \n"); 
			else { /* don't print message */ }
		}
	| return_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> return_statement \n"); 
			else { /* don't print message */ }
		}
	| exit_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> exit_statement \n"); 
			else { /* don't print message */ }
		}
	| read_statement 
		{ 
			if (action)
				fprintf(stdout, "statement -> read_statement \n"); 
			else { /* don't print message */ }
		}
	| write_statement
		{ 
			if (action)
				fprintf(stdout, "statement -> write_statement \n"); 
			else { /* don't print message */ }
		}
	;
assignment_statement : IDENTIFIER '=' arith_expression ';'
		{ 
			if (action)
				fprintf(stdout, "assignment_statement -> Identifier = arith_expression ; \n"); 
			else { /* don't print message */ }
		}
	;
compound_statement : '{' statements '}'
		{ 
			if (action)
				fprintf(stdout, "compound_statement -> { statements } \n"); 
			else { /* don't print message */ }
		}
	;
if_statement : IF '(' bool_expression ')' statement 
		{ 
			if (action)
				fprintf(stdout, "if_statement -> if ( bool_expression ) statement \n"); 
			else { /* don't print message */ }
		}
	| IF '(' bool_expression ')' statement ELSE statement
		{ 
			if (action)
				fprintf(stdout, "if_statement -> if ( bool_expression ) statement else statement \n"); 
			else { /* don't print message */ }
		}
	;
while_statement : WHILE '(' bool_expression ')' statement
		{ 
			if (action)
				fprintf(stdout, "while_statement -> while ( bool_expression ) statement \n"); 
			else { /* don't print message */ }
		}
	;
return_statement : RETURN arith_expression ';'
		{ 
			if (action)
				fprintf(stdout, "return_statement -> return arith_expression ; \n"); 
			else { /* don't print message */ }
		}
	;
exit_statement : EXIT ';'
		{ 
			if (action)
				fprintf(stdout, "exit_statement -> exit ; \n"); 
			else { /* don't print message */ }
		}
	;
read_statement : READ IDENTIFIER ';'
		{ 
			if (action)
				fprintf(stdout, "read_statement -> read Identifier ; \n"); 
			else { /* don't print message */ }
		}
	;
write_statement : WRITE arith_expression ';'
		{ 
			if (action)
				fprintf(stdout, "write_statement -> write arith_expression ; \n"); 
			else { /* don't print message */ }
		}
	;
bool_expression : bool_term 
		{ 
			if (action)
				fprintf(stdout, "bool_expression -> bool_term  \n"); 
			else { /* don't print message */ }
		}
	| bool_expression OR bool_term
		{ 
			if (action)
				fprintf(stdout, "bool_expression -> bool_expression || bool_term \n"); 
			else { /* don't print message */ }
		}
	;
bool_term : bool_factor  
		{ 
			if (action)
				fprintf(stdout, "bool_term -> bool_factor \n"); 
			else { /* don't print message */ }
		}
	| bool_term AND bool_factor
		{ 
			if (action)
				fprintf(stdout, "bool_term -> bool_term AND bool_factor \n"); 
			else { /* don't print message */ }
		}
	;
bool_factor : bool_primary  
		{ 
			if (action)
				fprintf(stdout, "bool_factor -> bool_primary \n"); 
			else { /* don't print message */ }
		}
	| '!' bool_primary
		{ 
			if (action)
				fprintf(stdout, "bool_factor -> ! bool_primary \n"); 
			else { /* don't print message */ }
		}
	;
bool_primary : arith_expression EQ arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression == arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression NEQ arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression != arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression '>' arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression > arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression GE arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression >= arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression '<' arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression < arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression LE arith_expression
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression <=  arith_expression \n"); 
			else { /* don't print message */ }
		}
	| '(' bool_expression ')'
		{ 
			if (action)
				fprintf(stdout, "bool_primary -> arith_expression ( bool_expression ) \n"); 
			else { /* don't print message */ }
		}
	;
arith_expressions : /* empty production */ 
		{ 
			if (action)
				fprintf(stdout, "arith_expressions -> empty \n"); 
			else { /* don't print message */ }
		}
	| arith_expression_list
		{ 
			if (action)
				fprintf(stdout, "arith_expressions -> arith_expression_list \n"); 
			else { /* don't print message */ }
		}
	;
arith_expression_list : arith_expression 
		{ 
			if (action)
				fprintf(stdout, "arith_expression_list -> arith_expression \n"); 
			else { /* don't print message */ }
		}
	| arith_expression_list ',' arith_expression
		{ 
			if (action)
				fprintf(stdout, "arith_expression_list -> arith_expression_list , arith_expression \n"); 
			else { /* don't print message */ }
		}
	;
arith_expression : arith_term 
		{ 
			if (action)
				fprintf(stdout, "arith_expression -> arith_term \n"); 
			else { /* don't print message */ }
		}
	| arith_expression '+' arith_term
		{ 
			if (action)
				fprintf(stdout, "arith_expression -> arith_expression + arith_term \n"); 
			else { /* don't print message */ }
		}
	| arith_expression '-' arith_term
		{ 
			if (action)
				fprintf(stdout, "arith_expression -> arith_expression - arith_term \n"); 
			else { /* don't print message */ }
		}
	;
arith_term : arith_factor 
		{ 
			if (action)
				fprintf(stdout, "arith_term -> arith_factor \n"); 
			else { /* don't print message */ }
		}
	| arith_term '*' arith_factor
		{ 
			if (action)
				fprintf(stdout, "arith_term -> arith_term * arith_factor \n"); 
			else { /* don't print message */ }
		}
	| arith_term '/' arith_factor
		{ 
			if (action)
				fprintf(stdout, "arith_term -> arith_term / arith_factor \n"); 
			else { /* don't print message */ }
		}
	| arith_term '%' arith_factor
		{ 
			if (action)
				fprintf(stdout, "arith_term -> arith_term % arith_factor \n"); 
			else { /* don't print message */ }
		}
	;
arith_factor : arith_primary 
		{ 
			if (action)
				fprintf(stdout, "arith_factor -> arith_primary \n"); 
			else { /* don't print message */ }
		}
	| '-' arith_primary %prec UMINUS
		{ 
			if (action)
				fprintf(stdout, "arith_factor -> - arith_primary \n");
			else { /* don't print message */ }
		}
	;
arith_primary : INTEGER 
		{ 
			if (action)
				fprintf(stdout, "arith_primary -> Integer \n"); 
			else { /* don't print message */ }
		}
	| IDENTIFIER 
		{ 
			if (action)
				fprintf(stdout, "arith_primary -> Identifier \n"); 
			else { /* don't print message */ }
		}
	| IDENTIFIER '(' arith_expressions ')' 
		{ 
			if (action)
				fprintf(stdout, "arith_primary -> Identifier ( arith_expressions ) \n"); 
			else { /* don't print message */ }
		}
	| '(' arith_expression ')'
		{ 
			if (action)
				fprintf(stdout, "arith_primary -> ( arith_expression ) \n"); 
			else { /* don't print message */ }
		}
	;
%%

/* Additional C codes
   yyparse will deal with errors  */

yyerror (char *s)  
{
	fprintf(stderr, "****** %s!! ",s);
	fprintf(stderr, "It occurs on line: %d ******\n", yylloc.first_line);  /* error record */
}

/* main function is right here */

main (argc, argv)  
int argc;
char **argv;
{
	++argv, --argc;  /* skip over the program name */
	yylloc.first_line = yylloc.last_line = 1;
	yylloc.first_column = yylloc.last_column = 0;

	if ( argc > 0 ) /* We consider the option mode */
	{ 
		//printf("\nYour option is : %s ... ", argv[0]);
		action = 1; // print messages
		if (!strcmp(argv[0], opt)) 
		{
			//printf("\nPass! Productions reduced by the parser are listed as follows... \n\n");
			yyin = stdin;
			yyparse();
		}
		else { /* Error command */ 
			printf("Error command. \n");
		}
	}
	else { /* Read file from stdin */ 
		action = 0; // don't print any message
		yyin = stdin;
		yyparse();
	}
}
		
