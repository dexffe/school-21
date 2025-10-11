#include "stack.h"
#include "parser.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

Stack* stack_create(size_t element_size, size_t initial_capacity) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = -1;
    s->items = malloc(initial_capacity * element_size);
    return s;
}

void stack_free(Stack* s) {
    free(s->items);
    free(s);
}

void stack_push(Stack* s, const void* data) {
    if (s->top >= 0 && s->top % 16 == 15) {
        size_t new_cap = s->top + 16;
        s->items = realloc(s->items, new_cap * sizeof(Token));
    }
    memcpy((char*)s->items + (s->top + 1) * sizeof(Token), data, sizeof(Token));
    s->top++;
}

void* stack_pop(Stack* s) {
    if (s->top == -1) return NULL;
    return (char*)s->items + s->top-- * sizeof(Token);
}

int stack_is_empty(const Stack* s) {
    return s->top == -1;
}
