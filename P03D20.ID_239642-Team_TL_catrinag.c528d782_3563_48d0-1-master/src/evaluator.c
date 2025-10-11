#include "evaluator.h"
#include <math.h>

double compute_function(int func_idx, double x) {
    switch(func_idx) {
        case 0: return sin(x);       // sin
        case 1: return cos(x);       // cos
        case 2: return tan(x);       // tan
        case 3: return 1.0 / tan(x); // ctg
        case 4: return sqrt(x);      // sqrt
        case 5: return log(x);       // ln
        default: return NAN;
    }
}

double evaluate_postfix(Token* postfix, int count, double x) {
    Stack* eval_stack = stack_create(sizeof(Token), 16);
    for (int i = 0; i < count; i++) {
        Token t = postfix[i];
        if (t.type == TOK_NUMBER) {
            stack_push(eval_stack, &t);
        } else if (t.type == TOK_X) {
            Token x_token = {TOK_NUMBER, x, 0};
            stack_push(eval_stack, &x_token);
        } else if (t.type == TOK_FUNC) {
            Token* arg = (Token*)stack_pop(eval_stack);
            if (arg->type != TOK_NUMBER) {
                stack_free(eval_stack);
                return NAN;
            }
            double result = compute_function(t.func_idx, arg->value);
            Token res_token = {TOK_NUMBER, result, 0};
            stack_push(eval_stack, &res_token);
        } else {
            Token* b = (Token*)stack_pop(eval_stack);
            Token* a = (Token*)stack_pop(eval_stack);
            if (a->type != TOK_NUMBER || b->type != TOK_NUMBER) {
                stack_free(eval_stack);
                return NAN;
            }
            double result;
            switch(t.type) {
                case TOK_OP_ADD: result = a->value + b->value; break;
                case TOK_OP_SUB: result = a->value - b->value; break;
                case TOK_OP_MUL: result = a->value * b->value; break;
                case TOK_OP_DIV: 
                    if (b->value == 0) { stack_free(eval_stack); return NAN; }
                    result = a->value / b->value; break;
                case TOK_OP_POW: result = pow(a->value, b->value); break;
                default: result = NAN;
            }
            Token res_token = {TOK_NUMBER, result, 0};
            stack_push(eval_stack, &res_token);
        }
    }

    if (eval_stack->top != 0) {
        stack_free(eval_stack);
        return NAN;
    }

    Token* result_token = (Token*)eval_stack->items;
    double result = result_token->value;
    stack_free(eval_stack);
    return result;
}
