#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

int main() {
    int M, T;
    scanf("%d %d", &M, &T);

    //выделение памяти для треугольника Паскаля
    int** C = (int**)malloc((MAX_N + 1) * sizeof(int*));
    for (int n = 0; n <= MAX_N; n++) {
        C[n] = (int*)malloc((n + 1) * sizeof(int)); 
    } 
    //заполнение треугольника
    for (int n = 0; n <= MAX_N; n++) {
        C[n][0] = 1 % M;
        C[n][n] = 1 % M;
        for (int k = 1; k < n; k++) {
            C[n][k] = (C[n-1][k-1] + C[n-1][k]) % M;
        }
    }

    while (T--) {
        int N;
        long long K;
        scanf("%d %lld", &N, &K);

        if (K < 0 || K > N) {
            printf("0\n");
        } else {
            printf("%d\n", C[N][(int)K]);
        }
    }
    return 0;
}