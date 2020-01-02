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
	ExpressionStatement *e;
} Asig;

typedef struct {
	char *name;
	Type type;
	ExpressionStatement *e;
} Decl_Asig;

typedef struct {
	ExpressionStatement * e;
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
	int line;
} Statement;

Statement * createDecl(char * name, Type type, int line);
Statement * createAsig(char * name, ExpressionStatement * e, int line);
Statement * createDeclAsig(char *name, Type t, ExpressionStatement * e, int line);
Statement * createPrint(ExpressionStatement * e, int line);
Statement * createWhile(ExpressionStatement * condition, Statement * body, int line);
Statement * createRepeat(ExpressionStatement * numIteracions, Statement * body, int line);
Statement * createIf(ExpressionStatement * condition, Statement * body, int line);
Statement * createIfElse(ExpressionStatement * condition, Statement * then_st, Statement * else_st, int line);

Statement * join(Statement * s1, Statement * s2);

void exec(Table table, Statement * s);

#endif
