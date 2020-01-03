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

Statement * createArrayAccessorAsig(char * name, ExpressionStatement * accessor, ExpressionStatement * e, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  st->type = ARRAY_ACC_ASIG;
  st->st._array_acc_asig.name = strdup(name);
  st->st._array_acc_asig.acc = accessor;
  st->st._array_acc_asig.e = e;
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

Statement * createDeclAsigArray(char * name, ExpressionStatement * arraySize, Type t, InitiationList * initList, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  int size = const_int_eval(arraySize);
  if(size == 0) {
      InitiationList * p = initList;
      while(p!=NULL){
          p=p->next;
          size++;
      }
  }
  st->type = ARRAY_DECL_ASIG;
  st->st._array_decl_asig.name = strdup(name);
  st->st._array_decl_asig.type = t;
  st->st._array_decl_asig.arraySize = size;
  st->st._array_decl_asig.initList = initList;

  st->line = line;
  return st;
}
Statement * createDeclArray(char * name, ExpressionStatement * arraySize, Type t, int line){
  Statement * st = (Statement *) malloc(sizeof(Statement));
  int size = const_int_eval(arraySize);
  st->type = ARRAY_DECL;
  st->type == ARRAY_DECL;
  st->st._array_decl.name = strdup(name);
  st->st._array_decl.type = t;
  st->st._array_decl.arraySize = size;
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
  st->st._while.body = body;
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

void testInitiationList(InitiationList * n) {
  if(n == NULL)
    printf("NULL LIST\n");
  else {
    printf("List node: ");
    if(n->e == NULL) {
        printf("e==Null");
    } else {
        printf("e not null");
    }
    testInitiationList(n->next);
  }
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
  EXIT_CODE code = SUCCESS;
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

void execArrayDeclAsig(Table table, Array_Decl_Asig st, int line){
  EXIT_CODE code;
  Type t = st.type;
  //Walking and autotyping the array
  InitiationList *p = st.initList;
  while(p!=NULL){
    if(p->e == NULL)
      p=p->next;
    else {
      Expression * expr = evaluate(table, p->e);
      if(t != UNKNOWN)
        t = getType(expr);
      else if(t!= getType(expr)) {
        t == UNKNOWN;
        break;
      }
      p=p->next;
    }
  }

  if(t == UNKNOWN) {
    printf("Error línea %d, la lista de inicialización de la variable %s no es valida",line,st.name);
  } else {
    //Actual assignation
    InitiationList *p = st.initList;
    int i = 0;
    Expression * expr;
    //value list
    switch(t){
        case    INT:
            ;// https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
            int *intlist = malloc(sizeof(int)*st.arraySize);
            while(p!=NULL){
              if(p->e == NULL) {
                  intlist[i] = 0;
              } else {
                  expr = evaluate(table, p->e);
                  intlist[i] = expr->value._int;
              }
              p=p->next;
              i++;
            }
            code = addArrayInt(table, st.name, intlist, st.arraySize);
            break;
        case DOUBLE:
            ;// https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
            double* doublelist = malloc(sizeof(double)*st.arraySize);
            while(p!=NULL){
              if(p->e == NULL) {
                  doublelist[i] = 0.0;
              } else {
                  expr = evaluate(table, p->e);
                  doublelist[i] = expr->value._double;
              }
              p=p->next;
              i++;
            }
            code = addArrayDouble(table, st.name, doublelist, st.arraySize);
            break;
        case BOOL:
            ;// https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
            Bool* boollist = malloc(sizeof(Bool)*st.arraySize);
            while(p!=NULL){
              if(p->e == NULL) {
                  boollist[i] = FALSE;
              } else {
                  expr = evaluate(table, p->e);
                  boollist[i] = expr->value._bool;
              }
              p=p->next;
              i++;
            }
            code = addArrayBool(table, st.name, boollist, st.arraySize);
            break;
        case CHAR:
            ;// https://stackoverflow.com/questions/18496282/why-do-i-get-a-label-can-only-be-part-of-a-statement-and-a-declaration-is-not-a
            char* charlist = malloc(sizeof(char)*st.arraySize);
            while(p!=NULL){
              if(p->e == NULL) {
                  charlist[i] = '\0';
              } else {
                  expr = evaluate(table, p->e);
                  charlist[i] = expr->value._char;
              }
              p=p->next;
              i++;
            }
            code = addArrayChar(table, st.name, charlist, st.arraySize);
            break;

    }
    switch (code) {
        case SUCCESS: break;
        case VAR_ALREADY_EXISTS_ERROR:
          printf("Error línea %d, la variable array %s ya existe",line,st.name);
          break;
    }
  }
}

void execArrayDecl(Table table, Array_Decl st, int line){
  EXIT_CODE code = SUCCESS;

  if(st.type == UNKNOWN) {
    printf("Error línea %d, el tipo de la variable array %s no es valido",line,st.name);
  } else if (st.arraySize ==0){
    printf("Error línea %d, el tamaño de la variable array %s no puede ser cero",line,st.name);
  } else {
    switch(st.type){
        case    INT:
            code = addDefaultArrayInt(table, st.name, st.arraySize);
            break;
        case DOUBLE:
            code = addDefaultArrayDouble(table, st.name, st.arraySize);
            break;
        case BOOL:
            code = addDefaultArrayBool(table, st.name, st.arraySize);
            break;
        case CHAR:
            code = addDefaultArrayChar(table, st.name, st.arraySize);
            break;
    }

  }
  switch (code) {
    case SUCCESS: break;
    case VAR_ALREADY_EXISTS_ERROR:
      printf("Error línea %d, la variable array %s ya existe",line,st.name);
      break;
  }

}

void execArrayAccAsig(Table table, Array_Acc_Asig st, int line){
  EXIT_CODE code;
  int accessor;
  Expression *e = evaluate(table,st.e);
  Expression *acc = evaluate(table,st.acc);

  switch(getType(acc)){
    case    INT: accessor = acc->value._int; break;
    default:
        printf("Error linea %d, accesores a array solo pueden ser enteros pero es de tipo %s",line,strType[getType(acc)]);
        return;
  }

  switch(getType(e)){
    case    INT: code = changeArrayInt(table,st.name,e->value._int, accessor);       break;
    case   BOOL: code = changeArrayBool(table,st.name,e->value._bool, accessor);     break;
    case   CHAR: code = changeArrayChar(table,st.name,e->value._char, accessor);     break;
    case DOUBLE: code = changeArrayDouble(table,st.name,e->value._double, accessor); break;
  }
  Expression * var;
  int size;
  switch(code){
    case SUCCESS: break;
    case TYPE_DOESNT_AGREE:
      valueOfArray(table,st.name,&var,size);
      printf("Error linea %d, se ha intentado asignar un %s al array %s pero es de tipo %s",
             line,strType[getType(e)],st.name,strType[getType(var)]);
      break;
    case VAR_NOT_FOUND_ERROR:
      printf("Error linea %d, la variable %s no existe", line, st.name);
      break;
  }
}

void execWhile(Table table, While st, int line){
  EXIT_CODE code;
  Expression *e = evaluate(table,st.condition);
  if(getType(e) == BOOL){
    while(e->value._bool == TRUE){
      exec(table,st.body);
      e = evaluate(table,st.condition);
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
    case            DECL: execDecl(table,s->st._decl,s->line);                      break;
    case            ASIG: execAsig(table, s->st._asig,s->line);                     break;
    case      ARRAY_DECL: execArrayDecl(table, s->st._array_decl, s->line);         break;
    case ARRAY_DECL_ASIG: execArrayDeclAsig(table, s->st._array_decl_asig, s->line);break;
    case  ARRAY_ACC_ASIG: execArrayAccAsig(table, s->st._array_acc_asig, s->line); break;
    case       DECL_ASIG: execDeclAsig(table,s->st._decl_asig, s->line);            break;
    case           PRINT: printExpression(evaluate(table,s->st._print.e));          break;
    case           WHILE: execWhile(table, s->st._while,s->line);                   break;
    case          REPEAT: execRepeat(table, s->st._repeat,s->line);                 break;
    case              IF: execIf(table, s->st._if, s->line);                        break;
    case         IF_ELSE: execIfElse(table, s->st._if_else, s->line);               break;
    case         COMPOSE:
      exec(table,s->st._compose.s1);
      exec(table,s->st._compose.s2);
      break;
  }
}
