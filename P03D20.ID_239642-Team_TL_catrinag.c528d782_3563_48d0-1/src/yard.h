#ifndef DIJKSTRA_H
#define DIJKSTRA_H

int precedence(char op);
void infixToPostfix(Token* tokens, int tokenCount, Token** postfix, int* postfixCount);
void printTokens(Token* tokens, int count);

#endif
