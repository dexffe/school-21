#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>
#include "stack.h"

typedef enum {
    TOK_NONE,
    TOK_NUMBER,
    TOK_X,
    TOK_OP_ADD,
    TOK_OP_SUB,
    TOK_OP_MUL,
    TOK_OP_DIV,
    TOK_OP_POW,
    TOK_LPAR,
    TOK_RPAR,
    TOK_FUNC
} TokenType;

typedef struct {
    TokenType type;
    double value;     // Для чисел и результатов
    int func_idx;     // Для функций
} Token;

// Таблица поддерживаемых функций
extern const char* functions[];
extern const int NUM_FUNCTIONS;

// Преобразование выражения в постфиксную форму
int tokenize_and_convert(const char* expr, Token** postfix, int* postfix_count);

#endif // PARSER_H
