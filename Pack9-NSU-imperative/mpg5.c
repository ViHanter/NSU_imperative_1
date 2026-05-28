#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {

        int pi = partition(arr, low, high);
        
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}


int main() {
    freopen("input.txt", "rb", stdin);
    freopen("output.txt", "wb", stdout);
    
    int N;
    
    fread(&N, sizeof(int), 1, stdin);
    if (N == 0) {
        return 0;
    }
    
    int* arr = (int*)malloc(N * sizeof(int));
    
    fread(arr, sizeof(int), N, stdin);
    
    quick_sort(arr,0,N-1);
    
    fwrite(arr, sizeof(int), N, stdout);
    
    free(arr);
    return 0;
}