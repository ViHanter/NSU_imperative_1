#include <stdio.h>


int main() {
    int counter = 0; // подсчет кол-ва делителей
    int fl = 0; // флаг
    int num; // ячейка для числа

    scanf("%d",&num);
    if (num == 2) {
        printf("YES"); // проверка если число 2
        return 0;
    }
    
    for (int i = 2; i < num; i++){ // цикл до числа num, подсчет делителей
        fl = 1; 
        if (num%i==0) counter++;
    }
    
    if (counter == 0 && fl == 1) printf("YES"); // вывод результата
    else printf("NO");

    return 0;
}
