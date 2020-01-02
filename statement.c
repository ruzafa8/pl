#include "statement.h"

Statement * createDecl(char * name, Type type){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._decl.name = strdup(name);
  st->st._decl.type = type;
  return st;
}
Statement * createAsig(char * name, Expression * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._asig.name = strdup(name);
  st->st._asig.e = e;
  return st;
}
Statement * createDeclAsig(char *name, Type t, Expression * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._decl_asig.name = strdup(name);
  st->st._decl_asig.type = type;
  return st;
}
Statement * createPrint(Expression * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = PRINT;
  st->st._print.e = e;
  return st;
}
Statement * createWhile();
Statement * createIf();
Statement * createIfElse();

Statement * join(Statement * s1, Statement * s2);

void exec(Table table, Statement * s){
  EXIT_CODE code;
  switch(s->type){
    case DECL: switch(s->st._decl.type){
        case    INT: code = addDefaultInt(table, s->st._decl.name);    break;
        case DOUBLE: code = addDefaultDouble(table, s->st._decl.name); break;
        case   BOOL: code = addDefaultBool(table, s->st._decl.name);   break;
        case   CHAR: code = addDefaultChar(table, s->st._decl.name);   break;
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case ASIG: switch(getType(s->st._asig.e)){
        case    INT: code = changeInt(table,s->st._asig.name,s->st._asig.e->value._int); break;
        case   BOOL: code = changeBool(table,s->st._asig.name,s->st._asig.e->value._bool); break;
        case   CHAR: code = changeChar(table,s->st._asig.name,s->st._asig.e->value._char); break;
        case DOUBLE: code = changeDouble(table,s->st._asig.name,s->st._asig.e->value._double); break;
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case DECL_ASIG: switch(getType(s->st._decl_asig.e)){
        case    INT: code = addInt(table, s->st._decl_asig.name, s->st._decl_asig.e->value._int);       break;
        case DOUBLE: code = addDouble(table, s->st._decl_asig.name, s->st._decl_asig.e->value._double); break;
        case   BOOL: code = addBool(table, s->st._decl_asig.name, s->st._decl_asig.e->value._bool);     break;
        case   CHAR: code = addChar(table, s->st._decl_asig.name, s->st._decl_asig.e->value._char);     break;
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case PRINT:
      printExpression(s->st._print.e);
      break;
    case WHILE: break;
    case REPEAT: break;
    case IF: break;
    case IF_ELSE: break;
    case COMPOSE:
      exec(s->st._compose->s1);
      exec(s->st._compose->s2);
      break;
  }
}
