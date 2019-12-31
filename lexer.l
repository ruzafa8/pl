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


IDENTITYRULE [[:alpha:]][[:alnum:]]*
%%

{WS}*            // Caracteres escapados

\"{NYCS}\" {
  char * res = (char *) malloc(strlen(yytext));
  strncpy(res, yytext + 1, strlen(yytext) - 2);
  yylval.valString = res;
  DEBUG_PRINT_LEX(res);
  return STRING;
}

":"              {DEBUG_PRINT_LEX(":"); return ASSIGNTOK;}
"="              {DEBUG_PRINT_LEX("="); return EQUALS;}
":="             {DEBUG_PRINT_LEX(":="); return ASSIGEQUALS;}
"Entero"         {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Decimal"        {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Proposicion"    {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}
"Letra"          {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return TYPETOK;}

"("              {DEBUG_PRINT_LEX("("); return OPPARTH; /* RECONOCIMIENTO DE OPERADORES BASICOS*/}
")"              {DEBUG_PRINT_LEX(")"); return CLOSPARTH;}
"+"              {DEBUG_PRINT_LEX("+"); return PLUS;}
"-"              {DEBUG_PRINT_LEX("-"); return MINUS;}
"*"              {DEBUG_PRINT_LEX("*"); return BY;}
"/"              {DEBUG_PRINT_LEX("/"); return DIVIDE;}



\'[:alnum:]\' { // -------- RECONOCIMIENTO DE TIPOS BASICOS --------
  yylval.expr = createChar(yytext[1]);
  DEBUG_PRINT_LEX(yytext[1]);
  return CARACTER;
}
"Verdadero" {
  yylval.expr = createBool(TRUE);
  DEBUG_PRINT_LEX("Verdadero");
  return PROPOSICION;
}
"Falso" {
  yylval.expr = createBool(FALSE);
  DEBUG_PRINT_LEX("Falso");
  return PROPOSICION;
}
{NUMS}\.{NUMS} {
  yylval.expr = createDouble(atof(yytext));
  DEBUG_PRINT_LEX(yytext);
  return DOBLE;
}
{NUMS} {
  yylval.expr = createInt(atoi(yytext));
  DEBUG_PRINT_LEX(yytext);
  return ENTERO;
}



{IDENTITYRULE}   {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX(yylval.valString); return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
