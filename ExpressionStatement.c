#include "ExpressionStatement.h"

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
    if (rhsType == INT && g == INT) {
        return createInt(rhs->value._int * lhs->value._int);
    } else if (rhsType == DOUBLE && g == DOUBLE) {
        return createDouble(rhs->value._double * lhs->value._double);
    } else if (rhsType == INT && g == DOUBLE) {
        return createDouble(rhs->value._int * lhs->value._double);
    } else if (rhsType == DOUBLE && g == INT) {
        return createDouble(rhs->value._double * lhs->value._int);
    } else {
        readExitCodeType(TYPE_ERROR,rhsType,lhsType);
        exit(-1);
    }
}

Expression * _eval_div(Expression * rhs, Expression * lhs) {
    Type rhsType = getType(rhs);
    Type lhsType = getType(lhs);
    if (rhsType == INT && g == INT) {
        return createInt(rhs->value._int / lhs->value._int);
    } else if (rhsType == DOUBLE && g == DOUBLE) {
        return createDouble(rhs->value._double / lhs->value._double);
    } else if (rhsType == INT && g == DOUBLE) {
        return createDouble(rhs->value._int / lhs->value._double);
    } else if (rhsType == DOUBLE && g == INT) {
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

Expression * binary_evaluate(Table table, BinExpressionStatement * e){
    Expression * rhs = evaluate(table, e->rhs);
    Expression * lhs = evaluate(table, e->lhs);

    switch(e->kind){
        case(PLUS): return _eval_plus(rhs, lhs);
        case(MINUS): return _eval_minus(rhs, lhs);
        case(BY): return _eval_mult(rhs, lhs);
        case(DIVIDE): return _eval_div(rhs, lhs);
        case(OR): return _eval_or(rhs, lhs);
        case(AND): return _eval_and(rhs, lhs);
        case(XOR): return _eval_xor(rhs, lhs);
        case(SI): return _eval_si(rhs, lhs);
        case(SII): return _eval_sii(rhs, lhs);
        case(LESS): return _eval_less(rhs, lhs);
        case(LESS_EQ): return _eval_less_eq(rhs, lhs);
        case(MORE): return _eval_more(rhs, lhs);
        case(MORE_EQ): return _eval_more_eq(rhs, lhs);
        case(NOT_EQ): return _eval_not_eq(rhs, lhs);
        case(DOBLE_EQUALS): return _eval_double_eq(rhs, lhs);
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

Expression unary_evaluate(Table table, UnExpressionStatement * e) {
    Expression * e = evaluate(table, e->rhs);

    switch(e->kind){
        case(MINUS): return _un_eval_minus(e);
    }
}

Expression evaluate(Table table, ExpressionStatement * e){
    switch(e->_n){
        case UNARY:
            return unary_evaluate(table, e->_unary);
        case BINARY:
            return binary_evaluate(table, e->_binary);
        default:
            printf("Expresion n-arity evaluation error\n");
            exit(-1);
    }
}

