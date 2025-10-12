#include <math.h>
#include <stdio.h>
#include <string.h>

#include "tokenize.h"

#define DBL_MAX 1.7976931348623157e+308

double evaluatePostfix(const Token* postfix, int postfixCount, double x) {
    double stack[100];
    int top = -1;
    int flag = 0;
    double result;

    for (int i = 0; i < postfixCount; i++) {
        Token token = postfix[i];

        if (token.type == NUMBER) {
            if (token.number == DBL_MAX)
                stack[++top] = x;
            else
                stack[++top] = token.number;
        } else if (token.type == OPERATOR) {
            double b = stack[top--];
            double a = stack[top--];
            switch (token.operator) {
                case '+':
                    stack[++top] = a + b;
                    break;
                case '-':
                    stack[++top] = a - b;
                    break;
                case '*':
                    stack[++top] = a * b;
                    break;
                case '/':
                    stack[++top] = a / b;
                    break;
            }
        } else if (token.type == FUNCTION) {
            double arg = stack[top--];

            if (strcmp(token.function, "sin") == 0) {
                stack[++top] = sin(arg);
            } else if (strcmp(token.function, "cos") == 0) {
                stack[++top] = cos(arg);
            } else if (strcmp(token.function, "tan") == 0) {
                stack[++top] = tan(arg);
            } else if (strcmp(token.function, "ctg") == 0) {
                if (fabs(sin(arg)) < 1e-9) return NAN;
                stack[++top] = cos(arg) / sin(arg);
            } else if (strcmp(token.function, "sqrt") == 0) {
                if (stack[top] < 0) return NAN;
                stack[++top] = sqrt(arg);
            } else if (strcmp(token.function, "ln") == 0) {
                if (stack[top] <= 0) return NAN;
                stack[++top] = log(arg);
            } else {
                result = NAN;
                flag = 1;
                break;
            }
        }
    }
    if (flag == 0) {
        result = stack[top];
    }

    return result;
}