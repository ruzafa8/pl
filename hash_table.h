#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#include<string.h>
#include "expression.h"

static const unsigned int HASH_TABLE_SIZE = 101;

typedef struct Node{
    char * name;
    Expression* expression;
    int len;
    struct Node* next;
} Variable;
typedef Variable** Table;
/**
 * This function returns a hash table to manage variables
 */
Table createTable();

/**
 * returns if the Variable is defined and also its value, its type and its length if it's an array
 */
int valueOf(const Table table, const char * var, Expression** value);
int valueOfArray(const Table table, const char * var, Expression ** value, int size);

/**
 * A Set of adds Variableiables
 */
/*
 * Creates a variable without a type
 */
EXIT_CODE add(Table table, const char * var);
/*
 * Creates a variable with a default value:
 */
EXIT_CODE addDefaultInt(Table table, const char * var); // int i = 0;
EXIT_CODE addDefaultChar(Table table, const char * var); // char c = '\0';
EXIT_CODE addDefaultDouble(Table table, const char * var); // double d = 0.0;
EXIT_CODE addDefaultBool(Table table, const char * var); // boolean b = false;

EXIT_CODE addInt(Table table, const char * var, int value);
EXIT_CODE addChar(Table table, const char * var, char value);
EXIT_CODE addDouble(Table table, const char * var, double value);
EXIT_CODE addBool(Table table, const char * var, Bool bool);

EXIT_CODE addDefaultArrayInt(Table table, const char * var, int len); // array de 0's
EXIT_CODE addDefaultArrayChar(Table table, const char * var, int len); // array de '\0'
EXIT_CODE addDefaultArrayDouble(Table table, const char * var, int len); // array de 0.0
EXIT_CODE addDefaultArrayBool(Table table, const char * var, int len); //array de falses

EXIT_CODE addArrayInt(Table table, const char * var, int* value, int len);
EXIT_CODE addArrayChar(Table table, const char * var, char* value, int len);
EXIT_CODE addArrayDouble(Table table, const char * var, double* value, int len);
EXIT_CODE addArrayBool(Table table, const char * var, Bool* bool, int len);

int isArray(const Table table, const char * var);
int isIntArray(const Table table, const char * var);
int isCharArray(const Table table, const char * var);
int isBoolArray(const Table table, const char * var);
int isDoubleArray(const Table table, const char * var);

EXIT_CODE changeArrayInt(const Table table, const char * var, int newValue, int pos);
EXIT_CODE changeArrayChar(const Table table, const char * var, char newValue, int pos);
EXIT_CODE changeArrayDouble(const Table table, const char * var, double newValue, int pos);
EXIT_CODE changeArrayBool(const Table table, const char * var, Bool newValue, int pos);

/*
 * This function deletes a Variable if it's defined
 */
EXIT_CODE delete(Table table, char * var);
/*
 * Changes the value of a Variable if the type is the right and exists
 */
EXIT_CODE changeInt(const Table table, const char * var, int newValue);
EXIT_CODE changeChar(const Table table, const char * var, char newValue);
EXIT_CODE changeDouble(const Table table, const char * var, double newValue);
EXIT_CODE changeBool(const Table table, const char * var, Bool newValue);
/*
EXIT_CODE changeArrayInt(const Table table, const char * var, int newValue, int position);
EXIT_CODE changeArrayChar(const Table table, const char * var, char newValue, int position);
EXIT_CODE changeArrayDouble(const Table table, const char * var, double newValue, int position);
EXIT_CODE changeArrayBool(const Table table, const char * var, Bool newValue, int position);
*/

/* Prints the value of all variables included in the hash table */
void printTable(const Table table);
#endif // HASH_TABLE_H_INCLUDED
