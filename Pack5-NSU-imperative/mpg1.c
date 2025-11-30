#include <stdio.h>

double get_exp(double x){
    if (x<0.0) return 1/(get_exp(x*(-1)));
    double num = 1.0;
    double res = 1.0;
    int n = 1;
    while (num>1e-15 || num<-1e-15){
        num = num*x/n++;
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
        printf("%0.15g\n",get_exp(x));
    }
    return 0;
}