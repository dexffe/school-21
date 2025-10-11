#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "evaluator.h"
#include <math.h>

int is_valid_expression(const char* expr) {
    int brackets = 0;
    for (int i = 0; expr[i]; i++) {
        if (expr[i] == '(') brackets++;
        if (expr[i] == ')') brackets--;
        if (brackets < 0) return 0;
    }
    return brackets == 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    const char* expr = argv[1];
    if (!is_valid_expression(expr)) {
        printf("n/a\n");
        return 0;
    }

    Token* postfix = NULL;
    int count;
    if (!tokenize_and_convert(expr, &postfix, &count)) {
        printf("n/a\n");
        free(postfix);
        return 0;
    }

    printf("Graph of function:\n");
    for (double x = -10; x <= 10; x += 0.5) {
        double y = evaluate_postfix(postfix, count, x);
        if (isnan(y)) {
            printf("n/a\n");
            free(postfix);
            return 0;
        }

        int pos = (int)(y * 2 + 20);
        if (pos >= 0 && pos < 40) {
            for (int i = 0; i < 40; i++) {
                if (i == pos) printf("*");
                else printf(" ");
            }
            printf("\n");
        }
    }

    free(postfix);
    return 0;
}
