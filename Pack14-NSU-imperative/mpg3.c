#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll mul_mod(ll a, ll b, ll mod) {
    ll res = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1) res = (res + a) % mod;
        a = (a * 2) % mod;
        b >>= 1;
    }
    return res;
}

ll egcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    ll g = egcd(a, m, &x, &y);
    x = (x % m + m) % m;
    return x;
}

int main() {
    int k;
    scanf("%d", &k);
    
    ll *M = (ll*)malloc(k * sizeof(ll));
    ll *A = (ll*)malloc(k * sizeof(ll));
    
    for (int i = 0; i < k; i++) {
        scanf("%lld", &M[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%lld", &A[i]);
    }
    
    ll P = 1;
    for (int i = 0; i < k; i++) {
        P *= M[i];
    }
    
    ll X = 0;
    for (int i = 0; i < k; i++) {
        ll Pi = P / M[i];
        ll inv = mod_inv(Pi, M[i]);
        ll term = mul_mod(A[i], Pi, P);
        term = mul_mod(term, inv, P);
        X = (X + term) % P;
    }
    
    printf("%lld\n", X);
    
    free(M);
    free(A);
    return 0;
}