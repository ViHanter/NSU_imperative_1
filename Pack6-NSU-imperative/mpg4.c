#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint64_t bits;
    uint8_t len;
} Bin;


int main(void) {
    FILE *input = fopen("input.txt","rb");
    FILE *output = fopen("output.txt","wb");

    uint32_t N;
    fread(&N,4,1,input);

    Bin *nums = (Bin*)calloc(N,sizeof(Bin));
    for (uint32_t i=0;i<N;i++){
        uint32_t L;
        fread(&L,4,1,input);
        nums[i].len = (uint8_t)L;
        
        uint64_t num=0;
        for (uint32_t j=0;j<L;j++){
            if ((fgetc(input)&1)!=0) num = num | ((uint64_t)1 << j);  
        }
        nums[i].bits = num;
    }
    uint32_t M;
    fread(&M,4,1,input);
    
    uint8_t byte = 0;
    uint8_t bit_pos = 0;
    
    for (uint32_t i = 0; i < M; i++) {
        uint16_t symbol;
        fread(&symbol, 2, 1, input);
        Bin code = nums[symbol];
        
        for (uint8_t j = 0; j < code.len; j++) {
            uint8_t bit = (code.bits >> j) & 1;
            byte |= bit << bit_pos();
            bit_pos++;
            if (bit_pos == 8) {
                fwrite(&byte, 1, 1, output);
                byte = 0;
                bit_pos = 0;
            }
        }
    }

    if (bit_pos>0){
        while (bit_pos!=8)
        {
            byte |= (0 << bit_pos);
            bit_pos++;
        }
        fwrite(&byte,1,1,output);
    }


    return 0;
}