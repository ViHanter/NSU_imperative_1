#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int key;
    char value[8];
    int original_order;
};

int compare_records(const void *a, const void *b) {
    const struct Record *rec1 = (const struct Record *)a;
    const struct Record *rec2 = (const struct Record *)b;
    
    if (rec1->key < rec2->key) return -1;
    if (rec1->key > rec2->key) return 1;
    
    return (rec1->original_order - rec2->original_order);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);
    
    struct Record *records = malloc(N * sizeof(struct Record));

    for (int i = 0; i < N; i++) {
        scanf("%d %s", &records[i].key, records[i].value);
        records[i].original_order = i;
    }

    qsort(records, N, sizeof(struct Record), compare_records);

    for (int i = 0; i < N; i++) {
        printf("%d %s\n", records[i].key, records[i].value);
    }

    free(records);

    return 0;
}