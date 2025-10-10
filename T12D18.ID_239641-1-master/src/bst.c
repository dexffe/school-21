#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Создание узла
t_btree* bstree_create_node(int item) {
    t_btree* node = (t_btree*)malloc(sizeof(t_btree));
    if (!node) return NULL;

    node->data = item;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Стандартный компаратор
int default_cmp(int a, int b) {
    return a - b;
}

// Вставка узла
void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int)) {
    if (!root) return;

    t_btree* current = root;
    bool found = false;
    while (!found) {
        int cmp_result = cmpf(item, current->data);

        if (cmp_result < 0) {
            if (current->left == NULL) {
                current->left = bstree_create_node(item);
                found = true;
            }
            current = current->left;
        } else if (cmp_result > 0) {
            if (current->right == NULL) {
                current->right = bstree_create_node(item);
                found = true;
            }
            current = current->right;
        } else {
            found = true;
        }
    }
}

// Infix (левое -> корень -> правое)
void bstree_apply_infix(t_btree* root, void (*applyf)(int)) {
    if (!root) return;
    bstree_apply_infix(root->left, applyf);
    applyf(root->data);
    bstree_apply_infix(root->right, applyf);
}

// Prefix (корень -> левое -> правое)
void bstree_apply_prefix(t_btree* root, void (*applyf)(int)) {
    if (!root) return;
    applyf(root->data);
    bstree_apply_prefix(root->left, applyf);
    bstree_apply_prefix(root->right, applyf);
}

// Postfix (левое -> правое -> корень)
void bstree_apply_postfix(t_btree* root, void (*applyf)(int)) {
    if (!root) return;
    bstree_apply_postfix(root->left, applyf);
    bstree_apply_postfix(root->right, applyf);
    applyf(root->data);
}
