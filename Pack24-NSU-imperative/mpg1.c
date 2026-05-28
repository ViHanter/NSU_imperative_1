#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    if (scanf("%d", &n) != 1) return 0;

    int cand = 0;
    int cnt = 0;
    int current;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &current) != 1) break;
        if (cnt == 0) {
            cand = current;
            cnt = 1;
        } else if (current == cand) {
            cnt++;
        } else {
            cnt--;
        }
    }

    if (n <= 0) {
        printf("NO\n");
        return 0;
    }
    freopen("input.txt", "r", stdin);
    scanf("%d", &n); 

    int actual_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &current) != 1) break;
        if (current == cand) {
            actual_cnt++;
        }
    }

    if (actual_cnt > n / 2) {
        printf("YES\n%d\n", cand); 
    } else {
        printf("NO\n");
    }

    return 0;
}