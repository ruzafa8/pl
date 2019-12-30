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
    char* valString;
    int valInt;
}

%locations

%token <valString> IDENTIFIER
%token ASSIGNTOK
%token <valString> TYPETOK           //Enum?
%token EQUALS
%token ASSIGEQUALS
%token OPPARTH
%token CLOSPARTH
%token <valInt> NUMBER
%token <valString> STRING
%token TRUE
%token FALSE

%left <valString> BINARYOP
%left PLUS  MINUS
%left MULTIPLICAR  DIVIDE
%precedence NEG   /* negation--unary minus */

%start S
%% /* grammar */

S:
  %empty            {DEBUG_PRINT_PAR("Empty\n");}
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
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression    {printf("Variable %s Type %s = \n", $1, $3);}
  | IDENTIFIER ASSIGNTOK TYPETOK                    {printf("Variable %s Type %s (noVal)\n", $1, $3);}
  | IDENTIFIER ASSIGEQUALS expression               {printf("Variable %s, auto, = \n", $1);}
;

varAssign:
  IDENTIFIER EQUALS expression                      {printf("Variable %s =", $1);}
;

literal:
  NUMBER | STRING | TRUE | FALSE
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

expression: expression PLUS t | t
t: t MINUS f | f
f: f MULTIPLICAR g | g
g: g DIVIDE h | h
h: h BINARYOP i | i
i: OPPARTH expression CLOSPARTH | literal | IDENTIFIER

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
