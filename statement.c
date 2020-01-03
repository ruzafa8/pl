#include "statement.h"

Statement * createDecl(char * name, Type type, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL;
  st->st._decl.name = strdup(name);
  st->st._decl.type = type;
  st->line = line;
  return st;
}
Statement * createAsig(char * name, ExpressionStatement * e, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = ASIG;
  st->st._asig.name = strdup(name);
  st->st._asig.e = e;
  st->line = line;
  return st;
}
Statement * createDeclAsig(char *name, Type t, ExpressionStatement * e, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = DECL_ASIG;
  st->st._decl_asig.name = strdup(name);
  st->st._decl_asig.type = t;
  st->st._decl_asig.e = e;
  st->line = line;
  return st;
}
Statement * createPrint(ExpressionStatement * e, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = PRINT;
  st->st._print.e = e;
  st->line = line;
  return st;
}
Statement * createWhile(ExpressionStatement * condition, Statement * body, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = WHILE;
  st->st._while.condition = condition;
  st->st._while.body = st;
  st->line = line;
  return st;
}
Statement * createRepeat(ExpressionStatement * numIteracions, Statement * body, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = REPEAT;
  st->st._repeat.numIteracions = numIteracions;
  st->st._repeat.body = body;
  st->line = line;
  return st;
}

Statement * createIf(ExpressionStatement * condition, Statement * body, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = IF;
  st->st._if.cond = condition;
  st->st._if.body = body;
  st->line = line;
  return st;
}
Statement * createIfElse(ExpressionStatement * condition, Statement * then_st, Statement * else_st, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = IF_ELSE;
  st->st._if_else.cond = condition;
  st->st._if_else.if_statement = then_st;
  st->st._if_else.else_statement = else_st;
  st->line = line;
  return st;
}

InitiationList * createInitiationList(ExpressionStatement * exp, InitiationList * n){
  InitiationList * initList = (InitiationList *) malloc(sizeof(InitiationList));
  initList->e = exp;
  initList->next = n;
  return initList;
}


Statement * join(Statement * s1, Statement * s2){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = COMPOSE;
  st->st._compose.s1 = s1;
  st->st._compose.s2 = s2;
  return st;
}

void execDecl(Table table, Decl st, int line){
  EXIT_CODE code;
  switch(st.type){
     case    INT: code = addDefaultInt(table, st.name);    break;
     case DOUBLE: code = addDefaultDouble(table, st.name); break;
     case   BOOL: code = addDefaultBool(table, st.name);   break;
     case   CHAR: code = addDefaultChar(table, st.name);   break;
     case UNKNOWN: code = add(table,st.name);
   }
   switch(code){
     case SUCCESS: break;
     case VAR_ALREADY_EXISTS_ERROR:
       printf("Error línea %d, la variable %s ya existe",line,st.name);
       break;
   }
}

void execAsig(Table table, Asig st, int line){
  Expression *e = evaluate(table,st.e);
  EXIT_CODE code;
  switch(getType(e)){
    case    INT: code = changeInt(table,st.name,e->value._int); break;
    case   BOOL: code = changeBool(table,st.name,e->value._bool); break;
    case   CHAR: code = changeChar(table,st.name,e->value._char); break;
    case DOUBLE: code = changeDouble(table,st.name,e->value._double); break;

  }
  Expression * var;
  switch(code){
    case SUCCESS: break;
    case TYPE_DOESNT_AGREE:
      valueOf(table,st.name,&var);
      printf("Error linea %d, se ha intentado asignar un %s a la variable %s pero es de tipo %s",
             line,strType[getType(e)],st.name,strType[getType(var)]);
      break;
    case VAR_NOT_FOUND_ERROR:
      printf("Error linea %d, la variable %s no existe", line, st.name);
      break;
  }
}

void execDeclAsig(Table table, Decl_Asig st, int line){
  EXIT_CODE code;
  Expression * e = evaluate(table,st.e);
  if(st.type == getType(e) || st.type == UNKNOWN)
  switch(getType(e)){
    case    INT: code = addInt(table, st.name, e->value._int);       break;
    case DOUBLE: code = addDouble(table, st.name, e->value._double); break;
    case   BOOL: code = addBool(table, st.name, e->value._bool);     break;
    case   CHAR: code = addChar(table, st.name, e->value._char);     break;
  }

  switch (code) {
    case SUCCESS: break;
    case VAR_ALREADY_EXISTS_ERROR:
      printf("Error línea %d, la variable %s ya existe",line,st.name);
      break;
  }
}

void execWhile(Table table, While st, int line){
  EXIT_CODE code;
  Expression *e = evaluate(table,st.condition);
  if(getType(e) == BOOL){
    while(e->value._bool == TRUE){
      exec(table,st.body);
    }
  } else {
    printf("Error línea %d, se esperaba una Proposicion, pero se encontró %s",line,strType[getType(e)]);
  }
}

void execRepeat(Table table, Repeat st, int line){
  EXIT_CODE code;
  Expression *e = evaluate(table, st.numIteracions);
  if(getType(e) == INT){
    int numIt;
    getInt(e,&numIt);
    for(int i = 0; i < numIt; i++){
      exec(table,st.body);
    }
  } else {
    printf("Error línea %d, se esperaba un Entero, pero se encontró %s",line,strType[getType(e)]);
  }
}
void execIf(Table table, If st, int line){
  EXIT_CODE code;
  Expression *e = evaluate(table,st.cond);
  if(getType(e) == BOOL){
    if(e->value._bool == TRUE){
      exec(table,st.body);
    }
  } else {
    printf("Error línea %d, se esperaba una Proposicion, pero se encontró %s",line,strType[getType(e)]);
  }
}
void execIfElse(Table table, If_else st, int line){
  EXIT_CODE code;
  Expression *e = evaluate(table,st.cond);
  if(getType(e) == BOOL){
    if(e->value._bool == TRUE){
      exec(table,st.if_statement);
    } else {
      exec(table,st.else_statement);
    }
  } else {
    printf("Error línea %d, se esperaba una Proposicion, pero se encontró %s",line,strType[getType(e)]);
  }
}
void exec(Table table, Statement * s){
  EXIT_CODE code;
  Expression * e;
  switch(s->type){
    case      DECL: execDecl(table,s->st._decl,s->line);             break;
    case      ASIG: execAsig(table, s->st._asig,s->line);            break;
    case DECL_ASIG: execDeclAsig(table,s->st._decl_asig, s->line);   break;
    case     PRINT: printExpression(evaluate(table,s->st._print.e)); break;
    case     WHILE: execWhile(table, s->st._while,s->line);          break;
    case    REPEAT: execRepeat(table, s->st._repeat,s->line);        break;
    case        IF: execIf(table, s->st._if, s->line);               break;
    case   IF_ELSE: execIfElse(table, s->st._if_else, s->line);      break;
    case   COMPOSE:
      exec(table,s->st._compose.s1);
      exec(table,s->st._compose.s2);
      break;
  }
}
