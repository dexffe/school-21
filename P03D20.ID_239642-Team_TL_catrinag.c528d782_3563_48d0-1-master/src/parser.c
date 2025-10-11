#include "parser.h"
#include <ctype.h>
#include <string.h>
#include <math.h>

const char* functions[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln"};
const int NUM_FUNCTIONS = 6;

int tokenize_and_convert(const char* expr, Token** postfix, int* postfix_count) {
    Stack* op_stack = stack_create(sizeof(Token), 16);
    *postfix_count = 0;
    *postfix = NULL;

    const char* p = expr;
    while (*p) {
        if (isspace(*p)) { p++; continue; }

        // Проверка на функцию
        if (isalpha(*p)) {
            char func_name[8];
            int i = 0;
            while (isalpha(*p)) func_name[i++] = *p++;
            func_name[i] = '\0';

            int is_func = 0;
            for (int j = 0; j < NUM_FUNCTIONS; j++) {
                if (strcmp(func_name, functions[j]) == 0) {
                    is_func = 1;
                    break;
                }
            }

            if (!is_func) {
                stack_free(op_stack);
                return 0;
            }

            for (int j = 0; j < NUM_FUNCTIONS; j++) {
                if (strcmp(func_name, functions[j]) == 0) {
                    Token t = {TOK_FUNC, 0, j};
                    stack_push(op_stack, &t);
                    break;
                }
            }

            if (*p != '(') {
                stack_free(op_stack);
                return 0;
            }
            p++;
            continue;
        }

        // Обработка остальных токенов
        TokenType token_type = TOK_NONE;
        switch(*p) {
            case '+': token_type = TOK_OP_ADD; break;
            case '-': token_type = TOK_OP_SUB; break;
            case '*': token_type = TOK_OP_MUL; break;
            case '/': token_type = TOK_OP_DIV; break;
            case '^': token_type = TOK_OP_POW; break;
            case '(': token_type = TOK_LPAR; break;
            case ')': token_type = TOK_RPAR; break;
            case 'x': token_type = TOK_X; break;
            default:
                if (isdigit(*p) || *p == '.') token_type = TOK_NUMBER;
                else {
                    stack_free(op_stack);
                    return 0;
                }
        }

        if (token_type == TOK_NUMBER) {
            char num_str[32];
            int i = 0;
            while (isdigit(*p) || *p == '.') num_str[i++] = *p++;
            num_str[i] = '\0';
            Token t = {TOK_NUMBER, atof(num_str), 0};
            *postfix = realloc(*postfix, ++(*postfix_count) * sizeof(Token));
            (*postfix)[*postfix_count - 1] = t;
        } else if (token_type == TOK_X) {
            Token t = {TOK_X, 0, 0};
            *postfix = realloc(*postfix, ++(*postfix_count) * sizeof(Token));
            (*postfix)[*postfix_count - 1] = t;
            p++;
        } else if (token_type == TOK_LPAR) {
            Token t = {TOK_LPAR, 0, 0};
            stack_push(op_stack, &t);
            p++;
        } else if (token_type == TOK_RPAR) {
            while (!stack_is_empty(op_stack)) {
                Token* t = stack_pop(op_stack);
                if (t->type == TOK_LPAR) break;
                *postfix = realloc(*postfix, ++(*postfix_count) * sizeof(Token));
                (*postfix)[*postfix_count - 1] = *t;
            }
            if (stack_is_empty(op_stack)) {
                stack_free(op_stack);
                return 0;
            }
            p++;
        } else {
            while (!stack_is_empty(op_stack)) {
                Token* top = (Token*)((char*)op_stack->items + op_stack->top * sizeof(Token));
                if (top->type != TOK_LPAR && 
                    get_precedence(top->type) >= get_precedence(token_type)) {
                    Token* t = stack_pop(op_stack);
                    *postfix = realloc(*postfix, ++(*postfix_count) * sizeof(Token));
                    (*postfix)[*postfix_count - 1] = *t;
                } else break;
            }
            Token t = {token_type, 0, 0};
            stack_push(op_stack, &t);
            p++;
        }
    }

    while (!stack_is_empty(op_stack)) {
        Token* t = stack_pop(op_stack);
        if (t->type == TOK_LPAR) {
            stack_free(op_stack);
            return 0;
        }
        *postfix = realloc(*postfix, ++(*postfix_count) * sizeof(Token));
        (*postfix)[*postfix_count - 1] = *t;
    }

    stack_free(op_stack);
    return 1;
}

int get_precedence(TokenType op) {
    switch(op) {
        case TOK_OP_ADD: case TOK_OP_SUB: return 1;
        case TOK_OP_MUL: case TOK_OP_DIV: return 2;
        case TOK_OP_POW: return 3;
        default: return 0;
    }
}
