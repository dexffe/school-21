#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef enum {NUMBER, OPERATOR, FUNCTION, PARENTHESIS} TokenType;

typedef struct {
    TokenType type;
    union {
        double number;
        char operator;
        char* function;
    };
} Token;

void tokenize(char* expr, Token** tokens, int* tokenCount);

#endif