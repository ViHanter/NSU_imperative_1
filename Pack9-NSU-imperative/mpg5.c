#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
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
    
    qsort(arr, N, sizeof(int), compare);
    
    fwrite(arr, sizeof(int), N, stdout);
    
    free(arr);
    return 0;
}