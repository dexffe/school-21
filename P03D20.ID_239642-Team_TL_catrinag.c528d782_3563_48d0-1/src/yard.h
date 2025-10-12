#include "tokenize.h"

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int precedence(char op);
void infixToPostfix(const Token* tokens, int tokenCount, Token** postfix, int* postfixCount);

#endif
