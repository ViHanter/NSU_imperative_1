#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int maxim(int a, int b) {
    return a > b ? a : b;
}

int height(Node *node) {
    return node ? node->height : 0;
}

int balance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* newNode(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T = x->right;
    x->right = y;
    y->left = T;
    y->height = maxim(height(y->left), height(y->right)) + 1;
    x->height = maxim(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T = y->left;
    y->left = x;
    x->right = T;
    x->height = maxim(height(x->left), height(x->right)) + 1;
    y->height = maxim(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node *root, int key, int *found) {
    if (!root) {
        *found = 0;
        return newNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key, found);
    } else if (key > root->key) {
        root->right = insert(root->right, key, found);
    } else {
        *found = 1;
        return root;
    }

    root->height = maxim(height(root->left), height(root->right)) + 1;

    int bal = balance(root);
    if (bal > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    if (bal < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    if (bal > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bal < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* minValueNode(Node *root) {
    Node *current = root;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

Node* delete(Node *root, int key, int *found) {
    if (!root) {
        *found = 0;
        return NULL;
    }
    if (key < root->key) {
        root->left = delete(root->left, key, found);
    } else if (key > root->key) {
        root->right = delete(root->right, key, found);
    } else {
        *found = 1;
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key, found);
        }
    }
    if (!root) return NULL;

    root->height = maxim(height(root->left), height(root->right)) + 1;

    int bal = balance(root);
    if (bal > 1 && balance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (bal > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bal < -1 && balance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (bal < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* lowerBound(Node *root, int v) {
    Node *current = root;
    Node *result = NULL;
    while (current) {
        if (current->key >= v) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return result;
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    Node *root = NULL;
    char op[10];
    int v;
    int found;

    for (int i = 0; i < M; i++) {
        scanf("%s %d", op, &v);
        if (strcmp(op, "add") == 0) {
            root = insert(root, v, &found);
            printf("%s\n", found ? "dupe" : "added");
        } else if (strcmp(op, "remove") == 0) {
            root = delete(root, v, &found);
            printf("%s\n", found ? "removed" : "miss");
        } else if (strcmp(op, "lower") == 0) {
            Node *lb = lowerBound(root, v);
            if (lb) {
                printf("%d\n", lb->key);
            } else {
                printf("###\n");
            }
        }
    }

    freeTree(root);
    fclose(stdin);
    fclose(stdout);
    return 0;
}