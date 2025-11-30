#include <stdio.h>

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N; // кол-во чисел
    int num; // ячейка для числа
    int minix,manix; // переменные для миникса (минимальное число) и маникса (максимальное)

    int id1=1,id2=1; // индексы чисел в последовательности

    scanf("%d",&N);
    scanf("%d",&minix); // заполнение мин и макс числа
    manix = minix;

    for (int i=1; i<=N;i++) {
        scanf("%d",&num);
        if (num<minix) {
            minix = num; // если нашлось число меньше мин. -> обновляю
            id1 = i+1;
        }
        if (num>manix) {
            manix = num; // если нашлось число больше макс. -> обновляю
            id2 = i+1;
        }
    }
    printf("%d %d %d %d",minix,id1,manix,id2); // вывод результата

    return 0;
}