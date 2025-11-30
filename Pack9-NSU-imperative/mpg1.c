#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_BUCKETS 100000

struct Node{
    char string[8];
    int key;
    struct Node *next;
};

void addNode(const char *,struct Node *,int key);
void print_list(struct Node *);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N;
    scanf("%d",&N);
    struct Node *buckets[NUM_BUCKETS] = {NULL};

    

    for (int i=0; i<N; i++){
        int key;
        char word[8];

        scanf("%d %s",&key, word);

        int bucket_index = key % NUM_BUCKETS;
        
        if (buckets[bucket_index] == NULL) {
            buckets[bucket_index] = malloc(sizeof(struct Node));

            strcpy(buckets[bucket_index]->string, word);
            buckets[bucket_index]->next = NULL;
            buckets[bucket_index]->key = key;
        } else {
            addNode(word, buckets[bucket_index],key);
        }
    }

    for (int i=0; i<NUM_BUCKETS; i++){
        if (buckets[i] != NULL){
            print_list(buckets[i]);
        }
    }

    return 0;
}

void print_list(struct Node *head){
    struct Node *curr = head;

    while (curr->next != NULL){
        printf("%d %s\n",curr->key,curr->string);
        curr = curr->next;
    }
    printf("%d %s\n",curr->key,curr->string);
}

void addNode(const char *word, struct Node *head,int key){
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    
    strcpy(new_node->string,word);
    new_node->next = NULL;
    new_node->key = key;
    
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}