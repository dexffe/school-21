#include "validation.h"
#include "tokenize.h"
#include <string.h>
#include <stdlib.h>

static int is_function_name(const char* name) {
    if (!name) return 0;
    return (strcmp(name, "sin") == 0 ||
            strcmp(name, "cos") == 0 ||
            strcmp(name, "tan") == 0 ||
            strcmp(name, "ctg") == 0 ||
            strcmp(name, "log") == 0 ||
            strcmp(name, "ln")  == 0 ||
            strcmp(name, "sqrt") == 0);
}

static int check_brackets(Token* tokens, int token_count) {
    int balance = 0;
    int i = 0;
    int valid = SUCCESS;

    while (i < token_count && valid == SUCCESS) {
        if (tokens[i].type == PARENTHESIS) {
            if (tokens[i].operator == '(') {
                balance++;
            } else if (tokens[i].operator == ')') {
                balance--;
                if (balance < 0) {
                    valid = FAIL;
                }
            }
        }
        i++;
    }

    if (valid == SUCCESS && balance != 0) {
        valid = FAIL;
    }

    return valid;
}

static int check_operators(Token* tokens, int token_count) {
    int i = 0;
    int valid = SUCCESS;

    while (i < token_count && valid == SUCCESS) {
        if (tokens[i].type == OPERATOR) {
            char op = tokens[i].operator;
            if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^') {
                valid = FAIL;
            }
            else if (i == 0) {
                if (op != '+' && op != '-') {
                    valid = FAIL;
                }
            }
            else if (i == token_count - 1) {
                valid = FAIL;
            }
            else {
                Token* prev = &tokens[i - 1];
                if (prev->type == OPERATOR || 
                    (prev->type == PARENTHESIS && prev->operator == '(')) {
                    if (op != '+' && op != '-') {
                        valid = FAIL;
                    }
                }
            }
        }
        i++;
    }

    return valid;
}

static int check_functions(Token* tokens, int token_count) {
    int i = 0;
    int valid = SUCCESS;

    while (i < token_count && valid == SUCCESS) {
        if (tokens[i].type == FUNCTION) {
            if (i + 1 >= token_count ||
                tokens[i + 1].type != PARENTHESIS ||
                tokens[i + 1].operator != '(' ||
                !is_function_name(tokens[i].function)) {
                valid = FAIL;
            }
        }
        i++;
    }

    return valid;
}

int validate_expression(const char* infix) {
    Token* tokens = NULL;
    int token_count = 0;
    int result = FAIL;

    tokenize((char*)infix, &tokens, &token_count);

    if (token_count > 0 && tokens != NULL) {
        int brackets_ok = check_brackets(tokens, token_count);
        int operators_ok = check_operators(tokens, token_count);
        int functions_ok = check_functions(tokens, token_count);

        if (brackets_ok == SUCCESS && operators_ok == SUCCESS && functions_ok == SUCCESS) {
            result = SUCCESS;
        }

        free(tokens);
    }

    return result;
}