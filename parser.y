%{
    #include <stdio.h>
    #include <string.h>

    #ifdef PAR_DEBUG
    #define DEBUG_PRINT_PAR(x) printf("%s",x)
    #else
    #define DEBUG_PRINT_PAR(x)
    #endif

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

%type <expr> expression literal t f g h i j

%start S
%% /* grammar */

S:
  /* %empty */            {DEBUG_PRINT_PAR("Empty\n");}
  | sentences ;
;

sentences:
  sentence              {DEBUG_PRINT_PAR("Sentence:\n");}
  | sentence sentences  {DEBUG_PRINT_PAR("Sentence:\n");}

sentence:
  varDecl
  | varAssign
  | expression

varDecl:
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression {
    printf("Variable %s Type %s = ", $1, $3);
    printExpression($5);
}
  | IDENTIFIER ASSIGNTOK TYPETOK {
    printf("Variable %s Type %s (noVal)\n", $1, $3);
}
  | IDENTIFIER ASSIGEQUALS expression {
    printf("Variable %s, auto, = \n", $1);
    printExpression($3);
}
;

varAssign:
  IDENTIFIER EQUALS expression                      {printf("Variable %s =", $1);}
;

expression: expression PLUS t {
  Type e = getType($1), t = getType($3);
  if (e == INT && t == INT) {
    $$ = createInt($1->value._int + $3->value._int);
  } else if (e == DOUBLE && t == DOUBLE) {
    $$ = createDouble($1->value._double + $3->value._double);
  } else if (e == INT && t == DOUBLE) {
    $$ = createDouble($1->value._int + $3->value._double);
  } else if (e == DOUBLE && t == INT) {
    $$ = createDouble($1->value._double + $3->value._int);
  } else {
    printf("Error, de tipado. No es posible sumar un %s con un %s",strType[e], strType[t]);
    return -1;
  }
}
  | t {$$ = $1;}
  ;
t: t MINUS f {
  Type t = getType($1), f = getType($3);
  if (t == INT && f == INT) {
    $$ = createInt($1->value._int - $3->value._int);
  } else if (t == DOUBLE && f == DOUBLE) {
    $$ = createDouble($1->value._double - $3->value._double);
  } else if (t == INT && f == DOUBLE) {
    $$ = createDouble($1->value._int - $3->value._double);
  } else if (t == DOUBLE && f == INT) {
    $$ = createDouble($1->value._double - $3->value._int);
  } else {
    printf("Error, de tipado. No es posible restar un %s con un %s",strType[t], strType[f]);
    return -1;
  }
}
  | f {$$ = $1;}
  ;
f: f BY g {
  Type f = getType($1), g = getType($3);
  if (f == INT && g == INT) {
    $$ = createInt($1->value._int * $3->value._int);
  } else if (f == DOUBLE && g == DOUBLE) {
    $$ = createDouble($1->value._double * $3->value._double);
  } else if (f == INT && g == DOUBLE) {
    $$ = createDouble($1->value._int * $3->value._double);
  } else if (f == DOUBLE && g == INT) {
    $$ = createDouble($1->value._double * $3->value._int);
  } else {
    printf("Error, de tipado. No es posible multiplicar un %s con un %s",strType[f], strType[g]);
    return -1;
  }
}
  | g {$$ = $1;}
  ;
g: g DIVIDE h {
  Type g = getType($1), h = getType($3);
  if (g == INT && h == INT) {
    $$ = createInt($1->value._int / $3->value._int);
  } else if (g == DOUBLE && h == DOUBLE) {
    $$ = createDouble($1->value._double / $3->value._double);
  } else if (g == INT && h == DOUBLE) {
    $$ = createDouble($1->value._int / $3->value._double);
  } else if (g == DOUBLE && h == INT) {
    $$ = createDouble($1->value._double / $3->value._int);
  } else {
    printf("Error, de tipado. No es posible dividir un %s con un %s",strType[g], strType[h]);
    return -1;
  }
}
  | h {$$ = $1;}
  ;
h: h BINARYOP i {
  printf("NOT IMPLEMENTED YET");
  return -1;
}
  | i {$$ = $1;}
  ;
i: MINUS j {
  Type j = getType($2);
  if(j == INT){
    $$ = createInt(-$2->value._int);
  } else if (j == DOUBLE){
    $$ = createDouble(-$2->value._double);
  } else {
    printf("Error, de tipado. No es posible poner un %s negativo",strType[j]);
    return -1;
  }
}
  | j {$$ = $1;}
  ;
j: OPPARTH expression CLOSPARTH {$$ = $2;}
  | literal {$$ = $1;}
  //| IDENTIFIER
  ;
literal:
  ENTERO | DOBLE | CARACTER | PROPOSICION {$$ = $1;}
  //| STRING
;
/*
expression:
  OPPARTH expression CLOSPARTH                      {DEBUG_PRINT_PAR("(s)");}
  | expression PLUS expression
  | expression MINUS expression
  | expression MULTIPLICAR expression
  | expression DIVIDE expression
  | MINUS expression  %prec NEG                       {DEBUG_PRINT_PAR("-_");}
  | binaryOp
  | IDENTIFIER                                      {DEBUG_PRINT_PAR("Identifier s");}
  | literal                                         {DEBUG_PRINT_PAR("Literal: s");}
;
*/


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
