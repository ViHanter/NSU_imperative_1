#include <stdio.h>

int readTime(char *iStr, int *oHours, int *oMinutes, int *oSeconds) {
    int dcnt = 0, j = 0;
    char num[10];
    int h = 0, m = 0, s = 0;
    

    if (oHours != NULL) *oHours = 0;
    if (oMinutes != NULL) *oMinutes = 0;
    if (oSeconds != NULL) *oSeconds = 0;

    for (int i = 0; iStr[i] != '\0'; i++) {
        if (iStr[i] == ':') {
            if (dcnt == 0) {
                num[j] = '\0';
                h = 1;
                if (oHours != NULL) sscanf(num, "%d", oHours);
            } else if (dcnt == 1) {
                num[j] = '\0';
                m = 1;
                if (oMinutes != NULL) sscanf(num, "%d", oMinutes);
            }
            dcnt++;
            j = 0;
            if (dcnt > 2) return 0;
        }
        if (!(('0' <= iStr[i] && iStr[i] <= '9') || iStr[i] == ':')) return 0;
        if ('0' <= iStr[i] && iStr[i] <= '9') {
            if (j < 9) { // защита от переполнения буфера
                num[j] = iStr[i];
                j++;
            }
        }
    }
    
    // Обработка последнего числа
    if (j > 0) {
        num[j] = '\0';
        if (dcnt == 0) {
            h = 1;
            if (oHours != NULL) sscanf(num, "%d", oHours);
        } else if (dcnt == 1) {
            m = 1;
            if (oMinutes != NULL) sscanf(num, "%d", oMinutes);
        } else if (dcnt == 2) {
            s = 1;
            if (oSeconds != NULL) sscanf(num, "%d", oSeconds);
        }
    }

    if (oHours != NULL && !(0 <= *oHours && *oHours <= 23)) return 0;
    if (oMinutes != NULL && !(0 <= *oMinutes && *oMinutes <= 59)) return 0;
    if (oSeconds != NULL && !(0 <= *oSeconds && *oSeconds <= 59)) return 0;

    return 1;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int hours,minutes,seconds;
    char time[1001];

    scanf("%s",time);
    int res1 = readTime(time,&hours,&minutes,&seconds);
    if (res1==1){
        printf("%d %d %d %d\n",res1,hours,minutes,seconds);
        int res2 = readTime(time,&hours,&minutes,NULL);
        printf("%d %d %d\n",res1,hours,minutes);
        int res3 = readTime(time,&hours,NULL,NULL);
        printf("%d %d",res1,hours);
    } else {
        printf("0 -1 -1 -1\n");
        printf("0 -1 -1\n");
        printf("0 -1\n");
    }

    return 0;
}