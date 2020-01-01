%{
    #include <stdio.h>
    #include <string.h>
    #include "hash_table.h"

    #ifdef PAR_DEBUG
    #define DEBUG_PRINT_PAR(x) printf(x)
    #define DEBUG_PRINT_EXPRESSION(x) printExpression(x)
    #define DEBUG_MODE 0
    #else
    #define DEBUG_PRINT_PAR(x)
    #define DEBUG_PRINT_EXPRESSION(x)
    #define DEBUG_MODE 1
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
  Expression * expr;
}

%code requires {
  #include "hash_table.h"
}

%locations

%token <valString> IDENTIFIER
%token IMPRIMIR
%token ASSIGNTOK
%token <type> TYPETOK           //Enum?
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
  | IMPRIMIR expression {
      DEBUG_PRINT_PAR("Imprimir:\n");
      printExpression($2);
    }

varDecl:
  IDENTIFIER ASSIGNTOK TYPETOK EQUALS expression {
    EXIT_CODE code;
    Type t = getType($5);
    if($3 != t){
      code = TYPE_DOESNT_AGREE;
    } else switch(t){
      case    INT: code = addInt(table, $1, $5->value._int);       break;
      case DOUBLE: code = addDouble(table, $1, $5->value._double); break;
      case   BOOL: code = addBool(table, $1, $5->value._bool);     break;
      case   CHAR: code = addChar(table, $1, $5->value._char);     break;
      default    : code = TYPE_NOT_EXISTS;
    }
    if(readExitCodeVariables(code, $1, t, $3) == 1){
      return -1;
    }
}
  | IDENTIFIER ASSIGNTOK TYPETOK {
    EXIT_CODE code;
    switch($3){
      case    INT: code = addDefaultInt(table, $1);    break;
      case DOUBLE: code = addDefaultDouble(table, $1); break;
      case   BOOL: code = addDefaultBool(table, $1);   break;
      case   CHAR: code = addDefaultChar(table, $1);   break;
      default    : code = TYPE_NOT_EXISTS;
    }
    if(readExitCodeVariables(code, $1, $3 ,$3) == 1){
      return -1;
    }
}
  | IDENTIFIER ASSIGEQUALS expression {
    EXIT_CODE code;
    Type t = getType($3);
    switch(t){
      case    INT: code = addInt(table, $1, $3->value._int);       break;
      case DOUBLE: code = addDouble(table, $1, $3->value._double); break;
      case   BOOL: code = addBool(table, $1, $3->value._bool);     break;
      case   CHAR: code = addChar(table, $1, $3->value._char);     break;
      default    : code = TYPE_NOT_EXISTS;
    }
    if(readExitCodeVariables(code, $1,t,t) == 1){
      return -1;
    }
  }
  | IDENTIFIER ASSIGNTOK {
    EXIT_CODE code = add(table, $1);
  }
;

varAssign:
  IDENTIFIER EQUALS expression {
    EXIT_CODE code;
    switch(getType($3)){
      case    INT: code = changeInt(table,$1,$3->value._int); break;
      case   BOOL: code = changeBool(table,$1,$3->value._bool); break;
      case   CHAR: code = changeChar(table,$1,$3->value._char); break;
      case DOUBLE: code = changeDouble(table,$1,$3->value._double); break;
      default    : code = TYPE_NOT_EXISTS;
    }
    Expression *e;
    valueOf(table, $1, &e);
    if(readExitCodeVariables(code, $1, getType($3), getType(e)) == 1){
      return -1;
    }
  }
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
  } else if(e == INT || e == DOUBLE || e == BOOL || e == CHAR &&
            t == INT || t == DOUBLE || t == BOOL || t == CHAR){
    readExitCodeType(TYPE_ERROR,e,t);
    return -1;
  } else {
    readExitCodeType(TYPE_DOESNT_AGREE, e,t);
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
  } else if(f == INT || f == DOUBLE || f == BOOL || f == CHAR &&
            t == INT || t == DOUBLE || t == BOOL || t == CHAR){
    readExitCodeType(TYPE_ERROR,f,t);
    return -1;
  } else {
    readExitCodeType(TYPE_DOESNT_AGREE, f,t);
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
  } else if(f == INT || f == DOUBLE || f == BOOL || f == CHAR &&
            g == INT || g == DOUBLE || g == BOOL || g == CHAR){
    readExitCodeType(TYPE_ERROR,f,g);
    return -1;
  } else {
    readExitCodeType(TYPE_DOESNT_AGREE, f,g);
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
  yyerror("NOT IMPLEMENTED YET");
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
    ("Error, de tipado. No es posible poner un %s negativo",strType[j]);
    return -1;
  }
}
  | j {$$ = $1;}
  ;
j: OPPARTH expression CLOSPARTH {$$ = $2;}
  | literal {$$ = $1;}
  | IDENTIFIER {
    Expression * e;
    EXIT_CODE code = valueOf(table, $1, &e);
    if(readExitCodeVariables(code, $1,getType(e),getType(e)) == 1){
      return -1;
    }
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
      return ret;
  } else {
    printf("Usage: cosa filename\n");
    return 0;
  }
}
