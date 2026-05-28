#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int capacity;
    int *data;
    int size;
} Stack;

void init(Stack *arr){
    arr->data = (int*)malloc(sizeof(int));
    arr->size = 0;
    arr->capacity = 1;
}

void push(Stack *arr, int data) {
    if (arr->size == arr->capacity){
        arr->capacity *=2;
        arr->data = (int*)realloc(arr->data,arr->capacity * sizeof(int));
    }
    arr->data[arr->size] = data;
    arr->size++;
}

void pop(Stack *arr){
    if (arr->size>0){
        printf("%d",arr->data[arr->size-1]);
        arr->data[arr->size-1] = NULL;
        arr->size--;
    }
}

int peek(Stack *arr){
    printf("%d",arr->data[arr->size-1]);
    return arr->data[arr->size-1];
}

void free_list(Stack *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->capacity = arr->size = 0;
}