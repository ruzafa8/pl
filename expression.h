#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "error.h"

typedef enum {
	FALSE, TRUE
}Bool;

typedef union{
	int _int;
	char _char;
	double _double;
	Bool _bool;
} Value;

typedef enum{
	INT, CHAR, DOUBLE, BOOL, UNKNOWN
} Type;

static const char * strType[] = {"Entero","Caracter","Decimal", "Proposicion"};

typedef struct {
	Type type;
	Value value;
} Expression;
Expression * create(Type type);
Expression * createInt(int value);
Expression * createDouble(double value);
Expression * createChar(char value);
Expression * createBool(Bool value);

EXIT_CODE getInt(Expression * expression, int* value);
EXIT_CODE getDouble(Expression * expression, double *value);
EXIT_CODE getChar(Expression * expression, char *value);
EXIT_CODE getBool(Expression * expression, Bool *value);

Type getType(Expression* e);
void printExpression(Expression *e);

#endif
