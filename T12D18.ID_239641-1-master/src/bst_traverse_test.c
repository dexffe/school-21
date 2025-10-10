#include <stdio.h>
#include <assert.h>
#include "bst.h"
#include <stdlib.h>

// Простая функция для вывода значения узла
void print_node(int value) {
    printf("%d ", value);
}

// Вспомогательная функция для проверки результата обхода
void test_traversal(const char* name, t_btree* root, void (*traversal_func)(t_btree*, void (*)(int))) {
    printf("✅ %s:\n", name);
    traversal_func(root, print_node);
    printf("\n");
}

int main() {
    // Создание дерева с кастомным компаратором
    t_btree* root = bstree_create_node(5);
    assert(root != NULL);

    // Вставляем 3 и 7 (с default_cmp)
    bstree_insert(root, 3, default_cmp); // 3 < 5 → вставим влево
    bstree_insert(root, 7, default_cmp); // 7 > 5 → вставим вправо

    // Тестирование всех трёх обходов
    test_traversal("Infix (по возрастанию)", root, bstree_apply_infix);
    test_traversal("Prefix (по вставке)", root, bstree_apply_prefix);
    test_traversal("Postfix (по убыванию)", root, bstree_apply_postfix);

    // Очистка памяти
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
