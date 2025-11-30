#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x<y) return -1;
    if (x>y) return 1;
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d",&N);
    long long *buff = (long long*)malloc(sizeof(long long)*N);

    for (int i=0;i<N;i++){
        long long num;
        scanf("%lld",&num);
        buff[i] = num;
    }
    qsort(buff,N,sizeof(long long),compare);

    int unique_count = 0;
    if (N > 0) {
        unique_count = 1;
        for (int i = 1; i < N; i++) {
            if (buff[i] != buff[i - 1]) {
                unique_count++;
            }
        }
    }

    printf("%d\n",unique_count);
    if (N > 0) {
        printf("%lld\n", buff[0]);
        for (int i = 1; i < N; i++) {
            if (buff[i] != buff[i - 1]) {
                printf("%lld\n",buff[i]);
            }
        }
    }


    return 0;
}