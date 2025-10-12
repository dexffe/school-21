#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"

#define DBL_MAX 1.7976931348623157e+308

int isdigit(int c) {
    return (c >= '0' && c <= '9');
}

int isalpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int isspace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void tokenize(char* expr, Token** tokens, int* tokenCount) {
    int i = 0, j = 0;
    *tokenCount = 0;

    // Сначала подсчитаем количество токенов для выделения памяти
    int maxTokens = strlen(expr) + 1;
    *tokens = (Token*)malloc(maxTokens * sizeof(Token));
    if (*tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    while (expr[i] != '\0') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        Token token;

        if (isdigit(expr[i]) || (expr[i] == '.' && isdigit(expr[i+1]))) {
            // Parse number
            token.type = NUMBER;
            char* endptr;
            token.number = strtod(&expr[i], &endptr);
            i = endptr - expr;
        }
        else if (expr[i] == 'x') {
            // varfiable!!!!!!!!
            token.type = NUMBER;
            token.number = DBL_MAX;
            i++;
        }
        else if (expr[i] == '(' || expr[i] == ')') {
            // Parenthesis
            token.type = PARENTHESIS;
            token.operator = expr[i];
            i++;
        }
        else if (strchr("+-*/", expr[i])) {
            // Operator
            token.type = OPERATOR;
            token.operator = expr[i];
            i++;
        }
        else if (isalpha(expr[i])) {
            // Handle functions (e.g., sin, cos, etc.)
            token.type = FUNCTION;
            char func[10];
            int len = 0;
            while (isalpha(expr[i]) && len < 9) {
                func[len++] = expr[i++];
            }
            func[len] = '\0';
            token.function = strdup(func);
            if (token.function == NULL) {
                fprintf(stderr, "Memory allocation failed for function name\n");
                break;
            }
        }
        else {
            // Неизвестный символ
            fprintf(stderr, "Unknown character: %c\n", expr[i]);
            i++;
            continue;
        }

        (*tokens)[j++] = token;
        (*tokenCount)++;
    }

    // Перераспределяем память под точное количество токенов
    if (*tokenCount > 0) {
        Token* temp = (Token*)realloc(*tokens, (*tokenCount) * sizeof(Token));
        if (temp != NULL) {
            *tokens = temp;
        }
    } else {
        free(*tokens);
        *tokens = NULL;
    }
}