#include <stdio.h>
// 1 - проверка конца файла и чтение символа 

int main(void) {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    char sym='\0',prev='\0'; // переменные для чтения настоящего и предыдущего символа
    int odComm = 0, mnComm = 0; // переменные bool начало/конец /**/ и //

    int isString = 0; // переменная bool для проверки начала кавычек 
    while (1){
        prev = sym; // запоминание предыдущего символа
        if (scanf("%c",&sym)!=1) break; // *1

        if (isString==0 && sym=='"' && prev!='\'' && odComm==0 && mnComm==0) { 
            printf("%c",sym);
            isString=1; // этот блок рассматривает случай открытия кавычек
            continue;
        }
        if (isString==1 && sym=='"') {
            isString=0; // этот блок рассматривает случай закрытия кавычек
        }

        if (isString==1){
            printf("%c",sym); // блок, когда кавычки открыты
            continue;
        }

        // далее идет блок, рассматривающий ситуацию, близкую к открытию комментария

        if (sym=='/' && mnComm==0 && odComm==0) { 
            if (scanf("%c",&sym)!=1) { 
                printf("/");
                break; // *1
            }
            if (sym=='*') {
                //printf(" OO ");
                mnComm=1;       // случай, когда мн. комментарии
                continue;
            }else if (sym=='/'){
                odComm=1;      // случай, когда ед. комментарии
                continue;
            } else {   
                printf("/%c",sym);   // случай, когда / оказался обычным символом
                continue;
            }
        }

        /* 
        далее идут 2 блока, рассматривающих, как программе вести себя, когда:
            1. идут мн. комментарии
            2. идут одиночные комментарии
        */
        if (mnComm==1) {
            if (sym=='\n') printf("\n"); // проверка на enter

            //блок, рассматривающий случай, способный привести к закрытию комментариев
            if (sym=='*') {
                if (scanf("%c",&sym)!=1) break; // 1*
                if (sym=='/') {
                    //printf(" ZZ ");
                    mnComm=0;   // закрытие комментариев
                    continue;
                }
            }
            continue;
        } else if (odComm==1){
            if (sym=='\n') {
                odComm=0;       //закрытие одиночного комментария при переходе на новую строку
                printf("\n");
            }
            continue;
        }
        printf("%c",sym);      // печать символа
    }

    return 0;
}
