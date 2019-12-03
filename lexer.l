%{
  #include <stdio.h>
  #include "y.tab.h"
%}
%option noyywrap
%option yylineno
WS [ \t\n]

NAMELITERAL [:alpha:]

NUMS [:digit:]+
CARS [:alpha:]+
NYCS [[:alnum:][:space:]]+


BINARYOP [\+\-\*\/"and""or"]
OPPAR [(]
CLOSEPAR )

IDENTITYRULE [:alpha:]+[:alnum:]*
%%

{WS}*            // Caracteres escapados

\"{NYCS}\"       {yyval.valString = strdup(yytext); return STRING;}
{OPPAR}          {return OPPARTH;}
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



{IDENTITYRULE}   {return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
