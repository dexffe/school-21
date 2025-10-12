#include "yard.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(const Token* tokens, int tokenCount, Token** postfix, int* postfixCount) {
    Token stack[100];
    int top = -1;
    *postfixCount = 0;

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == NUMBER) {
            (*postfix)[*postfixCount] = token;
            (*postfixCount)++;
        } else if (token.type == FUNCTION) {
            stack[++top] = token;
        } else if (token.type == OPERATOR) {
            while (top >= 0 && stack[top].type != PARENTHESIS &&
                   precedence(stack[top].operator) >= precedence(token.operator)) {
                (*postfix)[*postfixCount] = stack[top];
                (*postfixCount)++;
                top--;
            }
            stack[++top] = token;
        } else if (token.type == PARENTHESIS) {
            if (token.operator== '(') {
                stack[++top] = token;
            } else {
                while (top >= 0 && stack[top].operator!= '(') {
                    (*postfix)[*postfixCount] = stack[top];
                    (*postfixCount)++;
                    top--;
                }
                if (top >= 0 && stack[top].operator== '(') {
                    top--;
                }
                if (top >= 0 && stack[top].type == FUNCTION) {
                    (*postfix)[*postfixCount] = stack[top];
                    (*postfixCount)++;
                    top--;
                }
            }
        }
    }

    while (top >= 0) {
        (*postfix)[*postfixCount] = stack[top];
        (*postfixCount)++;
        top--;
    }
}
