#include "stack.h"

#include <stdlib.h>
#include <string.h>

stack* init() {
    stack* s = (stack*)malloc(sizeof(stack));
    if (!s) return NULL;

    s->capacity = 10;
    s->data = (int*)malloc(s->capacity * sizeof(int));
    if (!s->data) {
        free(s);
        return NULL;
    }

    s->top = 0;
    return s;
}

int push(stack* s, int value) {
    if (!s) return FAIL;

    if (s->top == s->capacity) {
        size_t new_capacity = s->capacity * 2;
        int* new_data = (int*)realloc(s->data, new_capacity * sizeof(int));
        if (!new_data) return FAIL;

        s->data = new_data;
        s->capacity = new_capacity;
    }

    s->data[s->top++] = value;
    return SUCCESS;
}

int pop(stack* s, int* result) {
    if (!s || s->top == 0) return FAIL;

    if (result) *result = s->data[--s->top];
    return SUCCESS;
}

void destroy(stack* s) {
    if (s) {
        free(s->data);
        free(s);
    }
}
