#pragma once

#include "statement.h"

typedef enum {
	PLUS, MINUS, BY, DIVIDE, OR, AND, XOR, SI, SII, LESS, LESS_EQ, MORE, MORE_EQ, NOT_EQ, DOBLE_EQUALS
} BinExpressionKind;

typedef enum {
	MINUS
} UnExpressionKind;

typedef struct {
	BinExpressionKind kind;
	ExpressionStatement lhs;
	ExpressionStatement rhs;
} BinExpressionStatement;

typedef struct {
	UnExpressionKind kind;
	ExpressionStatement e;
} UnExpressionStatement;


typedef union {
	BinExpressionStatement _binary;
	UnExpressionStatement _unary;
} ExpressionStatement;

Expression exec_expression(Table table, Statement * s);
