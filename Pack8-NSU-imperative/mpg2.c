#include <stdio.h>
#include <stdlib.h>

int binary_search(int *,int,int);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N,n,num;
    scanf("%d",&N);
    int *buff = (int*)malloc(N * sizeof(int));
    for (int i=0;i<N;i++) {scanf("%d",&buff[i]);}
    
    scanf("%d",&n);
    scanf("%d",&num);
    int A = binary_search(buff,N,num);
    printf("%d\n",A);
    for (int i=1;i<n;i++) {
        scanf("%d",&num);
        int res = binary_search(buff,N,num+A);
        printf("%d\n",res);
        A = res;
    }

    return 0;
}

int binary_search(int *arr,int len,int target){
    int l = 0;
    int r = len-1;
    int i = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (arr[m] == target) {
            i = m;
            break;
        } else if (arr[m] < target) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (i == -1) return -1;

    while (i<len && arr[i]==target) i++;
    return i-1;
}