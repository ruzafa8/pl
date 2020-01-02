#pragma once

#include "statement.h"

typedef enum {
	BIN_PLUS, BIN_MINUS, BIN_BY, BIN_DIVIDE, BIN_OR, BIN_AND, BIN_XOR, 
	BIN_SI, BIN_SII, BIN_LESS, BIN_LESS_EQ, BIN_MORE, BIN_MORE_EQ, 
	BIN_NOT_EQ, BIN_DOBLE_EQUALS
} BinExpressionKind;

typedef enum {
	UN_MINUS
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
} NaryExpressionStatement;

typedef struct {
	NaryExpressionStatement _e;
	ExpressionNarity _n;
} ExpressionStatement;

typedef enum {
	UNARY, BINARY
} ExpressionNarity;

Expression evaluate(Table table, ExpressionStatement * e);
ExpressionStatement * createExpression(char * name, Type type);
