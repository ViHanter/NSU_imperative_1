#include <stdio.h>

double get_sin(double x){
    double num = x;
    double res = x;
    int n = 1;
    while (n<100){
        n+=2;
        num= -num*x*x / ( (n-1)*n);
        res+=num;
        // n++;
    }
    return res;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n;
    scanf("%d",&n);

    double x;
    for (int i=0;i<n;i++){
        scanf("%lf",&x);
        printf("%0.15f\n",get_sin(x));
    }
    return 0;
}