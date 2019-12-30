%{
    #include <stdio.h>
    #include <string.h>
    void yyerror (char const *);
    extern int yylineno;
    extern int yylex();
%}

%union{
  char * valString;
  Expression * expr;
}

%code requires {
  #include "expression.h"
}

%locations

%token <valString> IDENTIFIER
%token ASSIGNTOK
%token <valString> TYPETOK           //Enum?
%token EQUALS
%token ASSIGEQUALS
%token <valString> STRING


%left <valString> BINARYOP
%token PLUS MINUS BY DIVIDE OPPARTH CLOSPARTH
%token <expr> ENTERO DOBLE CARACTER PROPOSICION

%start S
%% /* grammar */

S:
  /* %empty */            {printf("Empty\n");}
  | sentences ;
;

sentences:
  sentence              {printf("Sentence:\n");}
  | sentence sentences  {printf("Sentence:\n");}

sentence:
  varDecl
  | varAssign
  | expression

varDecl:
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression    {printf("Variable %s Type %s = \n", $1, $3);}
  | IDENTIFIER ASSIGNTOK TYPETOK                    {printf("Variable %s Type %s (noVal)\n", $1, $3);}
  | IDENTIFIER ASSIGEQUALS expression               {printf("Variable %s, auto, = \n", $1);}
;

varAssign:
  IDENTIFIER EQUALS expression                      {printf("Variable %s =", $1);}
;

literal:
  ENTERO | STRING | DOBLE | CARACTER | PROPOSICION
;
/*
expression:
  OPPARTH expression CLOSPARTH                      {printf("(s)");}
  | expression PLUS expression
  | expression MINUS expression
  | expression MULTIPLICAR expression
  | expression DIVIDE expression
  | MINUS expression  %prec NEG                       {printf("-_");}
  | binaryOp
  | IDENTIFIER                                      {printf("Identifier s");}
  | literal                                         {printf("Literal: s");}
;
*/

expression: expression PLUS t | t
t: t MINUS f | f
f: f BY g | g
g: g DIVIDE h | h
h: h BINARYOP i | i
i: MINUS j | j
j: OPPARTH expression CLOSPARTH | literal | IDENTIFIER
/*
binaryOp:
  expression BINARYOP expression
*/
%%
void yyerror (char const *message) { fprintf (stderr, "%s[%d]\n", message,yylineno);}

int main(int argc, char ** argv) {
  int ret;
  extern FILE *yyin;

  if(argc >= 2){
      // open a file handle to a particular file:
      FILE *myfile = fopen(argv[1], "r");
      // make sure it's valid:
      if (!myfile) {
        fprintf (stderr, "No se pudo abrir el archivo\n");
        return -1;
      }
      // set lex to read from it instead of defaulting to STDIN:
      yyin = myfile;

      // lex through the input:
      ret = yyparse();
      fclose(yyin);
      return ret;
  } else {
    printf("Usage: cosa filename\n");
    return 0;
  }
}
