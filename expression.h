#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include "error.h"

typedef enum {
    INTEGER,
    CHARACTER,
    DOUBLE,
    BOOLEAN, ARRAY,
    UNKNOWN
} Type;

typedef struct{
    int size;
    Type type;
    Value * value;
}Array

typedef enum {
    FALSE, TRUE
} Boolean;

typedef union {
    int int_value;
    char char_value;
    double double_value;
    Boolean boolean_value;
    Array array_value;
} Value;

typedef struct {
    Type type;
    Value value;
} Expression;

Expression * createExpression();
Expression * createIntegerExpression(int value);
Expression * createArrayIntegerExpression(int * values, int len);
Expression * createCharacterExpression(char value);
Expression * createArrayCharacterExpression(char * values, int len);
Expression * createDoubleExpression(double value);
Expression * createArrayDoubleExpression(double * values, int len);
Expression * createBooleanExpression(Boolean value);
Expression * createArrayBooleanExpression(Boolean * values, int len);

EXIT_CODE changeIntegerExpression(Expression* e,int value);
EXIT_CODE changeArrayIntegerExpression(Expression* e,int value, int position);
EXIT_CODE changeCharacterExpression(Expression* e,char value);
EXIT_CODE changeArrayCharacterExpression(Expression* e,char value, int position);
EXIT_CODE changeDoubleExpression(Expression* e,double value);
EXIT_CODE changeArrayDoubleExpression(Expression* e,double value, int position);
EXIT_CODE changeBooleanExpression(Expression* e,Boolean value);
EXIT_CODE changeArrayBooleanExpression(Expression* e,Boolean value, int position);


#endif // EXPRESSION_H_INCLUDED
