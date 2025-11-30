#include <stdio.h>

typedef struct LongNum_s 
{ 
    int len;      // сколько цифр в числе 
    int arr[3000]; // массив десятичных цифр числа 
} LongNum;

void long_mul(LongNum *result, LongNum *num1, LongNum *num2);
void convert_toLong(LongNum *num, int n);
void fac(LongNum *res,int n);
void print_fac(LongNum res);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    LongNum res;
    for (int i=0;i<3000;i++) res.arr[i]=0;
    res.arr[0]=1;
    res.len=1;
    int n;

    scanf("%d",&n);
    fac(&res,n);
    print_fac(res);
    
    return 0;
}

void print_fac(LongNum res){
    for (int i = res.len - 1; i >= 0; i--) printf("%d",res.arr[i]);
}
void long_mul(LongNum *result, LongNum *num1, LongNum *num2){
    int ost = 0;
    int start = 0, m_start = 0;
    int now = 0;

    LongNum temp = {0};
    for (int i = 0; i < 3000; i++) {
        temp.arr[i] = 0;
    }
    LongNum *a;
    LongNum *b;
    if (num1->len>num2->len) {a = num1; b = num2;}
    else {a = num2; b = num1;}
    printf("Умножение чисел: ");
    print_fac(*num1);
    printf(" на ");
    print_fac(*num2);
    printf("\n");
    for (int i=0;i<b->len;i++){
        for (int j=0;j<a->len;j++){
            ost += a->arr[j] * b->arr[i];
            now=j;

            printf("Происходит умножение %d на %d...\n",a->arr[j],b->arr[i]);
            if (temp.arr[now+start] + ost >= 10) {
                ost+=temp.arr[now+start];
                temp.arr[now+start] += ost%10;
                if (j == a->len - 1) temp.arr[now+start+m_start+1] = ost/10;
            } else temp.arr[now+start] += ost;
            printf("В ячейку %d помещаем %d, в остатке - %d\n\n",(now+start),ost%10,ost/10);
            /*printf("result на этой стадии: ");
            print_fac(temp);
            printf("\n\n");
            printf("%d => ",temp.arr[now+start+1]);
            printf("%d",temp.arr[now+start+1]);
            printf("  %d%d\n",temp.arr[now+start],temp.arr[now+start+1]);*/
            ost /= 10;
        }
        start++;
        m_start = 0;
    }
    
    while (ost){
        now++;
        temp.arr[now] = ost%10;
        ost/=10;
    }
    temp.len = 2999;
    while (temp.len > 0 && temp.arr[temp.len] == 0) {
    temp.len--;
    }
    temp.len++;

    result->len = temp.len;
    for (int i=0;i<result->len;i++) result->arr[i]= temp.arr[i];
    /*printf("\n");
    print_fac(*result);
    printf("\n");*/
}
void convert_toLong(LongNum *num, int n){
    int i = 0;
    while (n){
        num->arr[i] = n%10;
        n/=10;
        i++;
    }
    num->len = i;
};

void fac(LongNum *res,int n){
    LongNum n1;
    for (int i=0;i<3000;i++) n1.arr[i]=0;
    LongNum n2;

    for (int i=1;i<=n;i++){
        n1.len = res->len;
        for (int i=0;i<res->len;i++) n1.arr[i]= res->arr[i];
        
        convert_toLong(&n2,i);
        long_mul(res,&n1,&n2);
    }
}
