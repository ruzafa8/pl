
#include "hash_table.h"

Table createTable(){
    return (Variable**) calloc(HASH_TABLE_SIZE, sizeof(Variable*));
}



int hash(const char * var){
    int h = 0;
    int i = 0;
    while(var[i] != '\0'){
        h += (int) var[i++];
    }
    return h % HASH_TABLE_SIZE;
}

int valueOf(const Table table, const char * var, Expression* value){
    Variable * v = *(table + hash(var));
	int found = 0;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			found = 1;
			*value = *v->expression;
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
		new->expression = createExpression();
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
EXIT_CODE addDefaultBoolean(Table table, const char * var){
    return addBoolean(table,var,FALSE);
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
		new->expression = createIntegerExpression(value);
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
		new->expression = createCharacterExpression(value);
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
		new->expression = createDoubleExpression(value);
		new->next = *(table+h);
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addBoolean(Table table, const char * var, Boolean value){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createBooleanExpression(value);
		new->next = *(table+h);
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}

EXIT_CODE addDefaultArrayInt(Table table, const char * var, int len){
    int res[len];
    int i;
    for(i = 0; i < len; i++){
        res[i] = 0;
    }
    return addArrayInt(table,var,res,len);
}
EXIT_CODE addDefaultArrayChar(Table table, const char * var, int len){
    char res[len];
    int i;
    for(i = 0; i < len; i++){
        res[i] = '\0';
    }
    return addArrayChar(table,var,res,len);
}
EXIT_CODE addDefaultArrayDouble(Table table, const char * var, int len){
    double res[len];
    int i;
    for(i = 0; i < len; i++){
        res[i] = 0.0;
    }
    return addArrayDouble(table,var,res,len);
}
EXIT_CODE addDefaultArrayBoolean(Table table, const char * var, int len){
    Boolean res[len];
    int i;
    for(i = 0; i < len; i++){
        res[i] = FALSE;
    }
    return addArrayBoolean(table,var,res,len);
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
		new->expression = createArrayIntegerExpression(value,len);
		new->next = *(table+h);
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
		new->expression = createArrayCharacterExpression(value,len);
		new->next = *(table+h);
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
		new->expression = createArrayDoubleExpression(value,len);
		new->next = *(table+h);
		table[h] = new;
	}
	return aux == NULL? SUCCESS : VAR_ALREADY_EXISTS_ERROR;
}
EXIT_CODE addArrayBoolean(Table table, const char * var, Boolean* value, int len){
    int h = hash(var);
	Variable * aux = *(table+h);

	while(aux != NULL && strcmp(var,aux->name) != 0){
		aux = aux->next;
	}

	if(aux == NULL){
		Variable * new = (Variable*) malloc(sizeof(Variable));
		new->name = strdup(var);
		new->expression = createArrayBooleanExpression(value,len);
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
	return found ? SUCCESS : VAR_NOT_FOUND_ERROR;
}

EXIT_CODE changeInt(const Table table, const char * var, int newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeIntegerExpression(v->expression,newValue);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeChar(const Table table, const char * var, char newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeCharacterExpression(v->expression,newValue);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeDouble(const Table table, const char * var, double newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeDoubleExpression(v->expression,newValue);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeBoolean(const Table table, const char * var, Boolean newValue){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeBooleanExpression(v->expression,newValue);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}

EXIT_CODE changeArrayInt(const Table table, const char * var, int newValue, int position){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeArrayIntegerExpression(v->expression,newValue,position);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayChar(const Table table, const char * var, char newValue, int position){
    return -1;Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeArrayCharacterExpression(v->expression,newValue,position);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayDouble(const Table table, const char * var, double newValue, int position){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeArrayDoubleExpression(v->expression,newValue,position);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
EXIT_CODE changeArrayBoolean(const Table table, const char * var, Boolean newValue, int position){
    Variable * v = *(table + hash(var));
	int found = 0, code;

	while(v != NULL && !found){
		if(strcmp(var,v->name) == 0){
			code = changeArrayBooleanExpression(v->expression,newValue,position);
			found = 1;
		}
		v = v->next;
	}
	return found ? VAR_NOT_FOUND_ERROR : code;
}
