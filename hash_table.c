
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
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
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
      if(getType(v->expression) == INT){
        v->expression = createInt(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_ERROR;
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
      if(getType(v->expression) == CHAR){
        v->expression = createChar(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_ERROR;
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
      if(getType(v->expression) == DOUBLE){
        v->expression = createDouble(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_ERROR;
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
      if(getType(v->expression) == BOOL){
        v->expression = createBool(newValue);
        code = SUCCESS;
      } else {
        code = TYPE_ERROR;
      }
      found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
