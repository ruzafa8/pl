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
"Entero"         {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return TYPETOK;}
"Decimal"        {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return TYPETOK;}
"Proposicion"    {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return TYPETOK;}
"Letra"          {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return TYPETOK;}


"imprime"        {DEBUG_PRINT_LEX("%s","imprime"); return IMPRIMIR; /* Comandos */}

"("              {DEBUG_PRINT_LEX("%s","("); return OPPARTH; /* RECONOCIMIENTO DE OPERADORES BASICOS*/}
")"              {DEBUG_PRINT_LEX("%s",")"); return CLOSPARTH;}
"+"              {DEBUG_PRINT_LEX("%s","+"); return PLUS;}
"-"              {DEBUG_PRINT_LEX("%s","-"); return MINUS;}
"*"              {DEBUG_PRINT_LEX("%s","*"); return BY;}
"/"              {DEBUG_PRINT_LEX("%s","/"); return DIVIDE;}



\'[:alnum:]\' { // -------- RECONOCIMIENTO DE TIPOS BASICOS --------
  yylval.expr = createChar(yytext[1]);
  DEBUG_PRINT_LEX("%c",yytext[1]);
  return CARACTER;
}
"Verdadero" {
  yylval.expr = createBool(TRUE);
  DEBUG_PRINT_LEX("%s","Verdadero");
  return PROPOSICION;
}
"Falso" {
  yylval.expr = createBool(FALSE);
  DEBUG_PRINT_LEX("%s","Falso");
  return PROPOSICION;
}
{NUMS}\.{NUMS} {
  yylval.expr = createDouble(atof(yytext));
  DEBUG_PRINT_LEX("%s",yytext);
  return DOBLE;
}
{NUMS} {
  yylval.expr = createInt(atoi(yytext));
  DEBUG_PRINT_LEX("%s",yytext);
  return ENTERO;
}



{IDENTITYRULE}   {yylval.valString = strdup(yytext); DEBUG_PRINT_LEX("%s",yylval.valString); return IDENTIFIER;}


.          {
  printf("Unknown string %s found at line %d\n",yytext,yylineno);
}
%%
