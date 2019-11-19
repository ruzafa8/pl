#include <stdio.h>
#include <stdlib.h>
#include "expression.h"
int main() {
    Expression *e = createExpression();

    changeArrayDoubleExpression(e,2.4,5);
    int i;
    for(i = 0; i < 6; i++){
        printf("%lf",e->value.array_double_value[i]);
    }
    return 0;
}
