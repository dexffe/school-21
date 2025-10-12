#include "stack.h"
#include <stdlib.h>
#include <string.h>

struct node_stack* init(const char* value) {
    if (!value) return NULL;

    struct node_stack* node = calloc(1, sizeof(struct node_stack));
    if (node) {
        strncpy(node->value, value, MAX_STR_LEN - 1);
        node->value[MAX_STR_LEN - 1] = '\0'; 
        node->prev = NULL;
    }
    return node;
}

struct node_stack* push(struct node_stack* stack, const char* value) {
    if (!value) return stack;

    struct node_stack* node = calloc(1, sizeof(struct node_stack));
    if (node) {
        strncpy(node->value, value, MAX_STR_LEN - 1);
        node->value[MAX_STR_LEN - 1] = '\0';
        node->prev = stack;
        stack = node;
    }
    return stack;
}

struct node_stack* pop(struct node_stack* stack, char* value_out) {
    if (!stack || !value_out) return NULL;

    strncpy(value_out, stack->value, MAX_STR_LEN);
    struct node_stack* new_top = stack->prev;
    free(stack);
    return new_top;
}

char* peek(struct node_stack* stack, char* value_out) {
    if (!stack || !value_out) return NULL;

    strncpy(value_out, stack->value, MAX_STR_LEN);
    return value_out;
}

void destroy(struct node_stack* stack) {
    char tmp[MAX_STR_LEN];
    while ((stack = pop(stack, tmp)) != NULL);
}