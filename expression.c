#include "expression.h"

Expression * createBasicExpression(Typename type){
    if(type == ARRAY) return NULL;
    Expression* e = (Expression*) malloc(sizeof(Expression));
    *(e->type) = (Type*) malloc(sizeof(Type));
    e->type->name = type;
    e->type->next = NULL;
    return e;
}

Value * createValue(){
    return (Value*) malloc(sizeof(Value));
}
Expression * createArray(int len, Expression * e){
    Expression * res = (Expression*) malloc(sizeof(Expression));
    Type* t = (Type*) malloc(sizeof(Type));
    t->name = ARRAY;
    t->next = e->type;
    res->type->name = t;
    return res;
}

void setIntegerValue(Expression * e,int value){
    if(e->type == INTEGER){
        e->val.int_value = value;
    }
}
void setDoubleValue(Expression * e, double value){
    if(e->type == INTEGER){
        e->val.double_value = value;
    }
}
void setBooleanValue(Expression * e, Boolean value){
    if(e->type == INTEGER){
        e->val.boolean_value = value;
    }
}
void setCharacterValue(Expression * e, char value){
    if(e->type == INTEGER){
        e->val.char_value = value;
    }
}
Expression * get(int pos, Expression * e){
    if(e->type == ARRAY){
        e->value
    }
}
