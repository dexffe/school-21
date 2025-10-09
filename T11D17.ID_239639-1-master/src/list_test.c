#include "list.h"

#include <assert.h>
#include <stdio.h>

#include "door_struct.h"

#define SUCCESS 0
#define FAIL 1

// Создание тестовой двери
struct door create_test_door(int id, int status) {
    struct door d = {id, status};
    return d;
}

// Тест для add_door
int test_add_door() {
    // Создаем начальную дверь и узел
    struct door d1 = create_test_door(1, 0);
    struct node* root = init(&d1);
    if (!root) return FAIL;

    // Добавляем вторую дверь
    struct door d2 = create_test_door(2, 1);
    const struct node* added = add_door(root, &d2);
    if (!added) {
        destroy(root);
        return FAIL;
    }

    // Проверяем структуру списка
    if (added->data.id != 2 || root->next != added) {
        destroy(root);
        return FAIL;
    }

    // Очистка
    destroy(root);
    return SUCCESS;
}

// Тест для remove_door
int test_remove_door() {
    // Создаем список из трех дверей
    struct door d1 = create_test_door(1, 0);
    struct door d2 = create_test_door(2, 1);
    struct door d3 = create_test_door(3, 0);

    struct node* root = init(&d1);
    if (!root) return FAIL;

    struct node* n2 = add_door(root, &d2);
    if (!n2) {
        destroy(root);
        return FAIL;
    }

    const struct node* n3 = add_door(n2, &d3);
    if (!n3) {
        destroy(root);
        return FAIL;
    }

    // Удаляем второй узел
    root = remove_door(n2, root);  // Обновляем root после удаления
    if (!root) {
        destroy(root);
        return FAIL;
    }

    // Проверяем структуру после удаления
    if (root->next != n3 || n3->data.id != 3) {
        destroy(root);
        return FAIL;
    }

    // Очистка
    destroy(root);
    return SUCCESS;
}

// Тест для find_door
int test_find_door() {
    // Создаем список из трех дверей
    struct door d1 = create_test_door(1, 0);
    struct door d2 = create_test_door(2, 1);
    struct door d3 = create_test_door(3, 0);

    struct node* root = init(&d1);
    if (!root) return FAIL;

    struct node* n2 = add_door(root, &d2);
    if (!n2) {
        destroy(root);
        return FAIL;
    }

    const struct node* n3 = add_door(n2, &d3);
    if (!n3) {
        destroy(root);
        return FAIL;
    }

    // Тестируем find_door
    const struct node* found = find_door(2, root);
    if (!found || found != n2 || found->data.id != 2) {
        destroy(root);
        return FAIL;
    }

    // Проверяем несуществующий ID
    const struct node* not_found = find_door(999, root);
    if (not_found != NULL) {
        destroy(root);
        return FAIL;
    }

    // Очистка
    destroy(root);
    return SUCCESS;
}

int main() {
    int result = SUCCESS;

    if (test_add_door() != SUCCESS) {
        printf("❌ Test add_door failed\n");
        result = FAIL;
    }

    if (test_remove_door() != SUCCESS) {
        printf("❌ Test remove_door failed\n");
        result = FAIL;
    }

    if (test_find_door() != SUCCESS) {
        printf("❌ Test find_door failed\n");
        result = FAIL;
    }

    if (result == SUCCESS) {
        printf("✅ All tests passed!\n");
    } else {
        printf("❌ Some tests failed\n");
    }

    return result;
}
