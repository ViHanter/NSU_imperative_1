#include <stdio.h>

int Generator(char *stringi,int *oUpper){
    int cnt = 0;
    for (int i=0; stringi[i]!='\0';i++){
        if ('A'<=stringi[i] && stringi[i]<='Z') (*oUpper)++;
        cnt++;
    }
    return cnt;
}
void splitka(char *stringi){
    for (int i=0;stringi[i]!='\0';i++){
        if (!('A'<=stringi[i] && stringi[i]<='z')) stringi[i]=' ';
    }
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char stringi[100001];
    char word[10001];
    int uppers = 0,len=0;
    int j=0;

    scanf("%s",stringi);
    splitka(stringi);

    for (int i=0;i<Generator(stringi,&uppers);i++){
        uppers = 0;
        len = 0;
        if (stringi[i]!=' '){
            word[j]=stringi[i];
            j++;
        }
        if ((stringi[i]==' ' || stringi[i+1]=='\0') && j!=0){
            word[j]='\0';
            len = Generator(word,&uppers);
            j=0;
            printf("%d/%d %s\n",uppers,len,word);
        }
    }
    


    return 0;
}