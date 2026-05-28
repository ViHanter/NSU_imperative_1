#include <stdio.h>

#define MOD 1000000007
#define MAXN 1000

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    long long dp[MAXN + 1] = {0};
    dp[0] = 1;

    for (int m = 1; m <= N; m++) {
        for (int k = m; k <= N; k++) {
            dp[k] = (dp[k] + dp[k - m]) % MOD;
        }
    }

    printf("%lld\n", dp[N]);

    fclose(stdin);
    fclose(stdout);

    return 0;
}