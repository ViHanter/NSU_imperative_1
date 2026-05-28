#include <stdio.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

void init_list(Node *head, int data){
    head->next = NULL;
    head->data = data;
}

int addEnd(Node *head, int data){
    if (head == NULL){
        init_list(head,data);
        return 1;
    }
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    while (head->next!=NULL) head = head->next;

    head->next = new_node;
    return 1;
}

Node *addStart(Node *head, int data){
    if (head == NULL){
        init_list(head,data);
        return head;
    }
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = head;
    return new_node;
}