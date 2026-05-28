#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200000

int A[MAX_N];
int deque[MAX_N];
int front = 0, back = 0;

void push_back(int idx) {
    deque[back++] = idx;
}

void pop_back() {
    back--;
}

void pop_front() {
    front++;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    char commands[2 * MAX_N];
    scanf("%s", commands);

    int L = 0, R = 0;
    for (int i = 0; commands[i] != '\0'; i++) {
        if (commands[i] == 'R') {
            while (front < back && A[deque[back - 1]] <= A[R]) {
                pop_back();
            }
            push_back(R);
            R++;
        } else {
            if (front < back && deque[front] == L) {
                pop_front();
            }
            L++;
        }
        printf("%d\n", A[deque[front]]);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}