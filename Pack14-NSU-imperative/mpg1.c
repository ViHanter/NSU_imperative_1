#include <stdio.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    int T;
    long long M;
    scanf("%d %lld", &T, &M);

    while (T--) {
        long long A;
        scanf("%lld", &A);

        if (A % M == 0) {
            printf("-1\n");
        } else {
            long long inverse = mod_pow(A, M - 2, M);
            printf("%lld\n", inverse);
        }
    }

    return 0;
}