#include "list.h"

#include <stdlib.h>

// Инициализация нового узла списка
struct node* init(const struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) return NULL;

    new_node->data = *door;
    new_node->next = NULL;
    return new_node;
}

// Добавление новой двери после указанного узла
struct node* add_door(struct node* elem, const struct door* door) {
    if (!elem) return NULL;

    struct node* new_node = init(door);
    if (!new_node) return NULL;

    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

// Поиск двери по ID
struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current) {
        if (current->data.id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Удаление узла из списка
struct node* remove_door(struct node* elem, struct node* root) {
    if (!elem || !root) return NULL;

    // Если удаляем корень
    if (elem == root) {
        struct node* temp = root;
        root = root->next;
        free(temp);
        return root;
    }

    // Поиск предыдущего узла
    struct node* current = root;
    while (current && current->next != elem) {
        current = current->next;
    }

    if (!current) return NULL;  // Элемент не найден

    // Удаление узла
    struct node* temp = elem;
    current->next = elem->next;
    free(temp);
    return root;
}

// Освобождение памяти всего списка
void destroy(struct node* root) {
    while (root) {
        struct node* next = root->next;
        free(root);
        root = next;
    }
}
