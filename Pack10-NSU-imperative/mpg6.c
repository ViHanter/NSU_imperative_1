#include <stdio.h>
#include <stdlib.h>

int main(void) {
    long long k;
    scanf("%lld", &k);

    int *nums = NULL;
    int n = 0, cap = 0, v;
    while (scanf("%d", &v) == 1) {
        if (n == cap) {
            cap = cap ? cap * 2 : 8;
            nums = realloc(nums, cap * sizeof(int));
        }
        nums[n++] = v;
    }
    if (n == 0) {
        printf("0\n");
        return 0;
    }

    int **chld = (int**)malloc(n * sizeof(int*));
    int *chld_cnt = (int*)calloc(n, sizeof(int));
    int *chld_cap = (int*)calloc(n, sizeof(int));

    int *right = (int*)malloc(n * sizeof(int));
    int *stack = (int*)malloc(n * sizeof(int));
    int top = 0;

    for (int i = 0; i < n; i++) {
        right[i] = n;
        chld[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        while (top > 0 && nums[stack[top - 1]] < nums[i]) {
            right[stack[top - 1]] = i;
            top--;
        }
        if (top > 0) {
            int u = stack[top - 1];
            if (chld_cnt[u] == chld_cap[u]) {
                int new_cap = chld_cap[u] ? chld_cap[u] * 2 : 2;
                chld[u] = realloc(chld[u], new_cap * sizeof(int));
                chld_cap[u] = new_cap;
            }
            chld[u][chld_cnt[u]++] = i;
        }
        stack[top++] = i;
    }

    free(stack);

    int *deque = (int*)malloc(n * sizeof(int));
    int head = 0, tail = 0;

    long long ans = 0;
    long long sum_inc = 0;
    int l = 0;

    for (int r = 0; r < n; r++) {
        while (tail > head && nums[deque[tail - 1]] <= nums[r]) {
            tail--;
        }
        deque[tail++] = r;

        int cur_max = nums[deque[head]];
        if (cur_max > nums[r]) {
            sum_inc += (long long)(cur_max - nums[r]);
        }

        while (sum_inc > k) {
            int left_val = nums[l];
            int sz = chld_cnt[l];
            int *list = chld[l];

            for (int idx = 0; idx < sz; idx++) {
                int i = list[idx];
                if (i > r) break;

                long long diff = (long long)left_val - nums[i];
                if (diff <= 0) continue;

                int rb = right[i];
                if (rb > r + 1) rb = r + 1;
                long long len = (long long)(rb - i);
                if (len > 0) {
                    sum_inc -= diff * len;
                }
            }

            l++;
            while (tail > head && deque[head] < l) {
                head++;
            }
        }

        ans += (long long)(r - l + 1);
    }

    printf("%lld\n", ans);

    free(nums);
    free(right);
    for (int i = 0; i < n; i++) {
        if (chld[i]) free(chld[i]);
    }
    free(chld);
    free(chld_cnt);
    free(chld_cap);
    free(deque);

    return 0;
}