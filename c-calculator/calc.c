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

    printf("Advanced Calculator (Type 'EXIT' to quit)\n");

    while (1) {
        printf(">> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character

        if (strcmp(input, "EXIT") == 0) {
            break;
        } else if (strcmp(input, "HIST") == 0) {
            print_history();
            continue;
        }

        replace_ans(input, ans); // Replace "ANS" with the last answer

        double result;
        if (calculate(input, &result) == 0) {
            ans = result;
            add_to_history(input, result);
            printf("%.2f\n", result);
        } else {
            printf("SYNTAX ERROR\n");
        }
    }

    return 0;
}

