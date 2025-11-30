#include <stdio.h>

int main(void) {
    int N,num; // N - кол-во чисел в последовательности, num - ячейка для ввода
    int res = 0; // пустая переменная для результата

    scanf("%d",&N);
    
    for (int i = 0; i<N; i++) {
        scanf("%d",&num);
        if (num%2!=0) res+=num; // подсчет все нечетных числе в последовательнолсти
    }

    printf("%d",res); // вывод результата

    return 0;
}