#include <stdio.h>
#include <stdlib.h>

// ==================== AVL ДЕРЕВО ====================

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

typedef struct {
    AVLNode* root;
} AVLTree;

// Вспомогательные функции для AVL

// Максимум из двух чисел
int maxim(int a, int b) {
    return (a > b) ? a : b;
}

// Получение высоты узла
int avl_height(AVLNode* node) {
    if (node == NULL) return -1;
    return node->height;
}

// Получение баланс-фактора
int avl_balance_factor(AVLNode* node) {
    if (node == NULL) return 0;
    return avl_height(node->left) - avl_height(node->right);
}

// Создание нового узла AVL
AVLNode* avl_create_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    if (!node) return NULL;
    node->key = key;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Правый поворот (Left-Left case)
AVLNode* avl_rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    
    // Выполняем поворот
    x->right = y;
    y->left = T2;
    
    // Обновляем высоты
    y->height = maxim(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = maxim(avl_height(x->left), avl_height(x->right)) + 1;
    
    return x;
}

// Левый поворот (Right-Right case)
AVLNode* avl_rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    
    // Выполняем поворот
    y->left = x;
    x->right = T2;
    
    // Обновляем высоты
    x->height = maxim(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = maxim(avl_height(y->left), avl_height(y->right)) + 1;
    
    return y;
}

// Вставка в AVL дерево
AVLNode* avl_insert(AVLNode* node, int key) {
    // 1. Обычная вставка как в BST
    if (node == NULL) {
        return avl_create_node(key);
    }
    
    if (key < node->key) {
        node->left = avl_insert(node->left, key);
    } else if (key > node->key) {
        node->right = avl_insert(node->right, key);
    } else {
        return node; // Дубликаты не допускаются
    }
    
    // 2. Обновляем высоту текущего узла
    node->height = maxim(avl_height(node->left), avl_height(node->right)) + 1;
    
    // 3. Получаем баланс-фактор
    int balance = avl_balance_factor(node);
    
    // 4. Если узел несбалансирован, есть 4 случая
    
    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return avl_rotate_right(node);
    }
    
    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return avl_rotate_left(node);
    }
    
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = avl_rotate_left(node->left);
        return avl_rotate_right(node);
    }
    
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = avl_rotate_right(node->right);
        return avl_rotate_left(node);
    }
    
    return node;
}

AVLNode* avl_delete(AVLNode* root, int key) {
    if (root == NULL) return root;
    
    if (key < root->key) {
        root->left = avl_delete(root->left, key);
    } else if (key > root->key) {
        root->right = avl_delete(root->right, key);
    } else {
        // Узел найден
        
        if (root->left == NULL || root->right == NULL) {
            AVLNode* temp = root->left ? root->left : root->right;
            
            // Нет детей
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // Один ребёнок
                *root = *temp;
            }
            free(temp);
        } else {
            // Два ребёнка
            AVLNode* temp = avl_find_min(root->right);
            root->key = temp->key;
            root->right = avl_delete(root->right, temp->key);
        }
    }
    
    if (root == NULL) return root;
    
    // Обновляем высоту
    root->height = maxim(avl_height(root->left), avl_height(root->right)) + 1;
    
    // Проверяем баланс
    int balance = avl_balance_factor(root);
    
    // Балансировка
    if (balance > 1 && avl_balance_factor(root->left) >= 0) {
        return avl_rotate_right(root);
    }
    
    if (balance > 1 && avl_balance_factor(root->left) < 0) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }
    
    if (balance < -1 && avl_balance_factor(root->right) <= 0) {
        return avl_rotate_left(root);
    }
    
    if (balance < -1 && avl_balance_factor(root->right) > 0) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }
    
    return root;
}
