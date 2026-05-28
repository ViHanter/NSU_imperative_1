#include <stdio.h>
#include <stdlib.h>

// ==================== БИНАРНОЕ ДЕРЕВО ПОИСКА (BST) ====================

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct {
    BSTNode* root;
} BSTree;

// Создание нового узла BST
BSTNode* bst_create_node(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Вставка в BST (рекурсивно)
BSTNode* bst_insert(BSTNode* root, int key) {
    if (root == NULL) {
        return bst_create_node(key);
    }
    
    if (key < root->key) {
        root->left = bst_insert(root->left, key);
    } else if (key > root->key) {
        root->right = bst_insert(root->right, key);
    }
    // Если ключ уже существует, ничего не делаем
    
    return root;
}

// Поиск в BST (рекурсивно)
BSTNode* bst_search(BSTNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    
    if (key < root->key) {
        return bst_search(root->left, key);
    } else {
        return bst_search(root->right, key);
    }
}

// Нахождение минимального узла
BSTNode* bst_find_min(BSTNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Удаление узла из BST
BSTNode* bst_delete(BSTNode* root, int key) {
    if (root == NULL) return root;
    
    if (key < root->key) {
        root->left = bst_delete(root->left, key);
    } else if (key > root->key) {
        root->right = bst_delete(root->right, key);
    } else {
        // Узел найден
        
        // Узел с одним или нулём детей
        if (root->left == NULL) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Узел с двумя детьми: находим минимальный в правом поддереве
        BSTNode* temp = bst_find_min(root->right);
        
        // Копируем значение минимального узла
        root->key = temp->key;
        
        // Удаляем минимальный узел
        root->right = bst_delete(root->right, temp->key);
    }
    return root;
}

// Обходы дерева
void bst_inorder(BSTNode* root) {
    if (root != NULL) {
        bst_inorder(root->left);
        printf("%d ", root->key);
        bst_inorder(root->right);
    }
}

void bst_preorder(BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        bst_preorder(root->left);
        bst_preorder(root->right);
    }
}

void bst_postorder(BSTNode* root) {
    if (root != NULL) {
        bst_postorder(root->left);
        bst_postorder(root->right);
        printf("%d ", root->key);
    }
}

// Высота дерева
int bst_height(BSTNode* root) {
    if (root == NULL) return -1;
    
    int left_height = bst_height(root->left);
    int right_height = bst_height(root->right);
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Освобождение памяти
void bst_free(BSTNode* root) {
    if (root != NULL) {
        bst_free(root->left);
        bst_free(root->right);
        free(root);
    }
}