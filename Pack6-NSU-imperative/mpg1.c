#include <stdio.h>
#include <stdint.h>
/*
Алгоритм:
1) считать байты
2) Проверить big-endian или little-endian
3) Цикл uint32_t i < uint32_t n
3) В буффер закидываю сумму следующих n бинарных чисел
*/
uint32_t convert_to_bigendian(uint32_t num) {
    return ((num >> 24) & 0x000000FF) |    // перемещаем байт 3 в позицию 0
           ((num >> 8)  & 0x0000FF00) |    // перемещаем байт 2 в позицию 1
           ((num << 8)  & 0x00FF0000) |    // перемещаем байт 1 в позицию 2
           ((num << 24) & 0xFF000000);     // перемещаем байт 0 в позицию 3
}

int main(void){
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");

    uint32_t n,num;
    uint32_t sum=0;

    fread(&n,sizeof(uint32_t),1,input);

    if (n>10000){
        for(uint32_t i=0;i<convert_to_bigendian(n);i++){
            fread(&num,sizeof(uint32_t),1,input);
            sum+=convert_to_bigendian(num);
        }
        sum = convert_to_bigendian(sum);
    } else {
        for (uint32_t i=0;i<n;i++) {
            fread(&num,sizeof(uint32_t),1,input);
            sum+=num;
        }
    }

    fwrite(&sum,sizeof(uint32_t),1,output);

    /*int is_little_endian = 0;
    if (n[0]!=0 && n[3]==0) is_little_endian = 1;
    else if (n[0]==0 && n[3]!=0) is_little_endian = 0;
    else {
        if (n[1]!=0 && n[2]==0) is_little_endian = 1;
        else is_little_endian = 0;
    }*/
    


    return 0;
}