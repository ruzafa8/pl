%{
    #include <stdio.h>
    #include <string.h>
    #include "hash_table.h"

    #include "bool.h"

    #ifdef PAR_DEBUG
    #define DEBUG_PRINT_PAR(x) printf(x)
    #define DEBUG_PRINT_EXPRESSION(x) printExpression(x)
    #define DEBUG_MODE 1
    #else
    #define DEBUG_PRINT_PAR(x)
    #define DEBUG_PRINT_EXPRESSION(x)
    #define DEBUG_MODE 0
    #endif

    int readExitCodeType(EXIT_CODE, Type, Type);
    int readExitCodeVariables(EXIT_CODE, char *, Type, Type);
    void yyerror (char const *);
    extern int yylineno;
    extern int yylex();
    Table table;
%}


%union{
    char * valString;
    Type type;
    Statement * statement;
    ExpressionStatement * expr;
}
/*union{
  char * valString;
  Type type;
  Expression * expr;
}*/

%code requires {
  #include "hash_table.h"
  #include "statement.h"
  #include "ExpressionStatement.h"
}

%locations

%token <valString> IDENTIFIER
%token IMPRIMIR
%token IFTOK THENTOK ELSETOK
%token ASSIGNTOK
%token <type> TYPETOK           //Enum?
%token EQUALS
%token ASSIGEQUALS
%token <valString> STRING

%token PLUSTOK MINUSTOK BYTOK DIVIDETOK OPPARTH CLOSPARTH
%token ORTOK ANDTOK XORTOK SITOK SIITOK LESSTOK LESS_EQTOK MORETOK MORE_EQTOK NOT_EQTOK DOBLE_EQUALSTOK
%token <expr> ENTERO DOBLE CARACTER PROPOSICION
%token HAZ MIENTRAS PUNTO

%type <expr> expression literal o p q r s t u v w x y z f g h i
%type <statement> varDecl varAssign sentence sentences while_sentence conditional
%start S
%% /* grammar */

S:
  /* %empty */            {DEBUG_PRINT_PAR("Empty\n");}
  | sentences {exec(table,$1);};
;

sentences:
  sentence              {DEBUG_PRINT_PAR("Sentence:\n"); $$ = $1;}
  | sentence sentences  {DEBUG_PRINT_PAR("Sentence:\n"); $$ = join($1,$2);}

sentence:
  varDecl
  | varAssign {$$ = $1;}
  | conditional
  | IMPRIMIR expression {
      DEBUG_PRINT_PAR("Imprimir:\n");
      $$ = createPrint($2);
    }
  | while_sentence  {$$ = $1;}
  //| repeat

while_sentence: MIENTRAS expression HAZ sentences PUNTO {
  $$ = createWhile($2, $4);
}
varDecl:
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression {
    $$ = createDeclAsig($1,$3,$5);
}
  | IDENTIFIER ASSIGNTOK TYPETOK {
    $$ = createDecl($1,$3);
}
  | IDENTIFIER ASSIGEQUALS expression {
    $$ = createDeclAsig($1,getType($3),$3);
  }
  | IDENTIFIER ASSIGNTOK {
    $$ = createDecl($1, UNKNOWN);
  }
;

varAssign:
  IDENTIFIER EQUALS expression {
    $$ = createAsig($1, $3);
  }
;

conditional:
  IFTOK expression THENTOK sentences {}
 | IFTOK expression THENTOK sentences ELSETOK sentences {}

expression: expression ORTOK o {
    $$ = createBinExpression(BIN_OR, $1, $3);
}
 | o {$$ = $1;}
 ;
o: o ANDTOK p {
    $$ = createBinExpression(BIN_AND, $1, $3);
}
 | p {$$ = $1;}
 ;
p: p XORTOK q {
    $$ = createBinExpression(BIN_XOR, $1, $3);
}
 | q {$$ = $1;}
 ;
q: q SITOK r {
    $$ = createBinExpression(BIN_SI, $1, $3);
}
 | r {$$ = $1;}
 ;
r: r SIITOK s {
    $$ = createBinExpression(BIN_SII, $1, $3);
}
 | s {$$ = $1;}
 ;
s: s LESSTOK t {
    $$ = createBinExpression(BIN_LESS, $1, $3);
}
 | t {$$ = $1;}
 ;
t: t LESS_EQTOK u {
    $$ = createBinExpression(BIN_LESS_EQ, $1, $3);
}
 | u {$$ = $1;}
 ;
u: u MORETOK v {
    $$ = createBinExpression(BIN_MORE, $1, $3);
}
 | v {$$ = $1;}
 ;
v: v MORE_EQTOK w {
    $$ = createBinExpression(BIN_MORE_EQ, $1, $3);
}
 | w {$$ = $1;}
 ;
w: w NOT_EQTOK x {
    $$ = createBinExpression(BIN_NOT_EQ, $1, $3);
}
 | x {$$ = $1;}
 ;
x: x DOBLE_EQUALSTOK y {
    $$ = createBinExpression(BIN_DOBLE_EQUALS, $1, $3);
}
 | y {$$ = $1;}
 ;
y: y PLUSTOK z {
    $$ = createBinExpression(BIN_PLUS, $1, $3);
}
  | z {$$ = $1;}
  ;
z: z MINUSTOK f {
    $$ = createBinExpression(BIN_MINUS, $1, $3);
}
  | f {$$ = $1;}
  ;
f: f BYTOK g {
    $$ = createBinExpression(BIN_BY, $1, $3);
}
  | g {$$ = $1;}
  ;
g: g DIVIDETOK h {
    $$ = createBinExpression(BIN_DIVIDE, $1, $3);
}
  | h {$$ = $1;}
  ;
h: MINUSTOK i {
    $$ = createUnExpression(UN_MINUS, $2);
}
  | i {$$ = $1;}
  ;
i: OPPARTH expression CLOSPARTH {$$ = $2;}
  | literal {$$ = $1;}
  | IDENTIFIER {
    Expression * e = NULL;

    EXIT_CODE code = valueOf(table, $1, &e);
    if(DEBUG_MODE){
      printf("\nEXIT CODE DE VARIABLE %s = %d\n", $1, code);
    }

    if(e == NULL){
      readExitCodeVariables(VAR_NOT_FOUND_ERROR,$1, INT, INT);
      return -1;
    } else readExitCodeVariables(SUCCESS,$1, getType(e), getType(e));

    $$ = e;
  }
  ;
literal:
  ENTERO | DOBLE | CARACTER | PROPOSICION {$$ = $1;}
  //| STRING
;

%%
void yyerror (char const *message) { fprintf (stderr, "%s[%d]\n", message,yylineno);}
int readExitCodeType(EXIT_CODE code, Type e1, Type e2){
  int exitCode = 0;
  char error[100];
  switch(code){
    case SUCCESS: DEBUG_PRINT_EXPRESSION(e);break;
    case TYPE_NOT_EXISTS:
      sprintf(error,"Error linea %d, el tipo %s no existe\n",yylineno ,strType[e1]);
      yyerror(error); exitCode = 1; break;
    case CONDITION_NOT_BOOL:
      sprintf(error, "Error linea %d, operación condicional no definida para el tipo %s\n",yylineno ,strType[e1]);
      yyerror(error); exitCode = 1; break;
    case TYPE_ERROR:
      sprintf(error, "Error linea %d, operación no definida para los tipos %s y %s\n",yylineno ,strType[e1], strType[e2]);
      yyerror(error); exitCode = 1; break;
    case TYPE_DOESNT_AGREE:
      sprintf(error, "Error linea %d, los tipos no coinciden: %s, %s\n",yylineno ,strType[e1], strType[e2]);
      yyerror(error); exitCode = 1; break;
    default:
      yyerror("ERROR DE LA MUERTE");
      exitCode = 1;
  }
  return exitCode;
}
int readExitCodeVariables(EXIT_CODE code, char * var, Type exprType ,Type varType){
  char error[100];
  int exitCode = 0;
  switch(code){
    case SUCCESS:
      if(DEBUG_MODE){
        Expression * e;
        valueOf(table, var, &e);
        printf("Variable %s Type %s = ", var, strType[getType(e)]);
        printExpression(e);
      }
      break;
    case VAR_ALREADY_EXISTS_ERROR:
      sprintf(error,"Error linea %d, la variable %s ya existe\n",yylineno,var);
      yyerror(error); exitCode = 1; break;
    case VAR_NOT_FOUND_ERROR:
      sprintf(error, "Error linea %d, la variable %s no existe",yylineno,var);
      yyerror(error); exitCode = 1; break;
    default:
      exitCode = readExitCodeType(code, exprType, varType);
  }
  return code;
}

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
      table = createTable();
      ret = yyparse();
      fclose(yyin);
      printTable(table);
      return ret;
  } else {
    printf("Usage: cosa filename\n");
    return 0;
  }
}
