#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int calculate(char *expression, double *result) {
    double num1, num2;
    char op;

    if (sscanf(expression, "%lf %c %lf", &num1, &op, &num2) != 3) {
        return SYNTAX_ERROR;
    }

    switch (op) {
        case '+': *result = num1 + num2; break;
        case '-': *result = num1 - num2; break;
        case '*': *result = num1 * num2; break;
        case '/': 
            if (num2 == 0) {
                printf("MATH ERROR\n");
                return MATH_ERROR;
            }
            *result = num1 / num2; 
            break;
        case '%':
            if ((int)num2 == 0) {
              printf("MATH ERROR\n");
              return MATH_ERROR;
            }
            *result = (int)num1 % (int)num2;
            break;
        default: return SYNTAX_ERROR;
    }

    return SUCCESS;
}

