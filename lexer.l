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


IDENTITYRULE [[:alpha:]][[:alnum:]]*
%%

{WS}*            // Caracteres escapados

\"{NYCS}\" {
  char * res = (char *) malloc(strlen(yytext));
  strncpy(res, yytext + 1, strlen(yytext) - 2);
  yylval.valString = res;
  return STRING;
}

":"              {return ASSIGNTOK;}
"="              {return EQUALS;}
":="             {return ASSIGEQUALS;}
"Entero"         {yylval.valString = strdup(yytext); return TYPETOK;}
"Decimal"        {yylval.valString = strdup(yytext); return TYPETOK;}
"Proposicion"    {yylval.valString = strdup(yytext); return TYPETOK;}
"Letra"          {yylval.valString = strdup(yytext); return TYPETOK;}

"("              {return OPPARTH; /* RECONOCIMIENTO DE OPERADORES BASICOS*/}
")"              {return CLOSPARTH;}
"+"              {return PLUS;}
"-"              {return MINUS;}
"*"              {return BY;}
"/"              {return DIVIDE;}


\'[:alnum:]\' { // -------- RECONOCIMIENTO DE TIPOS BASICOS --------
  yylval.expr = createChar(yytext[1]);
  return CARACTER;
}
"Verdadero" {
  yylval.expr = createBool(TRUE);
  return PROPOSICION;
}
"Falso" {
  yylval.expr = createBool(FALSE);
  return PROPOSICION;
}
{NUMS}\.{NUMS} {
  yylval.expr = createDouble(atof(yytext));
  return DOBLE;
}
{NUMS} {
  yylval.expr = createInt(atoi(yytext));
  return ENTERO;
}



{IDENTITYRULE}   {yylval.valString = strdup(yytext); return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
