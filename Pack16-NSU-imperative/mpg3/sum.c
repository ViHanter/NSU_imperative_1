#include <stdint.h>

int N;
static int64_t pref[100001];

void Init(const int *arr, int n)
{
    N = n;
    pref[0] = 0;

    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + arr[i];
}

int64_t Sum(int l, int r)
{
    return pref[r] - pref[l];
}