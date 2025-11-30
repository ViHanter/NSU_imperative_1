#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 1000000
#define MAX_STRING_LENGTH 8

typedef struct {
    char** data;
    int size;
    int capacity;
} DynamicArray;


void pushBack(DynamicArray* arr, const char* value) {
    if (arr->capacity == 0) {
        arr->capacity = 4;
        arr->data = (char**)malloc(arr->capacity * sizeof(char*));
    }
    
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));
    }
    
    arr->data[arr->size] = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
    strcpy(arr->data[arr->size], value);
    arr->size++;
}

void freeArray(DynamicArray* arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    DynamicArray* buckets = (DynamicArray*)calloc(MAX_KEY + 1, sizeof(DynamicArray));
    
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int key;
        char value[MAX_STRING_LENGTH];
        scanf("%d %s", &key, value);
        
        pushBack(&buckets[key], value);
    }
    
    for (int key = 0; key <= MAX_KEY; key++) {
        DynamicArray* arr = &buckets[key];
        for (int i = 0; i < arr->size; i++) {
            printf("%d %s\n", key, arr->data[i]);
        }
    }
    
    for (int i = 0; i <= MAX_KEY; i++) {
        if (buckets[i].size > 0) {
            freeArray(&buckets[i]);
        }
    }
    free(buckets);
    
    return 0;
}