#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N, K;
    scanf("%d %d", &N, &K);
    
    Node* head = (Node*)malloc(sizeof(Node));
    head->value = 1;
    Node* current = head;
    
    for (int i = 2; i <= N; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node)); // круговой связный список
        newNode->value = i;
        current->next = newNode;
        current = newNode;
    }
    current->next = head;
    
    current = head;
    Node* prev = current;
    
    //ставим предыдущего (последний элемент)
    while (prev->next != head) {
        prev = prev->next;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K - 1; j++) {
            prev = current;
            current = current->next;
        }
        
        //вывод
        printf("%d\n", current->value);
        
        //блок удаления выбывшего
        prev->next = current->next;
        Node* toDelete = current;
        current = current->next;
        free(toDelete);
    }
    
    return 0;
}