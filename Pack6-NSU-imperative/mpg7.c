#include <stdio.h>
#include <stdint.h>

int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    long long nums[10000];
    long long num;
    int n, cnt=0;
    scanf("%d",&n);
    //fread(&n,sizeof(uint32_t),1,input);
    for (int i=0;i<n;i++) {
        scanf("%llx",&num);
        nums[i] = num;
    }
    for (int i=0;i<n;i++){
        for (int j=i+1;j<n;j++){
            if ((nums[i] & nums[j])==0) cnt++;
        }
    }
    printf("%d",cnt);
    return 0;
}