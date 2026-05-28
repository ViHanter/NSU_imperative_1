#include <stdio.h>
#include <string.h>

#define MAXA 105
#define MAXB 105

int graph[MAXA][MAXB];
int matchB[MAXB], matchA[MAXA];
int visited[MAXB];
int A, B, M;

int dfs(int u);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d %d", &A, &B, &M);

    memset(graph, 0, sizeof(graph));
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        graph[x][y] = 1;
    }

    memset(matchA, -1, sizeof(matchA));
    memset(matchB, -1, sizeof(matchB));

    int matching = 0;
    for (int u = 1; u <= A; u++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(u)) {
            matching++;
        }
    }

    printf("%d\n", matching);
    for (int u = 1; u <= A; u++) {
        if (matchA[u] != -1) {
            printf("%d %d\n", u, matchA[u]);
        }
    }

    return 0;
}

int dfs(int u) {
    for (int v = 1; v <= B; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = 1;
            if (matchB[v] == -1 || dfs(matchB[v])) {
                matchA[u] = v;
                matchB[v] = u;
                return 1;
            }
        }
    }
    return 0;
}