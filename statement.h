#ifndef STATEMENT_H_INCLUDED
#define STATEMENT_H_INCLUDED

#include "hash_table.h"

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
	Expression * condition;
	struct _Statement * body;
} While;

typedef struct {
} Repeat;

typedef struct {
	Expression * cond;
	struct _Statement * body;
} If;

typedef struct {
	Expression * cond;
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
Statement * createAsig(char * name, Expression * e);
Statement * createDeclAsig(char *name, Type t, Expression * e);
Statement * createPrint(Expression * e);
Statement * createWhile(Expression * condition, Statement * body);
Statement * createIf();
Statement * createIfElse();

Statement * join(Statement * s1, Statement * s2);

void exec(Table table, Statement * s);

#endif
