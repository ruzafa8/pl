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

Expression * _eval_plus(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if (rhsType == INT && lhsType == INT) {
        return createInt(rhs->value._int + lhs->value._int);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE) {
        return createDouble(rhs->value._double + lhs->value._double);
    } else if (rhsType == INT && lhsType == DOUBLE) {
        return createDouble(rhs->value._int + lhs->value._double);
    } else if (rhsType == DOUBLE && lhsType == INT) {
        return createDouble(rhs->value._double + lhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_minus(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if (rhsType == INT && lhsType == INT) {
        return createInt(rhs->value._int - lhs->value._int);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE) {
        return createDouble(rhs->value._double - lhs->value._double);
    } else if (rhsType == INT && lhsType == DOUBLE) {
        return createDouble(rhs->value._int - lhs->value._double);
    } else if (rhsType == DOUBLE && lhsType == INT) {
        return createDouble(rhs->value._double - lhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_mult(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);
    if (rhsType == INT && lhsType == INT) {
        return createInt(rhs->value._int * lhs->value._int);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE) {
        return createDouble(rhs->value._double * lhs->value._double);
    } else if (rhsType == INT && lhsType == DOUBLE) {
        return createDouble(rhs->value._int * lhs->value._double);
    } else if (rhsType == DOUBLE && lhsType == INT) {
        return createDouble(rhs->value._double * lhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_div(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);
    if (rhsType == INT && lhsType == INT) {
        return createInt(rhs->value._int / lhs->value._int);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE) {
        return createDouble(rhs->value._double / lhs->value._double);
    } else if (rhsType == INT && lhsType == DOUBLE) {
        return createDouble(rhs->value._int / lhs->value._double);
    } else if (rhsType == DOUBLE && lhsType == INT) {
        return createDouble(rhs->value._double / lhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_or(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == BOOL && lhsType == BOOL){
        return createBool(or(rhs->value._bool,lhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_and(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == BOOL && lhsType == BOOL){
        return createBool(and(rhs->value._bool,lhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_xor(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == BOOL && lhsType == BOOL){
        return createBool(xor(rhs->value._bool,lhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_si(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == BOOL && lhsType == BOOL){
        return createBool(si(rhs->value._bool,lhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_sii(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == BOOL && lhsType == BOOL){
        return createBool(sii(rhs->value._bool,lhs->value._bool));
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_less(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int < lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double < lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int < lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double < lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char < lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * _eval_less_eq(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int <= lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double <= lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int <= lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double <= lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char <= lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * _eval_more(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int > lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double > lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int > lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double > lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char > lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * _eval_more_eq(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int >= lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double >= lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int >= lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double >= lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char >= lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * _eval_not_eq(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int != lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double != lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int != lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double != lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char != lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * _eval_double_eq(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);

    if(rhsType == INT && lhsType == INT){
        return createBool(rhs->value._int == lhs->value._int ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == DOUBLE){
        return createBool(rhs->value._double == lhs->value._double ? TRUE : FALSE);
    } else if(rhsType == INT && lhsType == DOUBLE) {
        return createBool(rhs->value._int == lhs->value._double ? TRUE : FALSE);
    } else if (rhsType == DOUBLE && lhsType == INT){
        return createBool(rhs->value._double == lhs->value._int ? TRUE : FALSE);
    } else if(rhsType == CHAR && lhsType == CHAR){
        return createBool(rhs->value._char == lhs->value._char ? TRUE : FALSE);
    } else {
        readExitCodeType(TYPE_ERROR, rhsType, lhsType);
        exit(-1);
    }
}

Expression * binary_evaluate(Table table, BinExpressionStatement e){
    Expression * rhs = evaluate(table, e.rhs);
    Expression * lhs = evaluate(table, e.lhs);

    switch(e.kind){
        case(BIN_PLUS): return _eval_plus(rhs, lhs);
        case(BIN_MINUS): return _eval_minus(rhs, lhs);
        case(BIN_BY): return _eval_mult(rhs, lhs);
        case(BIN_DIVIDE): return _eval_div(rhs, lhs);
        case(BIN_OR): return _eval_or(rhs, lhs);
        case(BIN_AND): return _eval_and(rhs, lhs);
        case(BIN_XOR): return _eval_xor(rhs, lhs);
        case(BIN_SI): return _eval_si(rhs, lhs);
        case(BIN_SII): return _eval_sii(rhs, lhs);
        case(BIN_LESS): return _eval_less(rhs, lhs);
        case(BIN_LESS_EQ): return _eval_less_eq(rhs, lhs);
        case(BIN_MORE): return _eval_more(rhs, lhs);
        case(BIN_MORE_EQ): return _eval_more_eq(rhs, lhs);
        case(BIN_NOT_EQ): return _eval_not_eq(rhs, lhs);
        case(BIN_DOBLE_EQUALS): return _eval_double_eq(rhs, lhs);
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
          if(e == NULL){
            readExitCodeVariables(VAR_NOT_FOUND_ERROR,e->_e._var.name,UNKNOWN,UNKNOWN);
            exit(-1);
          }
          return res;
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
