%{
  #include <stdio.h>
  #include "y.tab.h"

  #define LEX_DEBUG

  #ifdef LEX_DEBUG
  #define DEBUG_PRINT_LEX(s,x) printf(s,x)
  #else
  #define DEBUG_PRINT_LEX(s,x)
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
  DEBUG_PRINT_LEX("%s",res);
  return STRING;
}

":"              {DEBUG_PRINT_LEX("%s",":"); return ASSIGNTOK;}
"="              {DEBUG_PRINT_LEX("%s","="); return EQUALS;}
":="             {DEBUG_PRINT_LEX("%s",":="); return ASSIGEQUALS;}
"Entero"         {yylval.type = INT; DEBUG_PRINT_LEX("%s","INT"); return TYPETOK;}
"Decimal"        {yylval.type = DOUBLE; DEBUG_PRINT_LEX("%s","DOUBLE"); return TYPETOK;}
"Proposicion"    {yylval.type = BOOL; DEBUG_PRINT_LEX("%s","BOOL"); return TYPETOK;}
"Letra"          {yylval.type = CHAR; DEBUG_PRINT_LEX("%s","CHAR"); return TYPETOK;}


"imprime"        {DEBUG_PRINT_LEX("%s","imprime"); return IMPRIMIR; /* Comandos */}
"se"             {DEBUG_PRINT_LEX("%s","se"); return IFTOK;}
"daquela"        {DEBUG_PRINT_LEX("%s","daquela"); return THENTOK;}
"se non"         {DEBUG_PRINT_LEX("%s","se non"); return ELSETOK;}


"("              {DEBUG_PRINT_LEX("%s","("); return OPPARTH; /* RECONOCIMIENTO DE OPERADORES BASICOS*/}
")"              {DEBUG_PRINT_LEX("%s",")"); return CLOSPARTH;}
"+"              {DEBUG_PRINT_LEX("%s","+"); return PLUSTOK;}
"-"              {DEBUG_PRINT_LEX("%s","-"); return MINUSTOK;}
"*"              {DEBUG_PRINT_LEX("%s","*"); return BYTOK;}
"/"              {DEBUG_PRINT_LEX("%s","/"); return DIVIDETOK;}

"o" {return ORTOK; /* OPERADORES BINARIOS*/}
"y" {return ANDTOK;}
"eo" {return XORTOK;}
"si" {return SITOK;}
"sii" {return SIITOK;}
"<" {return LESSTOK;}
"<=" {return LESS_EQTOK;}
">" {return MORETOK;}
">=" {return MORE_EQTOK;}
"/=" {return NOT_EQTOK;}
"==" {return DOBLE_EQUALSTOK;}

"mientras" {return MIENTRAS;}
"haz" {return HAZ;}
"." {return PUNTO;}



\'[:alnum:]\' { // -------- RECONOCIMIENTO DE TIPOS BASICOS --------
  yylval.expr = createLiteralExpression(createChar(yytext[1]));
  DEBUG_PRINT_LEX("%c",yytext[1]);
  return CARACTER;
}
"Verdadero" {
  yylval.expr = createLiteralExpression(createBool(TRUE));
  DEBUG_PRINT_LEX("%s","Verdadero");
  return PROPOSICION;
}
"Falso" {
  yylval.expr = createLiteralExpression(createBool(FALSE));
  DEBUG_PRINT_LEX("%s","Falso");
  return PROPOSICION;
}
{NUMS}\.{NUMS} {
  yylval.expr = createLiteralExpression(createDouble(atof(yytext)));
  DEBUG_PRINT_LEX("%s",yytext);
  return DOBLE;
}
{NUMS} {
  yylval.expr = createLiteralExpression(createInt(atoi(yytext)));
  DEBUG_PRINT_LEX("%s",yytext);
  return ENTERO;
}



{IDENTITYRULE}   {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
