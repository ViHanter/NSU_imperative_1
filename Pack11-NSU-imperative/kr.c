#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack{
    int size;
    int top;
    int *data;
} Stack;

void init(Stack *arr){
    arr->data = (int*)malloc(sizeof(int));
    arr->size = 1;
    arr->top = 0;
}

void push(Stack *arr, int data){
    if (arr->top >= arr->size){
        arr->size *=2;
        arr->data = (int*)realloc(arr->data, arr->size * sizeof(int));
    }

    arr->data[arr->top] = data;
    arr->top++;
}

void push_arr(Stack *arr, int *data){
    while ((arr->size - arr->top) < strlen(data)){
        arr->size *=2;
        arr->data = (int*)realloc(arr->data, arr->size * sizeof(int));
    }

    for (int i=arr->top;i<arr->top + strlen(data);i++){
        arr->data[i] = data[i - arr->top];
    }
}

int pop(Stack *arr){
    if (arr->top>0) {
        int temp = arr->data[arr->top-1];
        arr->data[arr->top-1] = NULL;
        arr->top--;
        printf("%d",temp);
        return temp;
    }
}

int peek(Stack *arr){
    if (arr->top>0) {
        int temp = arr->data[arr->top-1];
        printf("%d",temp);
        return temp;
    }
}

void swap(Stack *arr, int idx1, int idx2){
    int temp = arr->data[idx1];
    arr->data[idx1] = arr->data[idx2];
    arr->data[idx2] = temp;
}

void reverse(Stack *arr){
    for (int i=0;i<arr->top/2;i++){
        swap(arr,i,arr->top-i);
    }
}

int is_empty(Stack *arr){
    if (arr->top == 0) return 1;
    return 0;
}
int is_full(Stack *arr){
    if (arr->top == arr->size) return 1;
    return 0;
}