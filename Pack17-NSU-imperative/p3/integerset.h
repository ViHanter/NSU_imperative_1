#ifndef INTEGERSET_H
#define INTEGERSET_H

typedef struct IntegerSet IntegerSet;

IntegerSet* CreateSet(int *arr, int size);
int IsInSet(IntegerSet *set, int value);

#endif