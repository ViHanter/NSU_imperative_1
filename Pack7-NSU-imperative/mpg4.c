#include <stdio.h>
#include <string.h>

#define MAX_NODES 200010

struct Node{
    int data;
    int prev;
    int next;
};

struct Node nodes[MAX_NODES];

int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int T;
    scanf("%d",&T);
    while(T){
        int N,F,L,Q;
        scanf("%d %d %d %d",&N,&F,&L,&Q);
        for (int i=0;i<N;i++){
            scanf("%d %d %d",&nodes[i].data,&nodes[i].next,&nodes[i].prev);
        }

        int head = F;
        int tail = L;
        int next_idx = N;

        for (int i=0; i<Q;i++){
            int operation,idx;
            scanf("%d %d",&operation,&idx);
            
            if (operation != 0) {
                int new_value;
                
                int new_node = next_idx++;
                printf("%d\n",new_node);
                
                scanf("%d",&new_value);
                nodes[new_node].data = new_value;
                
                if (operation == -1){ // Добавление сзади (перед idx)
                    if (idx == -1){ // Вставка в конец
                        nodes[new_node].prev = tail;
                        nodes[new_node].next = -1;
                        if (tail != -1) {
                            nodes[tail].next = new_node;
                        }
                        tail = new_node;
                        if (head == -1) { // Если список был пустой
                            head = new_node;
                        }
                    } else { // Вставка перед idx
                        nodes[new_node].prev = nodes[idx].prev;
                        nodes[new_node].next = idx;
                        nodes[idx].prev = new_node;
                        
                        if (nodes[new_node].prev != -1){
                            nodes[nodes[new_node].prev].next = new_node;
                        } else {
                            head = new_node;
                        }
                    }
                } else { // operation == 1 - Добавление спереди (после idx)
                    if (idx == -1){ // Вставка в начало
                        nodes[new_node].prev = -1;
                        nodes[new_node].next = head;
                        if (head != -1) {
                            nodes[head].prev = new_node;
                        }
                        head = new_node;
                        if (tail == -1) { // Если список был пустой
                            tail = new_node;
                        }
                    } else { // Вставка после idx
                        nodes[new_node].prev = idx;
                        nodes[new_node].next = nodes[idx].next;
                        nodes[idx].next = new_node;
                        
                        if (nodes[new_node].next != -1){
                            nodes[nodes[new_node].next].prev = new_node;
                        } else {
                            tail = new_node;
                        }
                    }
                }
                
            } else { // operation == 0 - Удаление
                printf("%d\n",nodes[idx].data);
                
                // Обновляем связи соседних узлов
                if (nodes[idx].prev != -1) {
                    nodes[nodes[idx].prev].next = nodes[idx].next;
                } else {
                    head = nodes[idx].next;
                }
                
                if (nodes[idx].next != -1) {
                    nodes[nodes[idx].next].prev = nodes[idx].prev;
                } else {
                    tail = nodes[idx].prev;
                }
            }
        }
        
        printf("===\n");
        int curr = head;
        while (curr != -1){
            printf("%d\n",nodes[curr].data);
            curr = nodes[curr].next;
        }
        printf("===\n");

        T--;
    }

    return 0;
}