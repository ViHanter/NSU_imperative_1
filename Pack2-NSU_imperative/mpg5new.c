#include <stdio.h>

int powic(int x,int y) { // функция нахождения квадрата числа
    int resic=1;
    for (int i=0;i<y;i++) resic*=x;
    return resic;
}

int main(void){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n,bitcount=-1,res=0; // n - кол-во символов, bitcount - счетчик битов, res - результат
    char sym; // sym - ячейка для битов

    scanf("%d\n",&n);

    for (int i=0; i<n;i++){
        scanf("%c",&sym);
        if (sym!='1' && sym!='0') { // если sym не 1 и не 0 - скипаем и откатываем счетчик
            i--;
            continue;
        }
        bitcount++;
        if (sym == '1') res+=powic(2,bitcount); // если символ - 1, то умножаем на 2 в степени

        if (bitcount >= 7) {
            printf("%d",res); // если сложился бит - вывожу 
            if (i!=n-1) printf(" "); // пробел между ответами
            res = 0;
            bitcount=-1;
        }
    }
    if (res!=0) printf("%d",res); // если есть остаток после полных битов
    return 0;
}