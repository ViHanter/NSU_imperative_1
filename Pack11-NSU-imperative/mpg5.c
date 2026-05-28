#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define TRIALS 50000
#define BITS 32

uint32_t hash_func(uint64_t A, uint64_t B, uint64_t M, uint64_t R, uint64_t S, uint32_t x) {
    uint64_t t = (A * (uint64_t)x + B) % M;
    t = t % R;
    t = t / S;
    return (uint32_t)t;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    uint64_t A, B, M, R, S;
    scanf("%llu %llu %llu %llu %llu", &A, &B, &M, &R, &S);

    srand(time(NULL));

    int change_count[BITS][BITS] = {0};

    for (int t = 0; t < TRIALS; t++) {
        uint32_t key = ((uint32_t)rand() << 16) ^ rand();
        uint32_t h1 = hash_func(A, B, M, R, S, key);

        for (int i = 0; i < BITS; i++) {
            uint32_t key2 = key ^ (1u << i);
            uint32_t h2 = hash_func(A, B, M, R, S, key2);

            uint32_t diff = h1 ^ h2;
            for (int j = 0; j < BITS; j++) {
                if (diff & (1u << j)) {
                    change_count[i][j]++;
                }
            }
        }
    }

    for (int i = 0; i < BITS; i++) {
        for (int j = 0; j < BITS; j++) {
            int percent = (int)((double)change_count[i][j] / TRIALS * 100 + 0.5);
            printf("%d", percent);
            if (j < BITS - 1) printf(" ");
        }
        printf("\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}