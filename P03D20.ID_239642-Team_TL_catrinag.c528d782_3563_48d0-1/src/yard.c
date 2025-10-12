#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tokenize.h"
#include "yard.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(Token* tokens, int tokenCount, Token** postfix, int* postfixCount) {
    Token stack[100];
    int top = -1;
    *postfixCount = 0;

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == NUMBER) {
            (*postfix)[*postfixCount] = token;
            (*postfixCount)++;
        }
        else if (token.type == FUNCTION) {
            // Функции сразу помещаем в стек
            stack[++top] = token;
        }
        else if (token.type == OPERATOR) {
            while (top >= 0 && stack[top].type != PARENTHESIS && precedence(stack[top].operator) >= precedence(token.operator)) {
                (*postfix)[*postfixCount] = stack[top];
                (*postfixCount)++;
                top--;
            }
            stack[++top] = token;
        }
        else if (token.type == PARENTHESIS) {
            if (token.operator == '(') {
                stack[++top] = token;
            }
            else {
                while (top >= 0 && stack[top].operator != '(') {
                    (*postfix)[*postfixCount] = stack[top];
                    (*postfixCount)++;
                    top--;
                }
                if (top >= 0 && stack[top].operator == '(') {
                    top--;  // Pop '('
                }
                // После закрывающей скобки выталкиваем функцию из стека
                if (top >= 0 && stack[top].type == FUNCTION) {
                    (*postfix)[*postfixCount] = stack[top];
                    (*postfixCount)++;
                    top--;
                }
            }
        }
    }

    // Pop remaining operators
    while (top >= 0) {
        (*postfix)[*postfixCount] = stack[top];
        (*postfixCount)++;
        top--;
    }
}

/*
void infixToPostfix(Token* tokens, int tokenCount, Token** postfix, int* postfixCount) {
    Token stack[100];
    int top = -1;
    *postfixCount = 0;

    for (int i = 0; i < tokenCount; i++) {
        Token token = tokens[i];

        if (token.type == NUMBER) {
            (*postfix)[*postfixCount] = token;
            (*postfixCount)++;
        }
        else if (token.type == FUNCTION) {
            // Функции сразу помещаем в стек
            stack[++top] = token;
        }
        else if (token.type == OPERATOR) {
            while (top >= 0 && precedence(stack[top].operator) >= precedence(token.operator)) {
                (*postfix)[*postfixCount] = stack[top];
                (*postfixCount)++;
                top--;
            }
            stack[++top] = token;
        }
        else if (token.type == PARENTHESIS) {
            if (token.operator == '(') {
                stack[++top] = token;
            }
            else {
                while (top >= 0 && stack[top].operator != '(') {
                    (*postfix)[*postfixCount] = stack[top];
                    (*postfixCount)++;
                    top--;
                }
                if (top >= 0 && stack[top].operator == '(') {
                    top--;  // Pop '('
                }
            }
        }
    }

    // Pop remaining operators
    while (top >= 0) {
        (*postfix)[*postfixCount] = stack[top];
        (*postfixCount)++;
        top--;
    }
}*/

void printTokens(Token* tokens, int count) {
    for (int i = 0; i < count; i++) {
        switch (tokens[i].type) {
            case NUMBER:
                printf("%.2f ", tokens[i].number);
                break;
            case OPERATOR:
                printf("%c ", tokens[i].operator);
                break;
            case PARENTHESIS:
                printf("%c ", tokens[i].operator);
                break;
            case FUNCTION:
                printf("%s ", tokens[i].function);
                break;
        }
    }
    printf("\n");
}