#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    int size;
    struct Node *left;
    struct Node *right;
} Node;

const double ALPHA = 0.75;

Node* create_node(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int get_size(Node *node) {
    return node ? node->size : 0;
}

void update_size(Node *node) {
    if (node) {
        node->size = 1 + get_size(node->left) + get_size(node->right);
    }
}

bool is_unbalanced(Node *node) {
    if (!node) return false;
    int total = get_size(node);
    return get_size(node->left) > ALPHA * total || get_size(node->right) > ALPHA * total;
}

void inorder_collect(Node *node, Node **arr, int *idx) {
    if (!node) return;
    inorder_collect(node->left, arr, idx);
    arr[(*idx)++] = node;
    inorder_collect(node->right, arr, idx);
}

Node* build_balanced(Node **arr, int start, int end) {
    if (start >= end) return NULL;
    int mid = (start + end) / 2;
    Node *root = arr[mid];
    root->left = build_balanced(arr, start, mid);
    root->right = build_balanced(arr, mid + 1, end);
    update_size(root);
    return root;
}

Node* rebuild_tree(Node *root) {
    int n = get_size(root);
    Node **arr = (Node**)malloc(n * sizeof(Node*));
    int idx = 0;
    inorder_collect(root, arr, &idx);
    Node *new_root = build_balanced(arr, 0, n);
    free(arr);
    return new_root;
}

Node* insert_node(Node *root, int key, bool *found, Node **scapegoat) {
    if (!root) {
        *found = false;
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert_node(root->left, key, found, scapegoat);
    } else if (key > root->key) {
        root->right = insert_node(root->right, key, found, scapegoat);
    } else {
        *found = true;
        return root;
    }
    update_size(root);
    if (!(*scapegoat) && is_unbalanced(root)) {
        *scapegoat = root;
    }
    return root;
}

Node* insert(Node *root, int key) {
    bool found;
    Node *scapegoat = NULL;
    root = insert_node(root, key, &found, &scapegoat);
    if (scapegoat) {
        if (scapegoat == root) {
            root = rebuild_tree(scapegoat);
        } else {
            root = rebuild_tree(root);
        }
    }
    return root;
}

bool search(Node *root, int key) {
    while (root) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return true;
        }
    }
    return false;
}

void inorder_print(Node *root) {
    if (!root) return;
    inorder_print(root->left);
    printf("%d ", root->key);
    inorder_print(root->right);
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Q;
    scanf("%d", &Q);
    
    Node *root = NULL;
    char op[2];
    int x;
    
    for (int i = 0; i < Q; i++) {
        scanf("%1s", op);
        if (op[0] == '+') {
            scanf("%d", &x);
            root = insert(root, x);
        } else if (op[0] == '?') {
            scanf("%d", &x);
            if (search(root, x)) {
                printf("Found\n");
            } else {
                printf("Not found\n");
            }
        } else if (op[0] == 'p') {
            inorder_print(root);
            printf("\n");
        }
    }
    
    free_tree(root);
    fclose(stdin);
    fclose(stdout);
    return 0;
}