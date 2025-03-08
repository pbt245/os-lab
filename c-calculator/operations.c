#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

int calculate(char *expression, double *result) {
    double num1, num2;
    char op;

    if (sscanf(expression, "%lf %c %lf", &num1, &op, &num2) != 3) {
        return -1; // Syntax error
    }

    switch (op) {
        case '+': *result = num1 + num2; break;
        case '-': *result = num1 - num2; break;
        case '*': *result = num1 * num2; break;
        case '/': 
            if (num2 == 0) {
                printf("MATH ERROR\n");
                return -1;
            }
            *result = num1 / num2; 
            break;
        case '%': *result = (int)num1 % (int)num2; break;
        default: return -1;
    }

    return 0;
}

