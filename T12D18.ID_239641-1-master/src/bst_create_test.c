#include <stdio.h>
#include <assert.h>
#include "bst.h"

// Вспомогательная функция для печати дерева
void print_tree(t_btree* root) {
    if (root == NULL) return;

    printf("Node %d\n", root->data);
    if (root->left) printf("  Left: %d\n", root->left->data);
    if (root->right) printf("  Right: %d\n", root->right->data);
    print_tree(root->left);
    print_tree(root->right);
}

// Простая функция для вывода значения узла
void print_node(int value) {
    printf("%d ", value);
}

// Тест для Quest3: создание узла
void test_node_creation() {
    t_btree* node = bstree_create_node(4);
    assert(node != NULL);
    assert(node->data == 4);
    assert(node->left == NULL);
    assert(node->right == NULL);
    printf("✅ Node created successfully\n");
    free(node);
}

// Тест для Quest4: вставка с кастомным компаратором
void test_insertion() {
    t_btree* root = bstree_create_node(5);

    bstree_insert(root, 7, default_cmp); // 7 > 5 → вставим вправо
    bstree_insert(root, 3, default_cmp); // 3 < 5 → вставим влево

    printf("✅ Tree after insertion:\n");
    print_tree(root);

    free(root->left);
    free(root->right);
    free(root);
}

// Тест для Quest5: обходы дерева
void test_traversal() {
    t_btree* root = bstree_create_node(5);
    assert(root != NULL);

    // Создаём дерево: 5 (корень), 3 (лево), 7 (право)
    bstree_insert(root, 3, default_cmp);
    bstree_insert(root, 7, default_cmp);

    // Проверяем структуру дерева
    assert(root->data == 5);
    assert(root->left->data == 3);
    assert(root->right->data == 7);

    // Тест Infix (по возрастанию)
    printf("✅ Infix (по возрастанию):\n");
    bstree_apply_infix(root, print_node);
    printf("\nОжидаемый результат: 3 5 7\n");

    // Тест Prefix (по вставке)
    printf("✅ Prefix (по вставке):\n");
    bstree_apply_prefix(root, print_node);
    printf("\nОжидаемый результат: 5 3 7\n");

    // Тест Postfix (по убыванию)
    printf("✅ Postfix (по убыванию):\n");
    bstree_apply_postfix(root, print_node);
    printf("\nОжидаемый результат: 3 7 5\n");

    // Очистка памяти
    free(root->left);
    free(root->right);
    free(root);
}

int main() {
    #ifdef QUEST3
        test_node_creation();
    #elif defined(QUEST4)
        test_insertion();
    #elif defined(QUEST5)
        test_traversal();
    #else
        printf("❌ Не указан флаг QUEST3, QUEST4 или QUEST5\n");
        return 1;
    #endif
    return 0;
}
