#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "No parameters specified.\n");
        return 13;
    }

    long long mod = -1;
    char *operation = NULL;
    long long a, b;

    if (argc > 2 && strcmp(argv[1], "-m") == 0) {
        mod = atoll(argv[2]);
        operation = argv[3];
        a = atoll(argv[4]);
        b = atoll(argv[5]);
    }
    else if (argc > 4 && strcmp(argv[argc - 2], "-m") == 0) {
        mod = atoll(argv[argc - 1]);
        operation = argv[1];
        a = atoll(argv[2]);
        b = atoll(argv[3]);
    }
    else if (argc == 4) {
        operation = argv[1];
        a = atoll(argv[2]);
        b = atoll(argv[3]);
    } else {
        return 1;
    }

    long long result;
    if (strcmp(operation, "add") == 0) {
        result = a + b;
    } else if (strcmp(operation, "sub") == 0) {
        result = a - b;
    } else if (strcmp(operation, "mul") == 0) {
        result = a * b;
    } else {
        return 1;
    }

    if (mod != -1) {
        result %= mod;
        if (result < 0) result += mod;
    }

    printf("%lld\n", result);
    return 0;
}