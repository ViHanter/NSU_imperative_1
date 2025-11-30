#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LongNum_s 
{ 
    int len;      // сколько цифр в числе 
    int arr[3000]; // массив десятичных цифр числа 
} LongNum;

void convert_toLong(LongNum *num, const char *str);
void print_long(LongNum res);
void long_mul(LongNum *result, LongNum *num1, LongNum *num2);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char str1[1001], str2[1001];
    scanf("%s", str1);
    scanf("%s", str2);

    LongNum Lnum1;
    LongNum Lnum2;

    LongNum res;
    convert_toLong(&Lnum1,str1);
    convert_toLong(&Lnum2,str2);

    long_mul(&res,&Lnum1,&Lnum2);
    print_long(res);
    return 0;
}
void print_long(LongNum res){
    for (int i = res.len - 1; i >= 0; i--) printf("%d",res.arr[i]);
}
void long_mul(LongNum *result, LongNum *num1, LongNum *num2){
    int ost = 0;

    LongNum temp = {0};
    for (int i = 0; i < 3000; i++) {
        temp.arr[i] = 0;
    }
    LongNum *a;
    LongNum *b;
    if (num1->len>num2->len) {a = num1; b = num2;}
    else {a = num2; b = num1;}
    for (int i=0;i<b->len;i++){
        int ost = 0;
        for (int j = 0; j < a->len; j++){

            int product = a->arr[j] * b->arr[i] + ost;
            int total = product + temp.arr[i + j];

            temp.arr[i + j] = total % 10;
            ost = total / 10;
        }
        int pos = i + a->len;
        while (ost > 0) {
            int total = temp.arr[pos] + ost;
            temp.arr[pos] = total % 10;
            ost = total / 10;
            pos++;
        }
    }
    
    temp.len = 2999;
    while (temp.len > 0 && temp.arr[temp.len] == 0) {
    temp.len--;
    }
    temp.len++;
    
    result->len = temp.len;
    for (int i=0;i<result->len;i++) result->arr[i]= temp.arr[i];
}
void convert_toLong(LongNum *num, const char *str){
    int len = strlen(str);
    num->len = len;
    
    // Записываем цифры в обратном порядке
    for (int i = 0; i < len; i++) {
        num->arr[len - 1 - i] = str[i] - '0';
    }
    
    // Обнуляем оставшиеся позиции
    for (int i = len; i < 3000; i++) {
        num->arr[i] = 0;
    }
}