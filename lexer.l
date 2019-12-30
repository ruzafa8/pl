%{
  #include <stdio.h>
  #include "y.tab.h"
  
  #define LEX_DEBUG

  #ifdef LEX_DEBUG
  #define DEBUG_PRINT_LEX(x) printf("%s",x)
  #else
  #define DEBUG_PRINT_LEX(x)
  #endif

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

\"{NYCS}\"       {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return STRING;}
{OPPAR}          {DEBUG_PRINT_LEX("("); return OPPARTH;}
")"              {DEBUG_PRINT_LEX(")"); return CLOSPARTH;}
":"              {DEBUG_PRINT_LEX(":"); return ASSIGNTOK;}
"="              {DEBUG_PRINT_LEX("="); return EQUALS;}
":="             {DEBUG_PRINT_LEX(":="); return ASSIGEQUALS;}
"Entero"         {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Decimal"        {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Proposicion"    {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Letra"          {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Verdadero"      {DEBUG_PRINT_LEX("Verdadero"); return TRUE;}
"Falso"          {DEBUG_PRINT_LEX("Falso"); return FALSE;}
"+"              {DEBUG_PRINT_LEX("+"); return PLUS;}
"-"              {DEBUG_PRINT_LEX("-"); return MINUS;}
"*"              {DEBUG_PRINT_LEX("*"); return MULTIPLICAR;}
"/"              {DEBUG_PRINT_LEX("/"); return DIVIDE;}
{NUMS}           {DEBUG_PRINT_LEX("NUMS(?)"); return NUMBER;}



{IDENTITYRULE}   {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
