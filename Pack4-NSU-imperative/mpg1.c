#include <stdio.h>
#include <stdlib.h>

int isIn(int array[],int num,int len){
    for (int i=0;i<len;i++){
        if (array[i] == num) return 1;
    }
    return 0;
}
int compare(const void *a,const void *b){
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1<arg2) return -1;
    if (arg1>arg2) return 1;
    return 0;
    
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int nA,nB;
    int num;

    int arrA[100000];
    int arrB[100000];
    int res[100000];

    int count=0;
    
    scanf("%d",&nA);
    for (int i=0;i<nA;i++){
        scanf("%d",&num);
        if (isIn(arrA,num,nA)==0 )arrA[i] = num;
        else {
            i--;
            nA--;
        }
    }

    scanf("%d",&nB);
    for (int i=0;i<nB;i++){
        scanf("%d",&num);
        if (isIn(arrB,num,nA)==0 )arrB[i] = num;
        else {
            i--;
            nB--;
        }
    }

    for (int i=0;i<nA;i++) {
        if (isIn(arrB,arrA[i],nB) == 0) {
            count++;
            res[count-1]=arrA[i];
        }
    }
    qsort(res,count,sizeof(int),compare);

    printf("%d",count);
    if (count!=0){
        printf("\n");
        for (int i=0;i<count-1;i++) {
            printf("%d ",res[i]);
        }
        printf("%d",res[count-1]);
    }

    return 0;
}