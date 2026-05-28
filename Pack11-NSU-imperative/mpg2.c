#include <stdio.h>
#include <stdlib.h>

typedef void (*callback)(void *ctx, int *value);

void arrayForeach(void *ctx, callback func, int *arr, int n) {
    for (int i = 0; i < n; i++) {
        func(ctx, &arr[i]);
    }
}

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void listForeach(void *ctx, callback func, Node *head) {
    Node *current = head;
    while (current != NULL) {
        func(ctx, &current->data);
        current = current->next;
    }
}

void sumEvenCallback(void *ctx, int *value) {
    int *sum = (int *)ctx;
    if (*value % 2 == 0) {
        *sum += *value;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));
    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }


    Node *head = NULL;
    Node *tail = NULL;

    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);

        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = arr[i];
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }


    int sumArray = 0;
    int sumList = 0;

    arrayForeach(&sumArray, sumEvenCallback, arr, N);
    listForeach(&sumList, sumEvenCallback, head);

    printf("%d %d\n", sumArray, sumList);

    free(arr);
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}