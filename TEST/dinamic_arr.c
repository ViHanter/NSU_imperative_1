#include <stdio.h>
#include <stdlib.h>

typedef int value_type;
typedef struct vector{
    value_type *arr;
    size_t size;
    size_t capacity;
} vector;

void vector_init(vector *v, size_t capacity)
{
    v->arr = (value_type *)calloc(capacity, sizeof(value_type));
    if (v->arr == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    v->size = 0;
    v->capacity = capacity;
}

size_t vector_size(vector *v)
{
    return v->size;
}
size_t vector_capacity(vector *v)
{
    return v->capacity;
}

void new_capacity (vector *v, size_t capacity){
    v->arr = (value_type*)realloc(v->arr, capacity * sizeof(value_type));
    if (v->arr == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    for (size_t i = v->capacity; i < capacity; i++) {
        v->arr[i] = 0;
    }
    v->capacity = capacity;
}
void vector_push(vector*v, value_type data) {
    if (v->size == v->capacity){
        new_capacity(v,2*v->capacity);
    }
    v->arr[v->size] = data;
    v->size++;
}
void vector_set(vector *v, int index, value_type data){
    if (index >= v->capacity){
        new_capacity(v,index+1);
        v->size = index+1;
    }
    v->arr[index] = data;
}

int vector_delete(vector *v,int index){
    if (index >= v->capacity){
        return -1;
    }

    value_type a = v->arr[index];
    for (value_type i = index; i<v->size; i++){
        v->arr[i] = v->arr[i+1];
    }
    return a;
}