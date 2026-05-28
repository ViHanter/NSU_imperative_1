#include <stdint.h>

extern int N;
int64_t Sum(int l, int r);

int Query(int l, int64_t sum)
{
    int left = l;
    int right = N;

    while (left < right)
    {
        int mid = (left + right + 1) / 2;

        if (Sum(l, mid) <= sum)
            left = mid;
        else
            right = mid - 1;
    }

    return left;
}