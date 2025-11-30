#include <string.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n;
    int P,Q;
    uint64_t m;
    long long M;
    double res;

    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d/%d xor %llx",&P,&Q,&M);

        double X = (double)P / (double)Q;
        memcpy(&m,&X,sizeof(double));
        m^=M;
        memcpy(&res,&m,sizeof(double));
        printf("%0.15g\n",res);
    }

    return 0;
}