/* ========================================================== */
/* Project 1 of Compilers:                                    */
/* Implementation of a Lexical Analyzer for a small language  */
/* Student No.: 893410010                                     */
/* Name: Chung-Chieh Lin                                      */
/* Email address: lincc@cs.ccu.edu.tw                         */
/* ========================================================== */

%option noyywrap
%option yylineno
%x comment

%{
int num_lines = 1;
char *opt="-s";
int ACTION;

#include<string.h>
%}

Keyword                 "else"|"exit"|"int"|"if"|"read"|"return"|"while"|"write"
Identifier		[A-Za-z][A-Za-z0-9]*
IntConstant 		[0-9]+
Operator		[\+\-\*\/\%\>\<\!\=\;\,\(\)\{\}]|"=="|"!="|">="|"<="|"&&"|"||"

%%

{Keyword}		{ 
				if (ACTION)
					fprintf(stdout, "Keyword:\t\t%s\t\tline: %d\n", yytext, yylineno); 
				else {/* Don't print any message */}
			}

{Identifier}	        { 
				if (ACTION)
					fprintf(stdout, "Identifier:\t\t%s\t\tline: %d\n", yytext, yylineno); 
				else {/* Don't print any message */}
			}

{IntConstant}		{ 
				if (ACTION)
					fprintf(stdout, "Integer constant:\t%s\t\tline: %d\n", yytext, yylineno); 
				else {/* Don't print any message */}
			}

{Operator}		{ 
				if (ACTION)
					fprintf(stdout, "Operator:\t\t%s\t\tline: %d\n", yytext, yylineno); 
				else {/* Don't print any message */}
			}

"--"			{ BEGIN(comment); }
<comment>.*		{ /* eat up any character except newline */ }
<comment>\n		{ ++num_lines;
			  BEGIN(INITIAL); }

[ \t]+			{ /* eat up blanks */ }
\n			{ ++num_lines; }
.                       { fprintf(stderr, " ***** An error occurs on line %d, ", yylineno);
			  fprintf(stderr, "%s is an unrecognized character. ***** \n", yytext); }

%%

main( argc, argv )
int argc;
char **argv;
{
	++argv, --argc;  /* skip over the program name */
	if ( argc > 0 ){ /* We consider the option mode */
		//printf("\nYour option is : %s ... ", argv[0]);
		ACTION = 1;
		yyin = fopen( argv[0], "r" );
	        if (!strcmp(argv[0],opt)){
			printf("\n");
			yylex();
			printf("\nThe number of lines in this lotus program: %d\n", num_lines);
		} else	printf("Error command. \n\n");
	} else {  /* We consider the stdin mode but no actions will be performed */
		ACTION = 0;
		yyin = stdin;
		yylex;
	}			
}
