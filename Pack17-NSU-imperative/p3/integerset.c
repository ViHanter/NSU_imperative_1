#include "integerset.h"
#include <stdlib.h>

struct IntegerSet {
    int *data;
    int size;
};

static int cmp(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

IntegerSet* CreateSet(int *arr, int size) {
    IntegerSet *set = (IntegerSet*)malloc(sizeof(IntegerSet));
    if (!set) return NULL;

    set->size = size;

    if (size == 0) {
        set->data = NULL;
        return set;
    }

    set->data = (int*)malloc(size * sizeof(int));
    if (!set->data) return NULL;

    // копируем массив
    for (int i = 0; i < size; i++) {
        set->data[i] = arr[i];
    }

    // сортируем
    qsort(set->data, size, sizeof(int), cmp);

    // проверяем дубликаты
    for (int i = 1; i < size; i++) {
        if (set->data[i] == set->data[i - 1]) {
            return NULL;
        }
    }

    return set;
}

int IsInSet(IntegerSet *set, int value) {
    if (set == NULL || set->size == 0) return 0;

    int left = 0, right = set->size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (set->data[mid] == value)
            return 1;
        else if (set->data[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}