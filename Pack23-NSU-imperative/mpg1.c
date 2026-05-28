#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 12

int M, N;
char grid[MAX_SIZE][MAX_SIZE + 1];
int queen_pos[MAX_SIZE];

bool is_valid(int row, int col) {
    if (grid[row][col] == '.') {
        return false;
    }
    
    for (int i = 0; i < row; i++) {
        int prev_col = queen_pos[i];
        
        // Вертикаль
        if (prev_col == col) {
            return false;
        }
        
        // Диагонали
        if (abs(i - row) == abs(prev_col - col)) {
            return false;
        }
    }
    return true;
}

bool solve(int row) {
    if (row == M) {
        return true; 
    }
    
    for (int col = 0; col < N; col++) {
        if (is_valid(row, col)) {
            queen_pos[row] = col;
            
            if (solve(row + 1)) {
                return true;
            }
        }
    }
    return false;
}

int main(void) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d %d", &M, &N);
    
    for (int i = 0; i < M; i++) {
        scanf("%s", grid[i]);
    }
    
    if (solve(0)) {
        printf("YES\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (queen_pos[i] == j) {
                    printf("X");
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    } else {
        printf("NO\n");
    }
    
    return 0;
}
