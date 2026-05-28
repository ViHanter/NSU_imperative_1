#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1005

char maze[CHUNK_SIZE][CHUNK_SIZE];
int visited[CHUNK_SIZE][CHUNK_SIZE];
int n;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void fill(int r, int c);

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    fgetc(stdin); 

    int start_c = -1;
    for (int i = 0; i < n; i++) {
        fgets(maze[i], CHUNK_SIZE + 2, stdin);
        if (i != 0) continue;
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == ' ') {
                start_c = j;
                break;
            }        
        }
    }

    if (start_c != -1) {
        fill(0, start_c);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == ' ' && !visited[i][j]) {
                count++;
                fill(i, j);
            }
        }
    }

    printf("%d\n", count);
    return 0;
}

void fill(int r, int c) {
    int* column_queue = malloc(CHUNK_SIZE * CHUNK_SIZE * sizeof(int));
    int* row_queue = malloc(CHUNK_SIZE * CHUNK_SIZE * sizeof(int));
    int head = 0, tail = 0;

    column_queue[tail] = c;
    row_queue[tail] = r;
    visited[r][c] = 1;
    tail++;

    while (head < tail) {
        int curr_r = row_queue[head];
        int curr_c = column_queue[head];
        head++;

        for (int i = 0; i < 4; i++) {
            int nr = curr_r + dx[i];
            int nc = curr_c + dy[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && 
                maze[nr][nc] == ' ' && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                row_queue[tail] = nr;
                column_queue[tail] = nc;
                tail++;
            }
        }
    }
    free(row_queue);
    free(column_queue);
}