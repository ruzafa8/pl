#pragma once

#include "expression.h"
#include "hash_table.h"
typedef enum {
	BIN_PLUS, BIN_MINUS, BIN_BY, BIN_DIVIDE, BIN_OR, BIN_AND, BIN_XOR,
	BIN_SI, BIN_SII, BIN_LESS, BIN_LESS_EQ, BIN_MORE, BIN_MORE_EQ,
	BIN_NOT_EQ, BIN_DOBLE_EQUALS
} BinExpressionKind;

typedef enum {
	UN_MINUS
} UnExpressionKind;

typedef enum {
	UNARY, BINARY, LITERAL, VARIABLE
} ExpressionNarity;

//Resolve circular definition
typedef struct _binexprstatement BinExpressionStatement;
typedef struct _unexprstatement UnExpressionStatement;
typedef union _naryexprstatement NaryExpressionStatement;
typedef struct _exprstatement ExpressionStatement;

typedef struct _binexprstatement{
	BinExpressionKind kind;
	ExpressionStatement * lhs;
	ExpressionStatement * rhs;
} BinExpressionStatement;

typedef struct _unexprstatement{
	UnExpressionKind kind;
	ExpressionStatement * e;
} UnExpressionStatement;

typedef struct _litexprstatement{
	Expression * e;
} LitExpressionStatement;

typedef struct {
	char * name;
} VarExpressionStatement;

typedef union _naryexprstatement{
	VarExpressionStatement _var;
	LitExpressionStatement _lit;
	BinExpressionStatement _binary;
	UnExpressionStatement _unary;
} NaryExpressionStatement;

typedef struct _exprstatement{
	NaryExpressionStatement _e;
	ExpressionNarity _n;
} ExpressionStatement;

Expression * evaluate(Table table, ExpressionStatement * e);
ExpressionStatement * createBinExpression(BinExpressionKind k, ExpressionStatement * lhs, ExpressionStatement * rhs);
ExpressionStatement * createUnExpression(UnExpressionKind k, ExpressionStatement * e);
ExpressionStatement * createLiteralExpression(Expression * e);
ExpressionStatement * createVariableExpression(char * name);
