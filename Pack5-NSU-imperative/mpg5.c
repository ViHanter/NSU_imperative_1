#include <stdio.h>

typedef struct LongNum_s 
{ 
    int len;      // сколько цифр в числе 
    int arr[500]; // массив десятичных цифр числа 
} LongNum;

void fib_calc(LongNum *lnum, int N);
void fib_print(LongNum *lnum);
void long_plus(LongNum *result, LongNum *num1, LongNum *num2);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    LongNum fib_num;
    int N;
    scanf("%d",&N);

    fib_calc(&fib_num,N);
    fib_print(&fib_num);

    return 0;
}
void long_plus(LongNum *result, LongNum *num1, LongNum *num2){
    int carry = 0;
    int max_len;
    if (num1->len > num2->len) max_len=num1->len;
    else max_len=num2->len;
    
    for (int i = 0; i < max_len || carry; i++) {
        int sum = carry;
        if (i < num1->len) sum += num1->arr[i];
        if (i < num2->len) sum += num2->arr[i];
        
        result->arr[i] = sum % 10;
        carry = sum / 10;
        result->len = i + 1;
    }
}

void fib_calc(LongNum *lnum, int N){
    lnum->len = 1;
    lnum->arr[0]=1;

    LongNum lnum2;
    LongNum lnum3;

    lnum2.arr[0]=1, lnum2.len=1;
    lnum3.arr[0]=0, lnum3.len=1;
    
    for (int i=2;i<N;i++){
        lnum3.len = lnum2.len;
        for (int i=0;i<lnum2.len;i++) lnum3.arr[i]=lnum2.arr[i];
        lnum2.len = lnum->len;
        for (int i=0;i<lnum->len;i++) lnum2.arr[i]=lnum->arr[i];
        long_plus(lnum,&lnum2,&lnum3);
    }
}
void fib_print(LongNum *lnum){
    for (int i = lnum->len - 1; i >= 0; i--) printf("%d",lnum->arr[i]);
}