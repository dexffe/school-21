#include "tokenize.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DBL_MAX 1.7976931348623157e+308

int isdigit(int c) { return (c >= '0' && c <= '9'); }

int isalpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

int isspace(int c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

char* my_strdup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
}

void free_tokens(Token* tokens, int tokenCount) {
    if (tokens == NULL) return;

    for (int i = 0; i < tokenCount; i++) {
        if (tokens[i].type == FUNCTION && tokens[i].function != NULL) {
            free(tokens[i].function);
        }
    }
    free(tokens);
}

int tokenize(const char* expr, Token** tokens, int* tokenCount) {
    int i = 0, j = 0;
    *tokenCount = 0;

    int maxTokens = strlen(expr) + 1;
    *tokens = (Token*)malloc(maxTokens * sizeof(Token));
    if (*tokens == NULL) {
        return -1;
    }

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        Token token;
        memset(&token, 0, sizeof(Token));

        if (isdigit(expr[i]) || (expr[i] == '.' && isdigit(expr[i + 1]))) {
            token.type = NUMBER;
            char* endptr;
            token.number = strtod(&expr[i], &endptr);
            i = endptr - expr;
        } else if (expr[i] == 'x') {
            token.type = NUMBER;
            token.number = DBL_MAX;
            i++;
        } else if (expr[i] == '(' || expr[i] == ')') {
            token.type = PARENTHESIS;
            token.operator= expr[i];
            i++;
        } else if (strchr("+-*/", expr[i])) {
            token.type = OPERATOR;
            token.operator= expr[i];
            i++;
        } else if (isalpha(expr[i])) {
            token.type = FUNCTION;
            char func[10];
            int len = 0;
            while (isalpha(expr[i]) && len < 9) {
                func[len++] = expr[i++];
            }
            func[len] = '\0';
            token.function = my_strdup(func);
            if (token.function == NULL) {
                free_tokens(*tokens, j);
                *tokens = NULL;
                *tokenCount = 0;
                return -1;
            }
        } else {
            if (token.type == FUNCTION && token.function != NULL) {
                free(token.function);
            }
            free_tokens(*tokens, j);
            *tokens = NULL;
            *tokenCount = 0;
            return -1;
        }

        (*tokens)[j++] = token;
        (*tokenCount)++;
    }

    if (*tokenCount > 0) {
        Token* temp = (Token*)realloc(*tokens, (*tokenCount) * sizeof(Token));
        if (temp != NULL) {
            *tokens = temp;
        }
    } else {
        free(*tokens);
        *tokens = NULL;
    }
    return 0;
}