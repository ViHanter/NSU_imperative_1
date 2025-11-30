#include <stdio.h>
#include <string.h>

char *concat(char *pref, char *suff){
    int a = strlen(pref);
    int b = strlen(suff);

    for (int i=0;i<b;i++){
        pref[a+i]=suff[i];
    }

    return pref;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char stringi[101];
    char res[100001] = {'\0'};

    
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%s",stringi);
        concat(res,stringi);
    }
    printf("%s",res);
    return 0;
}