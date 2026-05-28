#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} Queue;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Добавление элемента в конец очереди (enqueue)
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    newNode->data = value;
    newNode->next = NULL;
    
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Удаление элемента из начала очереди (dequeue)
int dequeue(Queue* q) {  
    Node* temp = q->front;
    int value = temp->data;
    
    q->front = q->front->next;
    
    // Если после удаления очередь стала пустой
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return value;
}

int peek(Queue* q) {
    return q->front->data;
}

void clearQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
}