
#include "draw.h"
#include <stdio.h>
#include <math.h>
#include "eval.h"
#include "tokenize.h"
#include "yard.h"
#include "validation.h"
#include <stdlib.h>


#define M_PI 3.14159265358979323846

int is_valid(const char expr[]) {
    int valid = 1;
    if (validate_expression(expr) != SUCCESS) {
        printf("Invalid expression\n");
        valid = 0;
    }
    return valid;
}

int main_process(char expr[]) {
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
        samples[x] = evaluatePostfix(postfix, postfixCount, t);
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
    char expr[] = "x()";
    if (is_valid(expr)) {
        main_process(expr);
    }
    return 0;
}