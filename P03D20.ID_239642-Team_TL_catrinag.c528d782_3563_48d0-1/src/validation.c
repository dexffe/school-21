#include "validation.h"
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

static int is_function_name(const char* name) {
    int result = 0;
    if (name && (strcmp(name, "sin") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "tan") == 0 ||
                 strcmp(name, "ctg") == 0 || strcmp(name, "log") == 0 || strcmp(name, "ln") == 0 ||
                 strcmp(name, "sqrt") == 0)) {
        result = 1;
    }
    return result;
}

static int check_brackets(const Token* tokens, int token_count) {
    int balance = 0;
    int result = SUCCESS;
    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == PARENTHESIS) {
            if (tokens[i].operator == '(') {
                balance++;
            } else {
                balance--;
                if (balance < 0) {
                    result = FAIL;
                    break;
                }
            }
        }
    }
    if (result == SUCCESS && balance != 0) {
        result = FAIL;
    }
    return result;
}

static int check_operators(const Token* tokens, int token_count) {
    int result = token_count > 0 ? SUCCESS : FAIL;
    for (int i = 0; i < token_count && result == SUCCESS; i++) {
        if (tokens[i].type == OPERATOR) {
            if (i == token_count - 1 ||
                (i == 0 && tokens[i].operator != '+' && tokens[i].operator != '-') ||
                (i > 0 && tokens[i - 1].type != NUMBER &&
                 !(tokens[i - 1].type == PARENTHESIS && tokens[i - 1].operator == ')') &&
                 !(tokens[i].operator == '+' || tokens[i].operator == '-' ||
                   tokens[i - 1].type == OPERATOR ||
                   (tokens[i - 1].type == PARENTHESIS && tokens[i - 1].operator == '('))) ||
                (i + 1 < token_count && tokens[i + 1].type != NUMBER &&
                 tokens[i + 1].type != FUNCTION &&
                 !(tokens[i + 1].type == PARENTHESIS && tokens[i + 1].operator == '('))) {
                result = FAIL;
            }
        }
    }
    return result;
}

static int check_functions(const Token* tokens, int token_count) {
    int result = SUCCESS;
    for (int i = 0; i < token_count && result == SUCCESS; i++) {
        if (tokens[i].type == FUNCTION &&
            (i + 1 >= token_count || tokens[i + 1].type != PARENTHESIS ||
             tokens[i + 1].operator != '(' || !is_function_name(tokens[i].function))) {
            result = FAIL;
        }
    }
    return result;
}

static int check_numbers_and_variables(const Token* tokens, int token_count) {
    int result = SUCCESS;
    for (int i = 0; i < token_count && result == SUCCESS; i++) {
        if (tokens[i].type == NUMBER && i + 1 < token_count &&
            tokens[i + 1].type != OPERATOR &&
            !(tokens[i + 1].type == PARENTHESIS && tokens[i + 1].operator == ')')) {
            result = FAIL;
        }
    }
    return result;
}

int validate_expression(const char* infix) {
    int result = FAIL;
    Token* tokens = NULL;
    int token_count = 0;

    if (infix && infix[0] != '\0') {
        tokenize((char*)infix, &tokens, &token_count);
        if (token_count > 0 && tokens != NULL) {
            if (check_brackets(tokens, token_count) == SUCCESS &&
                check_operators(tokens, token_count) == SUCCESS &&
                check_functions(tokens, token_count) == SUCCESS &&
                check_numbers_and_variables(tokens, token_count) == SUCCESS) {
                result = SUCCESS;
            }
            for (int i = 0; i < token_count; i++) {
                if (tokens[i].type == FUNCTION) {
                    free(tokens[i].function);
                }
            }
            free(tokens);
        }
    }
    return result;
}