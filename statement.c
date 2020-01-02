#include "statement.h"

Statement * createDecl(char * name, Type type){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._decl.name = strdup(name);
  st->st._decl.type = type;
  return st;
}
Statement * createAsig(char * name, ExpressionStatement * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._asig.name = strdup(name);
  st->st._asig.e = e;
  return st;
}
Statement * createDeclAsig(char *name, Type t, ExpressionStatement * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL_ASIG;
  st->st._decl_asig.name = strdup(name);
  st->st._decl_asig.type = t;
  st->st._decl_asig.e = e;
  return st;
}
Statement * createPrint(ExpressionStatement * e){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = PRINT;
  st->st._print.e = e;
  return st;
}
Statement * createWhile(ExpressionStatement * condition, Statement * body){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = WHILE;
  st->st._while.condition = condition;
  st->st._while.body = st;
  return st;
}
Statement * createRepeat(ExpressionStatement * numIteracions, Statement * body){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = REPEAT;
  st->st._repeat.numIteracions = numIteracions;
  st->st._repeat.body = body;
  return st;
}

Statement * createIf(ExpressionStatement * condition, Statement * body){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = IF;
  st->st._if.cond = condition;
  st->st._if.body = body;
  return st;
}
Statement * createIfElse(ExpressionStatement * condition, Statement * then_st, Statement * else_st){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = IF_ELSE;
  st->st._if_else.cond = condition;
  st->st._if_else.if_statement = then_st;
  st->st._if_else.else_statement = else_st;
  return st;
}

Statement * join(Statement * s1, Statement * s2){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = COMPOSE;
  st->st._compose.s1 = s1;
  st->st._compose.s2 = s2;
  return st;
}

void exec(Table table, Statement * s){
  EXIT_CODE code;
  Expression * e;
  switch(s->type){
    case DECL: switch(s->st._decl.type){
        case    INT: code = addDefaultInt(table, s->st._decl.name);    break;
        case DOUBLE: code = addDefaultDouble(table, s->st._decl.name); break;
        case   BOOL: code = addDefaultBool(table, s->st._decl.name);   break;
        case   CHAR: code = addDefaultChar(table, s->st._decl.name);   break;
        case UNKNOWN: code = add(table,s->st._decl.name);
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case ASIG:
      e = evaluate(table,s->st._asig.e);
      switch(getType(e)){
        case    INT: code = changeInt(table,s->st._asig.name,e->value._int); break;
        case   BOOL: code = changeBool(table,s->st._asig.name,e->value._bool); break;
        case   CHAR: code = changeChar(table,s->st._asig.name,e->value._char); break;
        case DOUBLE: code = changeDouble(table,s->st._asig.name,e->value._double); break;
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case DECL_ASIG:
      e = evaluate(table,s->st._decl_asig.e);
      if(s->st._decl_asig.type == getType(e) || s->st._decl_asig.type == UNKNOWN)
      switch(getType(e)){
        case    INT: code = addInt(table, s->st._decl_asig.name, e->value._int);       break;
        case DOUBLE: code = addDouble(table, s->st._decl_asig.name, e->value._double); break;
        case   BOOL: code = addBool(table, s->st._decl_asig.name, e->value._bool);     break;
        case   CHAR: code = addChar(table, s->st._decl_asig.name, e->value._char);     break;
        default    : code = TYPE_NOT_EXISTS;
      } break;
    case PRINT:
      printExpression(table,evaluate(s->st._print.e));
      break;
    case WHILE:
      e = evaluate(table,s->st._while.condition);
      if(getType(e) == BOOL){
        while(e->value._bool == TRUE){
          exec(table,s->st._while.body);
        }
      } else{
        //error
      }

      break;
    case REPEAT:
      e = evaluate(table, s->st._repeat.numIteracions);
      if(getType(e) == INT){
        int numIt;
        getInt(e,&numIt);
        for(int i = 0; i < numIt; i++){
          exec(table,s->st._repeat.body);
        }
      } else {
        //ERROR DE TIPAO
      }
      break;
    case IF:
      e = evaluate(s->st._if.cond);
      if(getType(e) == BOOL){
        if(e->value._bool == TRUE){
          exec(table,s->st._if.body);
        }
      }
      break;
    case IF_ELSE:
      e = evaluate(s->st._if_else.cond);
      if(getType(e) == BOOL){
        if(e->value._bool == TRUE){
          exec(table,s->st._if_else.if_statement);
        } else {
          exec(table,s->st._if_else.else_statement);
        }
      }
      break;
    case COMPOSE:
      exec(table,s->st._compose.s1);
      exec(table,s->st._compose.s2);
      break;
  }
}
