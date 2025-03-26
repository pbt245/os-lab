#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "history.h"
#include "utils.h"

#define MAX_INPUT 50

int main() {
    char input[MAX_INPUT];
    double ans = 0.0;

    while (1) {
        printf(">> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "EXIT") == 0) {
            break;
        } else if (strcmp(input, "HIST") == 0) {
            print_history();
            continue;
        }

        replace_ans(input, ans);

        double result;
        int status = calculate(input, &result);
        if (status == SUCCESS) {
            ans = result;
            add_to_history(input, result);
            printf("%.2f\n", result);
        } else if (status == SYNTAX_ERROR){
            printf("SYNTAX ERROR\n");
        }
    }

    return 0;
}

