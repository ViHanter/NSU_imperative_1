#include <stdio.h>

void table(int h1,int h2,int h3){
    putchar('+'); 
    for(int i=0;i<h1;i++) putchar('-');
    putchar('+');
    for(int i=0;i<h2;i++) putchar('-');
    putchar('+');
    for(int i=0;i<h3;i++) putchar('-');
    putchar('+');
}

int getRazr(int num){
    if (num==0)return 1;
    int cnt=0;
    while(num>0){
        num/=10;
        cnt++;
    }
    return cnt;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N;
    scanf("%d",&N);

    int cntBuff[100000] = {0};
    int timeBuff[100000] = {0};

    int id,dl;
    int maxID=0,maxDL=0,maxCNT=0;

    for (int i=0;i<N;i++){
        scanf("%d %d",&id,&dl);
        cntBuff[id]++;
        timeBuff[id]+=dl;
    }
    for (int i=0;i<100000;i++){
        if (cntBuff[i]!=0) {
            maxID=i;
            if(cntBuff[i]>maxCNT) maxCNT=cntBuff[i];
        }
        if (timeBuff[i]>maxDL) maxDL = timeBuff[i];
    }

    int h1 = getRazr(maxID)+2, h2 = getRazr(maxCNT)+2, h3 = getRazr(maxDL)+2;
    for (int i=0;i<100000;i++){
        if (cntBuff[i]){
            table(h1,h2,h3);
            printf("\n| %*d | %*d | %*d |\n",h1-2,i,h2-2,cntBuff[i],h3-2,timeBuff[i]);
        }
    }
    table(h1,h2,h3);
    return 0;
}