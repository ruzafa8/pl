#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "error.h"

typedef enum {
    FALSE, TRUE
} Boolean;

typedef enum {
    INTEGER,
    CHARACTER,
    DOUBLE,
    BOOLEAN,
    ARRAY,
    UNKNOWN
} Typename;

typedef struct S_Type {
    Typename name;
    struct S_Type* next;
}Type;

typedef struct{
    int size;
    Value * value;
}Array

typedef union {
    int int_value;
    char char_value;
    double double_value;
    Boolean boolean_value;
    Array* array_value;
} Value;

typedef struct {
    Type* type;
    Value val;
} Expression;

Expression * createExpression();
Expression * createIntegerExpression(int value);
Expression * createCharacterExpression(char value);
Expression * createDoubleExpression(double value);
Expression * createBooleanExpression(Boolean value);
Expression * arrayConstructor(Expression* e, int len);


#endif // EXPRESSION_H_INCLUDED
