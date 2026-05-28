#include <stdio.h>

#define MOD 1000000007
#define MAX_N 1000000

long long fact[MAX_N + 1];
long long invFact[MAX_N + 1];

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

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    invFact[MAX_N] = mod_pow(fact[MAX_N], MOD - 2, MOD);
    for (int i = MAX_N - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

long long binomial(int N, int K) {
    if (K < 0 || K > N) return 0;
    return (fact[N] * invFact[K] % MOD) * invFact[N - K] % MOD; // Cnk = N! / (K! * (N-K)!)
}

int main() {
    precompute();

    int T;
    scanf("%d", &T);
    while (T--) {
        int N, K;
        scanf("%d %d", &N, &K);
        printf("%lld\n", binomial(N, K));
    }

    return 0;
}