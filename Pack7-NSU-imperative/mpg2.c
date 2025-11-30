#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 200010

struct Node {
    char data[8];
    int next;
};

struct Node nodes[MAX_NODES];
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    

    int T;
    scanf("%d",&T);

    while(T--){
        int N,F,Q;
        scanf("%d %d %d",&N,&F,&Q);

        for (int i=0;i<N;i++){
            scanf("%s %d",nodes[i].data,&nodes[i].next);
        }

        int head = F;
        int next_idx = N;

        for (int i=0;i<Q;i++){
            int operation,idx;
            scanf("%d %d",&operation,&idx);

            if (operation == 0) {
                char new_data[8];
                int new_idx = next_idx++;

                scanf("%s",new_data);
                strcpy(nodes[new_idx].data,new_data);
                
                if (idx==-1){
                    nodes[new_idx].next = head;
                    head = new_idx;
                } else {
                    nodes[new_idx].next = nodes[idx].next;
                    nodes[idx].next = new_idx;
                }
                printf("%d\n", new_idx);
            }
            else {
                int remove_idx;
                char removed_data[8];
                if (idx == -1) {
                    remove_idx = head;
                    head = nodes[head].next;
                } else {
                    remove_idx = nodes[idx].next;
                    nodes[idx].next = nodes[remove_idx].next;
                }
                strcpy(removed_data, nodes[remove_idx].data);
                printf("%s\n", removed_data);
            }
        }
        printf("===\n");

        int curr = head;
        while (curr != -1) {
            printf("%s\n", nodes[curr].data);
            curr = nodes[curr].next;
        }
        
        printf("===\n");
    }

    return 0;
}