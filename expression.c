#include "expression.h"

Expression * createExpression(){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->type = UNKNOWN;
    return e;
}
Expression * createIntegerExpression(int value){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.int_value = value;
    e->type = INTEGER;
    e->len = 1;
    return e;
}
Expression * createArrayIntegerExpression(int * values, int len){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.array_int_value = (int *) malloc(sizeof(int) * len);
    int i;
    for(i = 0; i < len; i++){
        (e->value.array_int_value)[i] = values[i];
    }
    e->type = ARRAY_INTEGER;
    e->len = len;
    return e;
}
Expression * createCharacterExpression(char value){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.char_value = value;
    e->type = CHARACTER;
    e->len = 1;
    return e;
}
Expression * createArrayCharacterExpression(char * values, int len){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.array_char_value = (char *) malloc(sizeof(char) * len);
    int i;
    for(i = 0; i < len; i++){
        (e->value.array_char_value)[i] = values[i];
    }
    e->type = ARRAY_CHARACTER;
    e->len = len;
    return e;
}
Expression * createDoubleExpression(double value){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.double_value = value;
    e->type = DOUBLE;
    e->len = 1;
    return e;
}
Expression * createArrayDoubleExpression(double * values, int len){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.array_double_value = (double *) malloc(sizeof(double) * len);
    int i;
    for(i = 0; i < len; i++){
            (e->value.array_double_value)[i] = values[i];
    }
    e->type = ARRAY_DOUBLE;
    e->len = len;
    return e;
}
Expression * createBooleanExpression(Boolean value){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.boolean_value = value;
    e->type = BOOLEAN;
    e->len = 1;
    return e;
}
Expression * createArrayBooleanExpression(Boolean * values, int len){
    Expression* e = (Expression *) malloc(sizeof(Expression));
    e->value.array_boolean_value = (Boolean *) malloc(sizeof(Boolean) * len);
    int i;
    for(i = 0; i < len; i++){
        e->value.array_boolean_value[i] = values[i];
    }
    e->type = ARRAY_BOOLEAN;
    e->len = len;
    return e;
}

EXIT_CODE changeIntegerExpression(Expression* e,int value){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = INTEGER;
    }

    if(e->type != INTEGER){
        code = TYPE_ERROR;
    } else {
        e->value.int_value = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeArrayIntegerExpression(Expression* e,int value, int position){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = ARRAY_INTEGER;
        e->len = position+1;
        e->value.array_int_value = (int *) malloc(sizeof(int) * e->len);
        int i;
        for(i = 0; i < position; i++){
            e->value.array_int_value[i] = 0;
        }
    }

    if(e->type != ARRAY_INTEGER){
        code = TYPE_ERROR;
    } else if(0 > position || position >= e->len) {
        code = OUT_OF_BOUNDS_ERROR;
    }else{
        e->value.array_int_value[position] = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeCharacterExpression(Expression* e,char value){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = CHARACTER;
    }

    if(e->type != CHARACTER){
        code = TYPE_ERROR;
    } else {
        e->value.char_value = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeArrayCharacterExpression(Expression* e,char value, int position){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = ARRAY_CHARACTER;
        e->len = position+1;
        e->value.array_char_value = (char *) malloc(sizeof(char) * e->len);
        int i;
        for(i = 0; i < position; i++){
            e->value.array_char_value[i] = '\0';
        }
    }

    if(e->type != ARRAY_CHARACTER){
        code = TYPE_ERROR;
    } else if(0 > position || position >= e->len) {
        code = OUT_OF_BOUNDS_ERROR;
    }else{
        e->value.array_char_value[position] = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeDoubleExpression(Expression* e,double value){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = DOUBLE;
    }

    if(e->type != DOUBLE){
        code = TYPE_ERROR;
    } else {
        e->value.double_value = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeArrayDoubleExpression(Expression* e,double value, int position){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = ARRAY_DOUBLE;
        e->len = position+1;
        e->value.array_double_value = (double *) malloc(sizeof(double) * e->len);
        int i;
        for(i = 0; i < position; i++){
            e->value.array_double_value[i] = 0.0;
        }
    }

    if(e->type != ARRAY_DOUBLE){
        code = TYPE_ERROR;
    } else if(0 > position || position >= e->len) {
        code = OUT_OF_BOUNDS_ERROR;
    }else{
        e->value.array_double_value[position] = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeBooleanExpression(Expression* e,Boolean value){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = BOOLEAN;
    }

    if(e->type != BOOLEAN){
        code = TYPE_ERROR;
    } else {
        e->value.boolean_value = value;
        code = SUCCESS;
    }
    return code;
}
EXIT_CODE changeArrayBooleanExpression(Expression* e,Boolean value, int position){
    EXIT_CODE code;
    if(e->type == UNKNOWN){
        e->type = ARRAY_BOOLEAN;
        e->len = position+1;
        e->value.array_boolean_value = (Boolean *) malloc(sizeof(Boolean) * e->len);
        int i;
        for(i = 0; i < position; i++){
            e->value.array_boolean_value[i] = FALSE;
        }
    }

    if(e->type != ARRAY_BOOLEAN){
        code = TYPE_ERROR;
    } else if(0 > position || position >= e->len) {
        code = OUT_OF_BOUNDS_ERROR;
    }else{
        e->value.array_boolean_value[position] = value;
        code = SUCCESS;
    }
    return code;
}
