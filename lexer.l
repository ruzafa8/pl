%{
  #include <stdio.h>
  #include "y.tab.h"
%}
%option noyywrap
%option yylineno
WS [ \t\n]

NAMELITERAL [:alpha:]

NUMS [[:digit:]]+
CARS [:alpha:]+
NYCS [[:alnum:][:space:]]+


BINARYOP [\+\-\*\/]|(and)|(or)
OPPAR [(]
CLOSEPAR )

IDENTITYRULE [[:alpha:]][[:alnum:]]*
%%

{WS}*            // Caracteres escapados

\"{NYCS}\"       {yylval.valString = strdup(yytext); return STRING;}
{OPPAR}          {return OPPARTH;}
")"              {return CLOSPARTH;}
":"              {return ASSIGNTOK;}
"="              {return EQUALS;}
":="             {return ASSIGEQUALS;}
"Entero"         {yylval.valString = strdup(yytext); return TYPETOK;}
"Decimal"        {yylval.valString = strdup(yytext); return TYPETOK;}
"Proposicion"    {yylval.valString = strdup(yytext); return TYPETOK;}
"Letra"          {yylval.valString = strdup(yytext); return TYPETOK;}
"Verdadero"      {return TRUE;}
"Falso"          {return FALSE;}
"+"              {return PLUS;}
"-"              {return MINUS;}
"*"              {return MULTIPLICAR;}
"/"              {return DIVIDE;}
{NUMS}           {return NUMBER;}



{IDENTITYRULE}   {return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
