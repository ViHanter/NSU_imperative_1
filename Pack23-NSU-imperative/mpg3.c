#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int nums[50005];

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    long long total_sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        total_sum += nums[i];
    }

    if (total_sum % 2 != 0) {
        printf("false\n");
        return 0;
    }

    int target = total_sum / 2;

    bool *dp = (bool *)calloc(target + 1, sizeof(bool));
    dp[0] = true;
    for (int i = 0; i < n; i++) {
        int val = nums[i];
        for (int j = target; j >= val; j--) {
            if (dp[j - val]) {
                dp[j] = true;
            }
        }
        if (dp[target]) {
            break;
        }
    }

    if (dp[target]) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    free(dp);
    return 0;
}
