#include <stdio.h>
#include <string.h>

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char day[20];
    scanf("%s",day);
    if (strcmp(day,"M")==0 || strcmp(day,"Mo")==0 || strcmp(day,"Mon")==0 || strcmp(day,"Mond")==0 || strcmp(day,"Monda")==0 || strcmp(day,"Monday")==0){
        printf("1"); // перебор всех вариантов для понедельника (strcmp сравнивает 2 слова посимвольно, те разница символов)
    } else if (strcmp(day,"Tu")==0 || strcmp(day,"Tue")==0 || strcmp(day,"Tues")==0 || strcmp(day,"Tuesd")==0 || strcmp(day,"Tuesda")==0 || strcmp(day,"Tuesday")==0){
        printf("2"); // перебор всех вариантов для вторника, кроме случая с T
    } else if (strcmp(day,"W")==0 || strcmp(day,"We")==0 || strcmp(day,"Wed")==0 || strcmp(day,"Wedn")==0 || strcmp(day,"Wedne")==0 || strcmp(day,"Wednes")==0 || strcmp(day,"Wednesd")==0 || strcmp(day,"Wednesda")==0 || strcmp(day,"Wednesday")==0){
        printf("3"); // для среды
    } else if (strcmp(day,"Th")==0 || strcmp(day,"Thu")==0 || strcmp(day,"Thur")==0 || strcmp(day,"Thurs")==0 || strcmp(day,"Thursd")==0 || strcmp(day,"Thursda")==0 || strcmp(day,"Thursday")==0){
        printf("4"); // для четверга, кроме T
    } else if (strcmp(day,"F")==0 || strcmp(day,"Fr")==0 || strcmp(day,"Fri")==0 || strcmp(day,"Frid")==0 || strcmp(day,"Frida")==0 || strcmp(day,"Friday")==0){
        printf("5"); // для пятницы
    } else if (strcmp(day,"Sa")==0 || strcmp(day,"Sat")==0 || strcmp(day,"Satu")==0 || strcmp(day,"Satur")==0 || strcmp(day,"Saturd")==0 || strcmp(day,"Saturda")==0 || strcmp(day,"Saturday")==0){
        printf("6"); // для субботы, кроме S
    } else if (strcmp(day,"Su")==0 || strcmp(day,"Sun")==0 || strcmp(day,"Sund")==0 || strcmp(day,"Sunda")==0 || strcmp(day,"Sunday")==0){
        printf("7"); // для воскресенья, кроме S
    } else if (strcmp(day,"S")==0 || strcmp(day,"T")==0){
        printf("Ambiguous"); // для спорных случаев с S И Т
    } else {
        printf("Invalid"); // не нашлось ничего
    }
    return 0;
}