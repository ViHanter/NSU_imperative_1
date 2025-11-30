#include <stdio.h>

int josephus(int n, int k) {
    int survivor = 0;
    
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + k) % i;
    }
    
    return survivor + 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, k;
    scanf("%d %d", &n, &k);
    
    printf("%d\n", josephus(n, k));
    
    return 0;
}