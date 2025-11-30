#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    scanf("%d", &n);
    
    long long *buff = (long long*)malloc(n * sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &buff[i]);
    }
    
    qsort(buff, n, sizeof(long long), compare);
    
    long long total_sum = 0;
    
    for (int i = 0; i < n - 1; i++) {
        total_sum += buff[i] * (n - i - 1);
    }
    
    printf("%lld\n", total_sum);
    
    free(buff);
    return 0;
}