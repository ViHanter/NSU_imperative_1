#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 1000000
#define MAX_LENGTH 8

struct Node {
    char data[MAX_LENGTH];
    struct Node *next;  
};

struct Node* buff[MAX_KEYS + 1] = {NULL};

void push(int key, const char *_data){
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newnode->data,_data);
    newnode->next = NULL;

    if (buff[key] == NULL) {
        buff[key] = newnode;
    } else {
        struct Node* current = buff[key];
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newnode;
    }
}

int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N=0;
    scanf("%d",&N);

    for (int i=0;i<N;i++){
        int key;
        char value[8];

        scanf("%d %s",&key,value);
        push(key,value);
    }

    for (int key=0;key <= MAX_KEYS;key++){
        struct Node* current = buff[key];
        while (current!=NULL){
            printf("%d %s\n",key,current->data);
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }


    return 0;
}