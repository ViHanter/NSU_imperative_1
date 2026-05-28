#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000
#define HASH_SIZE 2000003
#define BASE 911382323
#define MOD 972663749

typedef struct HashNode {
    long long key;
    int color;
    struct HashNode *next;
} HashNode;

HashNode *hash_table[HASH_SIZE] = {NULL};
int color_counter = 0;

unsigned int get_index(long long key) {
    return (unsigned int)((key ^ (key >> 32)) % HASH_SIZE);
}

int find_or_add_color(long long key) {
    unsigned int idx = get_index(key);
    HashNode *node = hash_table[idx];
    while (node != NULL) {
        if (node->key == key) {
            return node->color;
        }
        node = node->next;
    }
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->key = key;
    new_node->color = color_counter++;
    new_node->next = hash_table[idx];
    hash_table[idx] = new_node;
    return new_node->color;
}

void free_hash_table() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = hash_table[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
        hash_table[i] = NULL;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, B;
    scanf("%d %d", &N, &B);
    char S[MAX_N + 1];
    scanf("%s", S);

    long long *powB = (long long *)malloc((N + 1) * sizeof(long long));
    powB[0] = 1;
    for (int i = 1; i <= N; i++) {
        powB[i] = (powB[i-1] * BASE) % MOD;
    }

    long long *prefix_hash = (long long *)malloc((N + 1) * sizeof(long long));
    prefix_hash[0] = 0;
    for (int i = 0; i < N; i++) {
        prefix_hash[i+1] = (prefix_hash[i] * BASE + (S[i] - 'a' + 1)) % MOD;
    }

    for (int i = 0; i <= N - B; i++) {
        long long hash = (prefix_hash[i+B] - prefix_hash[i] * powB[B]) % MOD;
        if (hash < 0) hash += MOD;

        int color = find_or_add_color(hash);
        printf("%d", color);
        if (i < N - B) printf(" ");
    }
    printf("\n");

    free(powB);
    free(prefix_hash);
    free_hash_table();

    fclose(stdin);
    fclose(stdout);
    return 0;
}