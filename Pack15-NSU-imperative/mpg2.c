#include <stdio.h>
#include <math.h>

#define MAXN 200
#define EPS 1e-10

void gauss(int n, double a[MAXN][MAXN + 1], double x[MAXN]) {
    int i, j, k;
    double factor;

    for (i = 0; i < n; i++) {
        int max_row = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(a[k][i]) > fabs(a[max_row][i])) {
                max_row = k;
            }
        }

        if (max_row != i) {
            for (j = i; j <= n; j++) {
                double temp = a[i][j];
                a[i][j] = a[max_row][j];
                a[max_row][j] = temp;
            }
        }

        if (fabs(a[i][i]) < EPS) {
            continue;
        }

        for (j = n; j >= i; j--) {
            a[i][j] /= a[i][i];
        }

        for (k = i + 1; k < n; k++) {
            factor = a[k][i];
            for (j = i; j <= n; j++) {
                a[k][j] -= factor * a[i][j];
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, i, j;
    double a[MAXN][MAXN + 1];
    double x[MAXN];

    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    gauss(n, a, x);

    for (i = 0; i < n; i++) {
        printf("%.10lf\n", x[i]);
    }

    return 0;
}