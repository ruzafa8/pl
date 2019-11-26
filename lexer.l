%{
  #include <stdio.h>
  #include "y.tab.h"
%}
%option noyywrap
%option yylineno
WS [ \t\n]

NAMELITERAL [:alpha:]

%%

{WS}*         ;

.                       { printf("Unknown string %s found at line %d\n",yytext,yylineno);   };
%%

