#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int *data = (int*)calloc(5,sizeof(int));
    int *new;
    printf("%d",strlen(data));

    return 0;
}