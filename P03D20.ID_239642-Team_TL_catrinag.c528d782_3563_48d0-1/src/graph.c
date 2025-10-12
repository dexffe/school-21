#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "eval.h"
#include "inp.h"
#include "tokenize.h"
#include "validation.h"
#include "yard.h"

#define M_PI 3.14159265358979323846

int is_valid(const char expr[]) {
    int valid = 1;
    if (validate_expression(expr) != SUCCESS) {
        printf("n/a;");
        valid = 0;
    }
    return valid;
}

int main_process(const char expr[]) {
    char buf[DRAW_HEIGHT][DRAW_WIDTH];
    double samples[DRAW_WIDTH];

    Token* tokens = NULL;
    int tokenCount = 0;
    tokenize(expr, &tokens, &tokenCount);

    Token* postfix = malloc(tokenCount * sizeof(Token));
    int postfixCount = 0;
    infixToPostfix(tokens, tokenCount, &postfix, &postfixCount);

    for (int x = 0; x < DRAW_WIDTH; x++) {
        double t = (4.0 * M_PI) * x / (DRAW_WIDTH - 1);
        double y = evaluatePostfix(postfix, postfixCount, t);
        if (y > 1.0) y = 1.0;
        if (y < -1.0) y = -1.0;
        samples[x] = y;
    }

    draw_init_buffer(buf);
    draw_plot_samples(samples, buf);
    draw_print_buffer(buf);

    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == FUNCTION) {
            free(tokens[i].function);
        }
    }
    free(tokens);
    free(postfix);

    return 0;
}

int main() {
    char* expr = input_string();
    if (is_valid(expr)) {
        main_process(expr);
    }
    free(expr);
    return 0;
}