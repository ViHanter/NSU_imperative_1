#include <stdio.h>

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,num,cP=0,cO=0,cN=0; // n - кол-во, num - ячейка для чисел, cP-полож., cO-отриц., cN-нули 
    double res; // ячейка для сохранения результата
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d",&num); // счет числа
        if (num<0) cP+=1; 
        else if (num>0) cO+=1; // проверка на какое оно
        else cN+=1;
    }
    // подсчет результата
    res = (cP*1.00)/n;
    printf("%.05lf ",res);
    res = (cN*1.00)/n;
    printf("%.05lf ",res);
    res = (cO*1.00)/n;
    printf("%.05lf",res);
    return 0;
}