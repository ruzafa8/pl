#include "expression.h"

Expression * create(Type type){
	Expression * e;
	switch(type){
		case    INT: e = createInt(0); break;
		case DOUBLE: e = createDouble(0.0); break;
		case   CHAR: e = createChar('\0'); break;
		case   BOOL: e = createBool(FALSE); break;
		default    :
			e = (Expression *) malloc(sizeof(Expression));
			e->type = UNKNOWN;
	}
	return e;
}
Expression * createInt(int value){
	Expression* e = (Expression *) malloc(sizeof(Expression));
        e->type = INT;
        e->value._int = value;
        return e;
}
Expression * createDouble(double value){
	Expression* e = (Expression *) malloc(sizeof(Expression));
        e->type = DOUBLE;
        e->value._double = value;
        return e;
}
Expression * createChar(char value){
	Expression* e = (Expression *) malloc(sizeof(Expression));
        e->type = CHAR;
        e->value._char = value;
        return e;
}
Expression * createBool(Bool value){
	Expression *e = (Expression *) malloc(sizeof(Expression));
        e->type = BOOL;
        e->value._bool = value;
        return e;
}

EXIT_CODE getInt(Expression * expression, int* value){
	EXIT_CODE code = TYPE_ERROR;
	if(expression->type == INT){
		*value = expression->value._int;
		code = SUCCESS;
	}
	return code;
}
EXIT_CODE getDouble(Expression * expression, double *value){
	EXIT_CODE code = TYPE_ERROR;
	if(expression->type == DOUBLE){
		*value = expression->value._double;
		code = SUCCESS;
	}
	return code;
}
EXIT_CODE getChar(Expression * expression, char *value){
	EXIT_CODE code = TYPE_ERROR;
        if(expression->type == CHAR){
                *value = expression->value._char;
                code = SUCCESS;
        }
        return code;

}
EXIT_CODE getBool(Expression * expression, Bool *value){
	EXIT_CODE code = TYPE_ERROR;
        if(expression->type == BOOL){
                *value = expression->value._bool;
                code = SUCCESS;
        }
        return code;
}

Type getType(Expression* e){
	return e->type;
}

void printExpression(Expression *e){
        printf("[");
        int i;
        double d;
        char c;
        Bool b;
        switch(e->type){
                case INT:
                        getInt(e, &i);
                        printf("%d : Entero",i);
                        break;
                case DOUBLE:
                        getDouble(e,&d);
                        printf("%lf : Decimal",d);
                        break;
                case CHAR:
                        getChar(e,&c);
                        printf("%c : Caracter",c);
                        break;
                case BOOL:
                        getBool(e, &b);
                        printf("%s : Predicado",b == TRUE ?"Verdadero":"Falso");
                        break;
                default:
                        printf("Undefined");
        }
        printf("]\n");
}