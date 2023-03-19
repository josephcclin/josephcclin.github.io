/* Lexical analyzer for Lotus language  */
/* Designed by Chuang-Chieh Lin at 2004 */

%option noyywrap
%x comment

%{

#include "lotuser.tab.h"
#include <string.h>
#include <math.h>
extern YYLTYPE yylloc;

%}

Identifier		[A-Za-z][A-Za-z0-9]*
IntConstant 		[0-9]+
Operator		[\+\-\*\/\%\>\<\!\=\;\,\(\)\{\}]

%%

else			{ return ELSE; }
exit			{ return EXIT; }
int			{ return INT; }
if			{ return IF; }
read			{ return READ; }
return			{ return RETURN; }
while			{ return WHILE; }
write			{ return WRITE; }
"=="			{ return EQ; }
"!="			{ return NEQ; }
">="			{ return GE; }
"<="			{ return LE; }
"&&"			{ return AND; }
"||"			{ return OR; }

{Identifier}	        { return (IDENTIFIER); }

{IntConstant}		{ yylval = atoi(yytext);
			  return(INTEGER); }

{Operator}		{ return ((int)yytext[0]); }

"--"			{ BEGIN(comment); }
<comment>.*		{ /* eat up any character except newline */ }
<comment>\n		{ ++yylloc.first_line;
			  BEGIN(INITIAL); }

[ \t]+			{ /* eat up blanks */ }
\n			{ ++yylloc.first_line; }
<<EOF>>			{ return 0; /* end of file */ }
.                       { fprintf(stderr, " *** An error occurs on line %d, ", ++yylloc.first_line);
			  fprintf(stderr, "%s is an unrecognized character. *** \n", yytext); }

%%

