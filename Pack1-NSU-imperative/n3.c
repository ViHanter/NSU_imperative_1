#include <stdio.h>
#include <math.h>

int count9(int num) { // функция для подсчета девяток
    int counter = 0;

    while (num!=0) {
        if (num%10==9) counter++; // остаток деления на 10
        num = floor(num/10); // деление нацело на 10
    }
    return counter; 
}
int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N; // кол-во ценников
    int num; // ячейка для ввода цены
    int res = 0; // ячейка для результата
    int pred_res; // ячейка для предрезультата (цена до изменения)

    scanf("%d",&N);

    for (int i = 0; i<N; i++) {
        scanf("%d",&num);
        pred_res = count9(num); // нахождение кол-ва девяток до изменения
        res += (count9(num-1) + 2) - pred_res; // подсчет девяток ПОСЛЕ
    }

    printf("%d",res);
    return 0;
}