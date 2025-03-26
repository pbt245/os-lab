#include <stdio.h>
#include <string.h>
#include "history.h"

#define MAX_HISTORY 5
static char history[MAX_HISTORY][50];
static double results[MAX_HISTORY];
static int hist_count = 0;

void add_to_history(char *expression, double result) {
    if (hist_count < MAX_HISTORY) {
        hist_count++;
    }

    for (int i = MAX_HISTORY - 1; i > 0; i--) {
        strcpy(history[i], history[i - 1]);
        results[i] = results[i - 1];
    }

    strcpy(history[0], expression);
    results[0] = result;
}

void print_history() {
    for (int i = 0; i < hist_count; i++) {
        printf("%s = %.2f\n", history[i], results[i]);
    }
}

