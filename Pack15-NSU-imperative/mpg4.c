#include <stdio.h>

#define MAXN 305
#define MOD 1000000007LL

typedef long long ll;

ll power_mod(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// обратный элемент по модулю простого P
ll mod_inverse(ll a, ll P) {
    return power_mod(a, P - 2, P);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    ll P;

    scanf("%d %d %lld", &n, &k, &P);

    ll a[MAXN][MAXN];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%lld", &a[i][j]);
            a[i][j] %= P;
        }
    }

    int row = 0;
    int pivot_col[MAXN];
    for (int i = 0; i < n; i++)
        pivot_col[i] = -1;

    // Прямой ход Гаусса
    for (int col = 0; col < n && row < k; col++) {
        int sel = -1;

        for (int i = row; i < k; i++) {
            if (a[i][col] != 0) {
                sel = i;
                break;
            }
        }

        if (sel == -1)
            continue;

        // меняем строки
        for (int j = col; j <= n; j++) {
            ll tmp = a[row][j];
            a[row][j] = a[sel][j];
            a[sel][j] = tmp;
        }

        // нормализуем ведущий элемент
        ll inv = mod_inverse(a[row][col], P);
        for (int j = col; j <= n; j++)
            a[row][j] = (a[row][j] * inv) % P;

        // зануляем столбец
        for (int i = 0; i < k; i++) {
            if (i != row && a[i][col] != 0) {
                ll factor = a[i][col];
                for (int j = col; j <= n; j++) {
                    a[i][j] = (a[i][j] - factor * a[row][j] % P + P) % P;
                }
            }
        }

        pivot_col[row] = col;
        row++;
    }

    int rank = row;

    // проверка на несовместность
    for (int i = rank; i < k; i++) {
        if (a[i][n] != 0) {
            printf("0\n");
            return 0;
        }
    }

    if (rank == n) {
        printf("1\n");
        // единственное решение
        ll ans[MAXN] = {0};

        for (int i = 0; i < rank; i++) {
            ans[pivot_col[i]] = a[i][n];
        }

        for (int i = 0; i < n; i++)
            printf("%lld\n", ans[i]);
    } else {
        // бесконечно много решений
        ll result = power_mod(P, n - rank, MOD);
        printf("%lld\n", result);
    }

    return 0;
}