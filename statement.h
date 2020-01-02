#ifndef STATEMENT_H_INCLUDED
#define STATEMENT_H_INCLUDED

#include "hash_table.h"

typedef enum {
	DECL, ASIG, PRINT, WHILE, REPEAT, IF, IF_ELSE, COMPOSE
} StatementType;

typedef struct {
	char * name;
	Type t;
} Decl;

typedef struct {
	char * name;
	Expression *e;
} Asig;

typedef struct {
	Expression * e;
} Print;

typedef struct {
	Expression * e 
} While;

typedef struct {
} Repeat;

typedef struct {
	Expression * cond;
	Statement * 
} If;

typedef struct {
	Expression * cond;
	Statement * if_statement;
	Statement * else_statement;
} If_else;

typedef struct {
	Statement * s1;
	Statement * s2;
} Compose;

typedef union {
	Decl _decl;
	Asig _asig;
	Print _print;
	While _while;
	Repeat _repeat;
	If _if;
	If_else _if_else;
	Compose _compose;
} Statements;

typedef struct {
	Statements st;
	StatementType type;
}

Statement * createDecl();
Statement * createAsig();
Statement * createPrint();
Statement * createWhile();
Statement * createIf();
Statement * createIfElse();

Statement * join(Statement * s1, Statement * s2);

void exec(Table table, Statement * s);

#endif
