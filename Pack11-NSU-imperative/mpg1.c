#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define HASH_SIZE 2000003  // простое число > 1e6
#define KEY_RANGE 1000000000

typedef struct HashNode {
    int32_t key;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_SIZE] = {NULL};

unsigned int hash(int32_t key) {
    unsigned int h = (unsigned int)key;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h % HASH_SIZE;
}

int contains(int32_t key) {
    unsigned int index = hash(key);
    HashNode *node = hashTable[index];
    while (node != NULL) {
        if (node->key == key) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void insert(int32_t key) {
    unsigned int index = hash(key);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = hashTable[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");

    int32_t n;
    fread(&n, sizeof(int32_t), 1, input);

    int32_t *numbers = (int32_t *)malloc(n * sizeof(int32_t));
    int32_t *result = (int32_t *)malloc(n * sizeof(int32_t));

    fread(numbers, sizeof(int32_t), n, input);

    int32_t k = 0;
    for (int32_t i = 0; i < n; i++) {
        if (!contains(numbers[i])) {
            result[k++] = numbers[i];
            insert(numbers[i]);
        }
    }

    fwrite(&k, sizeof(int32_t), 1, output);
    fwrite(result, sizeof(int32_t), k, output);

    free(numbers);
    free(result);
    freeHashTable();
    fclose(input);
    fclose(output);

    return 0;
}