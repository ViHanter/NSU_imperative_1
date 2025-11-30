#include <stdio.h>

int calcLetters(char *iStr, int *oLowerCnt, int *oUpperCnt, int *oDigitsCnt) {
    int i=0;
    for (;iStr[i]!='\0' && iStr[i]!='\n';i++){
        if ('A'<=iStr[i] && iStr[i]<='Z') (*oUpperCnt)++;
        else if ('a'<=iStr[i] && iStr[i]<='z') (*oLowerCnt)++;
        else if ('0'<=iStr[i] && iStr[i]<='9') (*oDigitsCnt)++;
    }
    return i;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char stringi[10001];
    int oLower=0, oUpper=0, oDigits=0;
    int i=1,len;

    while (fgets(stringi,10001,stdin)) {
        len = calcLetters(stringi,&oLower,&oUpper,&oDigits);
        printf("Line %d has %d chars: %d are letters (%d lower, %d upper), %d are digits.\n",i,len,oUpper+oLower,oLower,oUpper,oDigits);
        i++;
        oLower=0,oUpper=0,oDigits=0;
    }
    return 0;
}