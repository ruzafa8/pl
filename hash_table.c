#include "hash_table.h"

Table createTable(){
    return (Variable**) calloc(HASH_TABLE_SIZE, sizeof(Variable*));
}

int hash(const char * var){// ALgoritmo de Horner.
    int prime = 31;
    int hash = 0;
    int i = 0;
    while(var[i] != '\0')
        hash = (prime * hash + (int) var[i++]) % HASH_TABLE_SIZE;
    return hash;
}

int valueOf(const Table table, const char * var, Expression** value){

  Variable * v = *(table + hash(var));
	int found = 0;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			found = 1;
			*value = v->expression;
		}
		v = v->next;
	}
	return found ? SUCCESS : VAR_NOT_FOUND_ERROR;
}

void printTable(const Table table) {
    for(int i=0; i<HASH_TABLE_SIZE; i++){
	Variable * v = *(table +i);
	while(v != NULL){
	    printf("%s -> ",v->name);
	    printExpression(v->expression);
	    v = v->next;
	}
    }
}

EXIT_CODE add(Table table, const char * var){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = create(UNKNOWN);
    new->next = *(table + h);
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}

EXIT_CODE addDefaultInt(Table table, const char * var){
    return addInt(table,var,0);
}
EXIT_CODE addDefaultChar(Table table, const char * var){
    return addChar(table,var,'\0');
}
EXIT_CODE addDefaultDouble(Table table, const char * var){
    return addDouble(table,var,0.0);
}
EXIT_CODE addDefaultBool(Table table, const char * var){
    return addBool(table,var,FALSE);
}

EXIT_CODE addInt(Table table, const char * var, int value){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createInt(value);
		new->next = *(table+h);
    new->len = 0;
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addChar(Table table, const char * var, char value){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createChar(value);
		new->next = *(table+h);
    new->len = 0;
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addDouble(Table table, const char * var, double value){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createDouble(value);
		new->next = *(table+h);
    new->len = 0;
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addBool(Table table, const char * var, Bool value){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createBool(value);
		new->next = *(table+h);
    new->len = 0;
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}

EXIT_CODE addDefaultArrayInt(Table table, const char * var, int len){ // array de 0's
  int value[len];
  for(int i = 0; i < len; i++) value[i] = 0;
  return addArrayInt(table,var,value,len);
}
EXIT_CODE addDefaultArrayChar(Table table, const char * var, int len){ // array de '\0'
  char value[len];
  for(int i = 0; i < len; i++) value[i] = '\0';
  return addArrayChar(table,var,value,len);
}

EXIT_CODE addDefaultArrayDouble(Table table, const char * var, int len){ // array de 0.0
  double value[len];
  for(int i = 0; i < len; i++) value[i] = 0.0;
  return addArrayDouble(table,var,value,len);
}
EXIT_CODE addDefaultArrayBool(Table table, const char * var, int len){ //array de falses
  Bool value[len];
  for(int i = 0; i < len; i++)value[i] = FALSE;
  return addArrayBool(table,var,value,len);
}

EXIT_CODE addArrayInt(Table table, const char * var, int* value, int len){
  int h = hash(var);
  Variable * aux = *(table+h);

  while(aux != NULL && strcmp(var,aux->name) != 0){
    aux = aux->next;
  }

  if(aux == NULL){
    Variable * new = (Variable*) malloc(sizeof(Variable));
    new->name = strdup(var);
    new->expression = (Expression *) malloc(sizeof(Expression) * len);
    for(int i = 0; i < len; i++) *((new->expression) + i) = *createInt(value[i]);
    new->next = *(table+h);
    new->len = len;
    table[h] = new;
  }
  return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addArrayChar(Table table, const char * var, char* value, int len){
  int h = hash(var);
  Variable * aux = *(table+h);

  while(aux != NULL && strcmp(var,aux->name) != 0){
    aux = aux->next;
  }

  if(aux == NULL){
    Variable * new = (Variable*) malloc(sizeof(Variable));
    new->name = strdup(var);
    new->expression = (Expression *) malloc(sizeof(Expression) * len);
    for(int i = 0; i < len; i++) *((new->expression) + i) = *createChar(value[i]);
    new->next = *(table+h);
    new->len = len;
    table[h] = new;
  }
  return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addArrayDouble(Table table, const char * var, double* value, int len){
  int h = hash(var);
  Variable * aux = *(table+h);

  while(aux != NULL && strcmp(var,aux->name) != 0){
    aux = aux->next;
  }

  if(aux == NULL){
    Variable * new = (Variable*) malloc(sizeof(Variable));
    new->name = strdup(var);
    new->expression = (Expression *) malloc(sizeof(Expression) * len);
    for(int i = 0; i < len; i++) *((new->expression) + i) = *createDouble(value[i]);
    new->next = *(table+h);
    new->len = len;
    table[h] = new;
  }
  return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addArrayBool(Table table, const char * var, Bool* value, int len){
  int h = hash(var);
  Variable * aux = *(table+h);

  while(aux != NULL && strcmp(var,aux->name) != 0){
    aux = aux->next;
  }

  if(aux == NULL){
    Variable * new = (Variable*) malloc(sizeof(Variable));
    new->name = strdup(var);
    new->expression = (Expression *) malloc(sizeof(Expression) * len);
    for(int i = 0; i < len; i++) *((new->expression) + i) = *createBool(value[i]);
    new->next = *(table+h);
    new->len = len;
    table[h] = new;
  }
  return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}

int valueOfArray(const Table table, const char * var, Expression ** value, int *size){
  Variable * v = *(table + hash(var));
	int found = 0;
  EXIT_CODE code = VAR_NOT_FOUND_ERROR;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			found = 1;
      if (v->len > 0){
			   *value = v->expression;
         code = SUCCESS;
      } else {
        code = IS_NOT_AN_ARRAY;
      }
		}
		v = v->next;
	}
	return code;
}

int isIntArray(const Table table, const char * var){
  Expression * e;
  int len;
  EXIT_CODE code = valueOfArray(table,var,&e,&len);
  return code == SUCCESS && getType(e) == INT;
}
int isCharArray(const Table table, const char * var){
  Expression * e;
  int len;
  EXIT_CODE code = valueOfArray(table,var,&e,&len);
  return code == SUCCESS && getType(e) == CHAR;
}
int isBoolArray(const Table table, const char * var){
  Expression * e;
  int len;
  EXIT_CODE code = valueOfArray(table,var,&e,&len);
  return code == SUCCESS && getType(e) == BOOL;
}
int isDoubleArray(const Table table, const char * var){
  Expression * e;
  int len;
  EXIT_CODE code = valueOfArray(table,var,&e,&len);
  return code == SUCCESS && getType(e) == DOUBLE;
}

EXIT_CODE changeArrayInt(const Table table, const char * var, int newValue, int pos){
  Variable * v = *(table + hash(var));
  int found = 0, code;

  while(v != NULL && !found){
    if(strcmp(var,v->name) == 0){
      if(getType(v->expression) == INT){
        if(v->len == 0){
          code = IS_NOT_AN_ARRAY;
        } else if(0 <= pos && pos < v->len){
          *(v->expression + pos) = *createInt(newValue);
          code = SUCCESS;
        } else {
          code = OUT_OF_BOUNDS_ERROR;
        }
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
    }
    v = v->next;
  }
  return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayChar(const Table table, const char * var, char newValue, int pos){
  Variable * v = *(table + hash(var));
  int found = 0, code;

  while(v != NULL && !found){
    if(strcmp(var,v->name) == 0){
      if(getType(v->expression) == INT){
        if(v->len == 0){
          code = IS_NOT_AN_ARRAY;
        } else if(0 <= pos && pos < v->len){
          *(v->expression + pos) = *createChar(newValue);
          code = SUCCESS;
        } else {
          code = OUT_OF_BOUNDS_ERROR;
        }
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
    }
    v = v->next;
  }
  return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayDouble(const Table table, const char * var, double newValue, int pos){
  Variable * v = *(table + hash(var));
  int found = 0, code;

  while(v != NULL && !found){
    if(strcmp(var,v->name) == 0){
      if(getType(v->expression) == INT){
        if(v->len == 0){
          code = IS_NOT_AN_ARRAY;
        } else if(0 <= pos && pos < v->len){
          *(v->expression + pos) = *createDouble(newValue);
          code = SUCCESS;
        } else {
          code = OUT_OF_BOUNDS_ERROR;
        }
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
    }
    v = v->next;
  }
  return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayBool(const Table table, const char * var, Bool newValue, int pos){
  Variable * v = *(table + hash(var));
  int found = 0, code;

  while(v != NULL && !found){
    if(strcmp(var,v->name) == 0){
      if(getType(v->expression) == INT){
        if(v->len == 0){
          code = IS_NOT_AN_ARRAY;
        } else if(0 <= pos && pos < v->len){
          *(v->expression + pos) = *createBool(newValue);
          code = SUCCESS;
        } else {
          code = OUT_OF_BOUNDS_ERROR;
        }
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
    }
    v = v->next;
  }
  return ! found ? VAR_NOT_FOUND_ERROR : code;
}


EXIT_CODE delete(Table table, char * var){
    int h = hash(var);
	Variable * v = *(table + h);
	Variable * anterior = NULL;
	int found = 0;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			if(anterior == NULL){
				*(table + h) = v->next;
			} else {
				anterior->next = v->next;
			}
			free(v->name);
			free(v->expression);
			free(v);
			found = 1;
		}
		anterior = v;
		v = v->next;
	}
	return ! found ? SUCCESS : VAR_NOT_FOUND_ERROR;
}

EXIT_CODE changeInt(const Table table, const char * var, int newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
      Type t = getType(v->expression);
      if(t == INT || t == UNKNOWN){
        v->expression = createInt(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
		}
		v = v->next;
	}
	return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeChar(const Table table, const char * var, char newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
      Type t = getType(v->expression);
      if(t == CHAR || t == UNKNOWN){
        v->expression = createChar(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
		}
		v = v->next;
	}
	return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeDouble(const Table table, const char * var, double newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
      Type t = getType(v->expression);
      if(t == DOUBLE || t == UNKNOWN){
        v->expression = createDouble(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
		}
		v = v->next;
	}
	return ! found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeBool(const Table table, const char * var, Bool newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
      Type t = getType(v->expression);
      if(t == BOOL || t == UNKNOWN){
        v->expression = createBool(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_DOESNT_AGREE;
      }
      found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
