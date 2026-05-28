#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    int32_t key;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(int32_t key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, int32_t key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        root->count++;
    }
    return root;
}

void inorder_write(Node* root, FILE* out) {
    if (root == NULL) return;
    inorder_write(root->left, out);
    for (int i = 0; i < root->count; i++) {
        fwrite(&(root->key), sizeof(int32_t), 1, out);
    }
    inorder_write(root->right, out);
}

void free_tree(Node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);

    int32_t n;
    fread(&n, sizeof(int32_t), 1, stdin);

    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int32_t num;
        fread(&num, sizeof(int32_t), 1, stdin);
        root = insert(root, num);
    }

    inorder_write(root, stdout);

    free_tree(root);
    fclose(stdin);
    fclose(stdout);
    return 0;
}