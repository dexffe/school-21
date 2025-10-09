#include "stack.h"

#include <assert.h>
#include <stdio.h>

// Тест для push
int test_push() {
    stack* s = init();
    if (!s) return FAIL;

    // Проверяем добавление элементов
    for (int i = 0; i < 20; i++) {
        if (push(s, i) != SUCCESS) {
            destroy(s);
            return FAIL;
        }
    }

    // Проверяем порядок элементов
    for (int i = 19; i >= 0; i--) {
        int result;
        if (pop(s, &result) != SUCCESS || result != i) {
            destroy(s);
            return FAIL;
        }
    }

    destroy(s);
    return SUCCESS;
}

// Тест для pop
int test_pop() {
    stack* s = init();
    if (!s) return FAIL;

    // Добавляем элементы
    for (int i = 0; i < 10; i++) {
        push(s, i);
    }

    // Проверяем удаление
    for (int i = 9; i >= 0; i--) {
        int result;
        if (pop(s, &result) != SUCCESS || result != i) {
            destroy(s);
            return FAIL;
        }
    }

    // Попытка удалить из пустого стека
    int result;
    if (pop(s, &result) == SUCCESS) {
        destroy(s);
        return FAIL;
    }

    destroy(s);
    return SUCCESS;
}

int main() {
    int result = SUCCESS;

    if (test_push() != SUCCESS) {
        printf("❌ Test push failed\n");
        result = FAIL;
    }

    if (test_pop() != SUCCESS) {
        printf("❌ Test pop failed\n");
        result = FAIL;
    }

    if (result == SUCCESS) {
        printf("✅ All tests passed!\n");
    } else {
        printf("❌ Some tests failed\n");
    }

    return result;
}
