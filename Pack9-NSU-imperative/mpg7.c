#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
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
    
    heapSort(arr, N);
    
    fwrite(arr, sizeof(int), N, stdout);
    
    free(arr);
    return 0;
}