#ifndef STATEMENT_H_INCLUDED
#define STATEMENT_H_INCLUDED

#include "hash_table.h"
#include "ExpressionStatement.h"

typedef enum  {
	DECL, ASIG, DECL_ASIG, PRINT, WHILE, REPEAT, IF, IF_ELSE, COMPOSE
} StatementType;


typedef struct {
	char * name;
	Type type;
} Decl;

typedef struct {
	char * name;
	Expression *e;
} Asig;

typedef struct {
	char *name;
	Type type;
	Expression *e;
} Decl_Asig;

typedef struct {
	Expression * e;
} Print;

typedef struct {
	ExpressionStatement * condition;
	struct _Statement * body;
} While;

typedef struct {
	ExpressionStatement * numIteracions;
	struct _Statement * body;
} Repeat;

typedef struct {
	ExpressionStatement * cond;
	struct _Statement * body;
} If;

typedef struct {
	ExpressionStatement * cond;
	struct _Statement * if_statement;
	struct _Statement * else_statement;
} If_else;

typedef struct {
	struct _Statement * s1;
	struct _Statement * s2;
} Compose;

typedef union {
	Decl _decl;
	Asig _asig;
	Decl_Asig _decl_asig;
	Print _print;
	While _while;
	Repeat _repeat;
	If _if;
	If_else _if_else;
	Compose _compose;
} Statements;

typedef struct _Statement {
	Statements st;
	StatementType type;
} Statement;

Statement * createDecl(char * name, Type type);
Statement * createAsig(char * name, ExpressionStatement * e);
Statement * createDeclAsig(char *name, Type t, ExpressionStatement * e);
Statement * createPrint(ExpressionStatement * e);
Statement * createWhile(ExpressionStatement * condition, Statement * body);
Statement * createRepeat(ExpressionStatement * numIteracions, Statement * body);
Statement * createIf(ExpressionStatement * condition, Statement * body);
Statement * createIfElse(ExpressionStatement * condition, Statement * then_st, Statement * else_st);

Statement * join(Statement * s1, Statement * s2);

void exec(Table table, Statement * s);

#endif
