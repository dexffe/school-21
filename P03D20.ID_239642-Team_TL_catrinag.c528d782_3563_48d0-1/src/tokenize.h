#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum { NUMBER, OPERATOR, FUNCTION, PARENTHESIS } TokenType;

typedef struct {
    TokenType type;
    union {
        double number;
        char operator;
        char* function;
    };
} Token;

int tokenize(const char* expr, Token** tokens, int* tokenCount);

#endif