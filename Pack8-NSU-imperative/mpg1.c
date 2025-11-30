#include <stdio.h>
#include <stdlib.h>

typedef enum {
    CREATE,
    DELETE,
    PRINT,
    COUNT
} commands;

int count(char *,char);

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int N;
    scanf("%d",&N);
    char **buff = (char**)malloc(N*sizeof(char*));

    for (int i = 0; i < N; i++) {
        buff[i] = NULL;
    }
    
    int next_ID=0;
    
    for (int i=0;i<N;i++){
        int command,idx,len;
        scanf("%d",&command);
        switch(command){
            case CREATE:
                scanf("%d",&len);
                buff[next_ID] = (char*)malloc((len+1)*sizeof(char));
                scanf("%s",buff[next_ID]);
                next_ID++;
                break;
            case DELETE:
                scanf("%d",&idx);
                free(buff[idx]);
                buff[idx] = NULL;
                break;
            case PRINT:
                scanf("%d",&idx);
                printf("%s\n",buff[idx]);
                break;
            case COUNT:
                char target;
                scanf("%d",&idx);
                scanf(" %c",&target);
                printf("%d\n",count(buff[idx],target));
                break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (buff[i] != NULL) {
            free(buff[i]);
        }
    }
    free(buff);
    return 0;
}

int count(char *buffer,char target){
    int cnt=0;
    for (int i=0;buffer[i]!='\0';i++){
        if (buffer[i]==target) cnt++;
    }
    return cnt;
}