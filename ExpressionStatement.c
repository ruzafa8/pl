#include "ExpressionStatement.h"
int readExitCodeType(EXIT_CODE code, Type e1, Type e2){
  int exitCode = 0;
  switch(code){
    case SUCCESS:;break;
    case TYPE_ERROR:
      printf("Error linea, operación no definida para los tipos %s y %s\n" ,strType[e1], strType[e2]);
      exitCode = 1; break;
    case TYPE_DOESNT_AGREE:
      printf("Error linea, los tipos no coinciden: %s, %s\n" ,strType[e1], strType[e2]);
      exitCode = 1; break;
    default:
      printf("ERROR DE LA MUERTE");
      exitCode = 1;
  }
  return exitCode;
}
int readExitCodeVariables(EXIT_CODE code, char * var, Type exprType ,Type varType){
  int exitCode = 0;
  switch(code){
    case SUCCESS:
      break;
    case VAR_ALREADY_EXISTS_ERROR:
      printf("Error linea , la variable %s ya existe\n",var);
      exitCode = 1; break;
    case VAR_NOT_FOUND_ERROR:
      printf("Error linea, la variable %s no existe",var);
      exitCode = 1; break;
    default:
      exitCode = readExitCodeType(code, exprType, varType);
  }
  return code;
}

Expression * _eval_plus(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if (lhsType == INT && rhsType == INT) {
        return createInt(rhs->value._int + rhs->value._int);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE) {
        return createDouble(rhs->value._double + rhs->value._double);
    } else if (lhsType == INT && rhsType == DOUBLE) {
        return createDouble(rhs->value._int + rhs->value._double);
    } else if (lhsType == DOUBLE && rhsType == INT) {
        return createDouble(rhs->value._double + rhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_minus(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if (lhsType == INT && rhsType == INT) {
        return createInt(lhs->value._int - rhs->value._int);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE) {
        return createDouble(lhs->value._double - rhs->value._double);
    } else if (lhsType == INT && rhsType == DOUBLE) {
        return createDouble(lhs->value._int - rhs->value._double);
    } else if (lhsType == DOUBLE && rhsType == INT) {
        return createDouble(lhs->value._double - rhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_mult(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if (lhsType == INT && rhsType == INT) {
        return createInt(lhs->value._int * rhs->value._int);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE) {
        return createDouble(lhs->value._double * rhs->value._double);
    } else if (lhsType == INT && rhsType == DOUBLE) {
        return createDouble(lhs->value._int * rhs->value._double);
    } else if (lhsType == DOUBLE && rhsType == INT) {
        return createDouble(lhs->value._double * rhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_div(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);
    if (lhsType == INT && rhsType == INT) {
        return createInt(lhs->value._int / rhs->value._int);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE) {
        return createDouble(lhs->value._double / rhs->value._double);
    } else if (lhsType == INT && rhsType == DOUBLE) {
        return createDouble(lhs->value._int / rhs->value._double);
    } else if (lhsType == DOUBLE && rhsType == INT) {
        return createDouble(lhs->value._double / rhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_or(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == BOOL && rhsType == BOOL){
        return createBool(or(lhs->value._bool,rhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_and(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == BOOL && rhsType == BOOL){
        return createBool(and(lhs->value._bool,rhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_xor(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == BOOL && rhsType == BOOL){
        return createBool(xor(lhs->value._bool,rhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_si(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == BOOL && rhsType == BOOL){
        return createBool(si(lhs->value._bool,rhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_sii(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == BOOL && rhsType == BOOL){
        return createBool(sii(lhs->value._bool,rhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,lhsType,rhsType);
        exit(-1);
    }
}

Expression * _eval_less(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int < rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double < rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int < rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double < rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char < rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * _eval_less_eq(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int <= rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double <= rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int <= rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double <= rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char <= rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * _eval_more(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int > rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double > rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int > rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double > rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char > rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * _eval_more_eq(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int >= rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double >= rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int >= rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double >= rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char >= rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * _eval_not_eq(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int != rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double != rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int != rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double != rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char != rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * _eval_double_eq(Expression * lhs, Expression * rhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(lhsType == INT && rhsType == INT){
        return createBool(lhs->value._int == rhs->value._int ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == DOUBLE){
        return createBool(lhs->value._double == rhs->value._double ? TRUE : FALSE);
    } else if(lhsType == INT && rhsType == DOUBLE) {
        return createBool(lhs->value._int == rhs->value._double ? TRUE : FALSE);
    } else if (lhsType == DOUBLE && rhsType == INT){
        return createBool(lhs->value._double == rhs->value._int ? TRUE : FALSE);
    } else if(lhsType == CHAR && rhsType == CHAR){
        return createBool(lhs->value._char == rhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, lhsType, rhsType);
        exit(-1);
    }
}

Expression * binary_evaluate(Table table, BinExpressionStatement e){
    Expression * rhs = evaluate(table, e.rhs);
    Expression * lhs = evaluate(table, e.lhs);

    switch(e.kind){
        case(BIN_PLUS): return _eval_plus(lhs, rhs);
        case(BIN_MINUS): return _eval_minus(lhs, rhs);
        case(BIN_BY): return _eval_mult(lhs, rhs);
        case(BIN_DIVIDE): return _eval_div(lhs, rhs);
        case(BIN_OR): return _eval_or(lhs, rhs);
        case(BIN_AND): return _eval_and(lhs, rhs);
        case(BIN_XOR): return _eval_xor(lhs, rhs);
        case(BIN_SI): return _eval_si(lhs, rhs);
        case(BIN_SII): return _eval_sii(lhs, rhs);
        case(BIN_LESS): return _eval_less(lhs, rhs);
        case(BIN_LESS_EQ): return _eval_less_eq(lhs, rhs);
        case(BIN_MORE): return _eval_more(lhs, rhs);
        case(BIN_MORE_EQ): return _eval_more_eq(lhs, rhs);
        case(BIN_NOT_EQ): return _eval_not_eq(lhs, rhs);
        case(BIN_DOBLE_EQUALS): return _eval_double_eq(lhs, rhs);
    }
}

Expression * _un_eval_minus(Expression * e) {
    Type j = getType(e);
    if(j == INT){
        return createInt(-e->value._int);
    } else if (j == DOUBLE){
        return createDouble(-e->value._double);
    } else {
        printf("Error, de tipado. No es posible poner un %s negativo",strType[j]);
        exit(-1);
    }
}

Expression * unary_evaluate(Table table, UnExpressionStatement e) {
    Expression * expr = evaluate(table, e.e);

    switch(e.kind){
        case(UN_MINUS): return _un_eval_minus(expr);
    }
}

Expression * array_accessor_evaluate(Table table, ArrayAccessorExpressionStatement acc){
    Expression * res;
    int size;
    Expression * accessor = evaluate(table, acc.accessor);

    valueOfArray(table, acc.name, &res, &size);
    if(res == NULL) {
        readExitCodeVariables(VAR_NOT_FOUND_ERROR, acc.name,UNKNOWN,UNKNOWN);
        exit(-1);
    }

    return &res[accessor->value._int];
}

Expression * evaluate(Table table, ExpressionStatement * e){
    Expression * res = NULL;
    switch(e->_n){
        case UNARY:
            return unary_evaluate(table, e->_e._unary);
        case BINARY:
            return binary_evaluate(table, e->_e._binary);
        case LITERAL:
            return e->_e._lit.e;
        case VARIABLE:

          valueOf(table,e->_e._var.name,&res);
          if(res == NULL){
            readExitCodeVariables(VAR_NOT_FOUND_ERROR,e->_e._var.name,UNKNOWN,UNKNOWN);
            exit(-1);
          }
          return res;
        case ACCESSOR:
          return array_accessor_evaluate(table, e->_e._acc);
        default:
            printf("Expresion n-arity evaluation error\n");
            exit(-1);
    }
}

ExpressionStatement * createBinExpression(BinExpressionKind k, ExpressionStatement * lhs, ExpressionStatement * rhs){
    ExpressionStatement * st = (ExpressionStatement *) malloc(sizeof(ExpressionStatement));
    st->_n = BINARY;
    st->_e._binary.kind = k;
    st->_e._binary.lhs = lhs;
    st->_e._binary.rhs = rhs;

    return st;
}

ExpressionStatement * createUnExpression(UnExpressionKind k, ExpressionStatement * e){
    ExpressionStatement * st = (ExpressionStatement *) malloc(sizeof(ExpressionStatement));
    st->_n = UNARY;
    st->_e._unary.kind = k;
    st->_e._unary.e = e;

    return st;
}

ExpressionStatement * createLiteralExpression(Expression * e) {
    ExpressionStatement * st = (ExpressionStatement *) malloc(sizeof(ExpressionStatement));
    st->_n = LITERAL;
    st->_e._lit.e = e;

    return st;
}

ExpressionStatement * createVariableExpression(char * name){
  ExpressionStatement * st = (ExpressionStatement *) malloc(sizeof(ExpressionStatement));
  st->_n = VARIABLE;
  st->_e._var.name = strdup(name);

  return st;
}

ExpressionStatement * createArrayAccessorExpression(char * name, ExpressionStatement *accessor){
  ExpressionStatement * st = (ExpressionStatement *) malloc(sizeof(ExpressionStatement));
  st->_n = ACCESSOR;
  st->_e._acc.name = strdup(name);
  st->_e._acc.accessor = accessor;

  return st;
}

int const_int_eval(ExpressionStatement * e){
  if(e->_n == LITERAL){
    Expression * exp = evaluate(NULL, e);
    if(getType(exp) == INT){
      return exp->value._int;
    } else printf("Error. No se puede especificar el tamaño de un Array con %s", strType[getType(exp)]);
  } else {
    printf("Error. El tamaño de un array se debe especificar con un valor constante");
  }
  exit(-1);
}
