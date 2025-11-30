#include <stdio.h>
int getlim(int month,int year) { // функция, находившая лимит дней в месяце
    int lim = 0;
    if (month==2){
        if (year%400==0 || (year%4==0 && year%100!=0)) {
            lim=29;
        } else lim=28;
    } else if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
        lim=31;
    } else lim=30;

    return lim;
}
int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int day,month,year,newdays; // day - день, month - месяц, year - год, newdays - кол-во доб. дней
    scanf("%d %d %d %d",&day,&month,&year,&newdays); // считывание данных
    int lim = getlim(month,year); // поиск кол-ва дней в месяце
    
    while (newdays>0) { // цикл, пока кол-во дней не закончится
        day++;
        newdays--;
        if (day>lim) { // блок обновления месяца, при переполнении дней
            month++;
            if (month>12) { // блок обновления месяца, при переполнении месяцев
                year++; 
                month=1;
            }
            lim = getlim(month,year); // обновление предела дней
            day=1;
        }
    }
    printf("%d %d %d",day,month,year); // вывод результата
    return 0;
}