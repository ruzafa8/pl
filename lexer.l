%{
  #include <stdio.h>
  #include "y.tab.h"
%}
%option noyywrap
%option yylineno
WS [ \t\n]

NAMELITERAL [:alpha:]
NUM [0-9]
CAR [a-Z]
NYC {NUM} | {CAR} /* Una letra o caracter */

NUMS {NUM}+
CARS {CAR}+
NYCS {NYC}+       /* Numeros y/o caracteres */

BINARYOP [\+\-\*\/"and""or"]

%%

{WS}*            // Caracteres escapados
\"{NYCS}\"       {yyval.valString = strdup(yytext); return STRING;}
"("              {return OPPARTH;}
")"              {return CLOSPARTH;}
":"              {return ASSIGNTOK;}
"="              {return EQUALS;}
":="             {return ASSIGEQUALS;}
"Entero"         {yyval.valString = strdup(yytext); return TYPEOK;}
"Decimal"        {yyval.valString = strdup(yytext); return TYPEOK;}
"Proposicion"    {yyval.valString = strdup(yytext); return TYPEOK;}
"Letra"          {yyval.valString = strdup(yytext); return TYPEOK;}
"Verdadero"      {return TRUE;}
"Falso"          {return FALSE;}
"+"              {return "+";}
"-"              {return "-";}
"*"              {return "*";}
"/"              {return "/";}
{NUMS}           {return NUMBER;}



{CAR}{NYCS}      {return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
