#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "decls.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

EXPORT
void echo_0(State *state) {
    printf("ECHO: \n");
}
EXPORT
void echo_1(State *state, char *arg0) {
    printf("ECHO: %s\n", arg0);
}
EXPORT
void echo_2(State *state, char *arg0, char *arg1) {
    printf("ECHO: %s|%s\n", arg0, arg1);
}
EXPORT
void echo_3(State *state, char *arg0, char *arg1, char *arg2) {
    printf("ECHO: %s|%s|%s\n", arg0, arg1, arg2);
}
EXPORT
void print_1(State *state, char *idx) {
    int i = atoi(idx);
    printf("%s\n", state->regs[i]);
}
EXPORT
void printregs_0(State *state) {
    for (int i = 0; i < 256; i++) {
        if (state->regs[i] != NULL) {
            printf("%d = %s\n", i, state->regs[i]);
        }
    }
}
EXPORT
void store_2(State *state, char *idx, char *what) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
    }
    state->regs[i] = malloc(strlen(what) + 1);
    strcpy(state->regs[i], what);
}
EXPORT
void copy_2(State *state, char *dst, char *src) {
    int d = atoi(dst);
    int s = atoi(src);
    if (state->regs[d] != NULL) {
        free(state->regs[d]);
    }
    state->regs[d] = malloc(strlen(state->regs[s]) + 1);
    strcpy(state->regs[d], state->regs[s]);
}
EXPORT
void clear_1(State *state, char *idx) {
    int i = atoi(idx);
    if (state->regs[i] != NULL) {
        free(state->regs[i]);
        state->regs[i] = NULL;
    }
}