%{
    #include <stdio.h>
    #include <string.h>
    void yyerror (char const *);
    extern int yylineno;
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
%left <valString> BINARYOP
%token <valInt> NUMBER
%token <valString> STRING
%token TRUE
%token FALSE

%left "+"  "-"
%left "*"  "/"
%left UMINUS


%start S
%% /* grammar */

S:
  %empty            {printf("Empty\n");}
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
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression    {printf("Variable s Type t =");}
  | IDENTIFIER ASSIGNTOK TYPETOK                    {printf("Variable s Type t (noVal)\n");}
  | IDENTIFIER ASSIGEQUALS expression               {printf("Variable s, auto, =");}
;

varAssign:
  IDENTIFIER EQUALS expression                      {printf("Variable s =");}
;

literal:
  NUMBER | STRING | TRUE | FALSE
;

expression:
  OPPARTH expression CLOSPARTH                      {printf("(s)");}
  | expression "+" expression
  | expression "-" expression
  | expression "*" expression
  | expression "/" expression 
  | UMINUS expression                              {printf("-_");}
  | binaryOp
  | IDENTIFIER                                      {printf("Identifier s");}
  | literal                                         {printf("Literal: s");}
;

binaryOp:
  expression BINARYOP expression

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
