#include <stdio.h>
#include <stdint.h>

void Init(const int *arr, int n);
int Query(int l, int64_t sum);

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int N, M;
    scanf("%d %d", &N, &M);

    int A[100000];

    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    Init(A, N);

    for (int i = 0; i < M; i++)
    {
        int L;
        int64_t S;

        scanf("%d %lld", &L, &S);

        printf("%d\n", Query(L, S));
    }

    return 0;
}