#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char color[7]; //массив для полного кода цвета
    char fclr[3]; // массив для первого цвета
    char sclr[3]; // массив для второго цвета
    char tclr[3]; // массив для третьего цвета

    int flag = 0; // flag
    scanf("%s",color); // считывание строки кода цвета
    const char allowed[] = "0123456789ABCDEFabcdef"; // список разрешенных символов к коде цвета
    for (int i=0;i<2;i++){ //цикл до 2, тк в каждом цвете по 2 символа
        fclr[i] = color[i]; // первый цвет
        sclr[i] = color[i+2]; // второй
        tclr[i] = color[i+4]; // третий
    }
    for (int i=0; i<strlen(color);i++){
        if (strchr(allowed,color[i])==NULL) { // проверка на то, что в коде цвета нет запрещенных символов
            flag = 1;
        }
    }
    if (flag==0 && strlen(color)==6){ 
        int r = (int)strtol(fclr,NULL,16);
        int g = (int)strtol(sclr,NULL,16); // перевод цветов из 16ричной в 10чную систему
        int b = (int)strtol(tclr,NULL,16);

        printf("%d %d %d",r,g,b); // вывод ответа
    } else printf("-1 -1 -1");
    return 0;
}