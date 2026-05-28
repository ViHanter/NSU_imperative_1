#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 200005

int head[MAXN], to[MAXM], nxt[MAXM], idx;
int dist[MAXN], queue[MAXN];
int front, rear;

void add_edge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    memset(head, -1, sizeof(head));
    idx = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    memset(dist, -1, sizeof(dist));
    dist[1] = 0;
    front = rear = 0;
    queue[rear++] = 1;

    while (front < rear) {
        int u = queue[front++];
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", dist[i]);
    }

    return 0;
}