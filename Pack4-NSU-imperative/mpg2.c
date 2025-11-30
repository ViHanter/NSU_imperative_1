#include <stdio.h>
#include <string.h>

void reverse (char *start, int len){
    for (int i=0;i<len/2;i++){
        char l=start[i];
        start[i]=start[len-1-i];
        start[len-1-i]=l;
    }
}
int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    char stringi[101];
    int n;
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%s",stringi);
        reverse(stringi,strlen(stringi));
        if (i!=n-1) printf("%s\n",stringi);
        else printf("%s",stringi);
    }

    return 0;
}