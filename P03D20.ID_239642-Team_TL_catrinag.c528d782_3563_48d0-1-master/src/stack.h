#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    int top;
    void* items;
} Stack;

// Создание стека
Stack* stack_create(size_t element_size, size_t initial_capacity);

// Освобождение стека
void stack_free(Stack* s);

// Добавление элемента
void stack_push(Stack* s, const void* data);

// Извлечение элемента
void* stack_pop(Stack* s);

// Проверка пустоты
int stack_is_empty(const Stack* s);

#endif // STACK_H
