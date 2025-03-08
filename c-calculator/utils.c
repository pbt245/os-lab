#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

void replace_ans(char *expression, double ans) {
    char *pos = strstr(expression, "ANS");
    if (pos != NULL) {
        char temp[50];
        snprintf(temp, sizeof(temp), "%.2f", ans);
        strncpy(pos, temp, strlen(temp));
    }
}

