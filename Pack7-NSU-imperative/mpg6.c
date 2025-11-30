#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Node
{
struct Node *prev, *next;
double value;
} Node;
// создаёт пустой список
// возвращает указатель на value в голове списка (вспом. узел)
double *initList();
// полностью освобождает память списка
// принимает указатель на value голове списка (вспом. узел)
void freeList(double *head);
// определяет следующий элемент после заданного
//(для вспом. узла возвращает первый элемент)
double *getNext(double *curr);
// определяет предыдущий элемент перед заданным
//(для вспом. узла возвращает последний элемент)
double *getPrev(double *curr);
// создаёт и вставляет узел со значением newval сразу после узла where
double *addAfter(double *where, double newval);
// создаёт и вставляет узел со значением newval сразу перед узлом where
double *addBefore(double *where, double newval);
// удаляет и освобождает заданный узел
void erase(double *what);

void print_list(double *head);
double* getNodebyIDX(double *head, int idx);

Node* getHeadNode(double *head_value) {
    return (Node*)((char*)head_value - offsetof(Node, value));
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T;
    scanf("%d",&T);
    while(T){
        int Q;
        scanf("%d",&Q);

        double *head = initList();

        Node *head_node = getHeadNode(head);
        double **nodes = (double**)malloc(sizeof(double*) * (Q + 2));
        int node_count = 0;
        nodes[0] = head;

        for (int i=0;i<Q;i++){
            int type,idx;
            double value;

            scanf("%d %d",&type,&idx);
            
            double *target = nodes[idx + 1];
            switch (type)
            {
            case 1:
                scanf("%lf",&value);
                nodes[++node_count] = addAfter(target, value);
                break;
            case -1:
                scanf("%lf",&value);
                nodes[++node_count] = addBefore(target, value);
                break;
            case 0:
                Node *target_node = getHeadNode(target);
                printf("%0.3lf\n", target_node->value);
                erase(target);
                nodes[idx + 1] = NULL;
                break;
            }
        }
        print_list(head);
        freeList(head);
        T--;
    }

    return 0;
}

double *initList(){
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->prev = new_node;
    new_node->next = new_node;
    return &(new_node->value);
}
void freeList(double *head){
    Node *head_node = (Node*)((char*)head - offsetof(Node,value));
    Node *curr = head_node->next;

    while (curr != head_node) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(head_node);
}
double *getNext(double *curr){

    Node *current_node = (Node*)((char*)curr - offsetof(Node, value));
    Node *next_node = current_node->next;
    
    if (next_node->next == next_node->prev)
        return &(next_node->next->value);
    
    return &(next_node->value);
}
double *getPrev(double *curr){
    Node *current_node = (Node*)((char*)curr - offsetof(Node, value));
    Node *prev_node = current_node->prev;
    
    if (prev_node->next == prev_node->prev) {
        return &(prev_node->prev->value);
    }
    
    return &(prev_node->value);
}
double *addAfter(double *where, double newval){
    Node *where_node = (Node*)((char*)where - offsetof(Node,value));
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->value = newval;
    new_node->prev = where_node;
    new_node->next = where_node->next;

    where_node->next->prev = new_node;
    where_node->next = new_node;

    return &(new_node->value);
}
double *addBefore(double *where, double newval){
    Node *where_node = (Node*)((char*)where - offsetof(Node,value));
    Node *new_node = (Node*)malloc(sizeof(Node));

    new_node->value = newval;
    new_node->next = where_node;
    new_node->prev = where_node->prev;

    where_node->prev->next = new_node;
    where_node->prev = new_node;

    return &(new_node->value);
}
void erase(double *what){
    Node *what_node = (Node*)((char*)what - offsetof(Node,value));
    
    if (what_node->next == what_node && what_node->prev == what_node) {
        return;
    }

    what_node->prev->next = what_node->next;
    what_node->next->prev = what_node->prev;

    free(what_node);
}
void print_list(double *head){
    Node *head_node = (Node*)((char*)head - offsetof(Node,value));
    Node *curr = head_node->next;

    printf("===\n");
    while (curr != head_node) {
        printf("%0.3lf\n",curr->value);
        curr = curr->next;
    }
    printf("===\n");
};
double* getNodebyIDX(double *head, int idx){
    if (idx == -1) return head;

    Node *head_node = (Node*)((char*)head - offsetof(Node,value));
    Node *curr = head_node->next;
    
    for (int i = 0; i < idx && curr != head_node; i++) {
        curr = curr->next;
    }
    return &(curr->value);
}