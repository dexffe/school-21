#ifndef STACK_H
#define STACK_H

#include <stddef.h>  // Для size_t

#define SUCCESS 0
#define FAIL 1

// Структура динамического стека
typedef struct stack {
    int* data;
    size_t top;
    size_t capacity;
} stack;

stack* init();

int push(stack* s, int value);

int pop(stack* s, int* result);

void destroy(stack* s);

#endif
