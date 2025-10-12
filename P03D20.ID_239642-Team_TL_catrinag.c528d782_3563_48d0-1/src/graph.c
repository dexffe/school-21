#include "draw.h"
#include <stdio.h>
#include <math.h>
#include "eval.h"
#include "tokenize.h"
#include "yard.h"
#include "validation.h"
#include <stdlib.h>

int is_valid(const char expr[]) {
    int valid = 1;
    if (validate_expression(expr) != SUCCESS) {
        printf("Invalid expression\n");
        valid = 0;
    }
    return valid;
}

int main_process(const char* expr) {
    char buf[DRAW_HEIGHT][DRAW_WIDTH];
    
    Token* tokens = NULL;
    int tokenCount = 0;
    tokenize((char*)expr, &tokens, &tokenCount);

    Token* postfix = malloc(tokenCount * sizeof(Token));
    int postfixCount = 0;
    infixToPostfix(tokens, tokenCount, &postfix, &postfixCount);
    
    draw_init_buffer(buf);
    draw_plot_samples(buf, postfix, postfixCount);
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
    char expr[100];
    int result = 0;
    
    printf("input exp: ");
    if (fgets(expr, sizeof(expr), stdin) != NULL) {
        size_t len = strlen(expr);
        if (len > 0 && expr[len-1] == '\n') {
            expr[len-1] = '\0';
        }
        
        if (is_valid(expr)) {
            main_process(expr);
        } else {
            result = 1; 
        }
    } else {
        printf("Error reading input\n");
        result = 1; 
    }
    
    return result; 
}