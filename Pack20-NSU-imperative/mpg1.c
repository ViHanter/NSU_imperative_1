#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int head[MAXN], to[MAXM], nxt[MAXM], idx;
int indeg[MAXN], queue[MAXN], topo[MAXN], assign[MAXN];
int front, rear;

void add_edge(int u, int v);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));
    memset(indeg, 0, sizeof(indeg));
    idx = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        indeg[v]++;
    }

    front = rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            queue[rear++] = i;
        }
    }

    int topo_size = 0;
    while (front < rear) {
        int u = queue[front++];
        topo[topo_size++] = u;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            indeg[v]--;
            if (indeg[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    if (topo_size != n) {
        printf("NO\n");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        assign[topo[i]] = i + 1;
    }

    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        printf("%d", assign[i]);
        if (i < n) printf(" ");
    }
    printf("\n");

    return 0;
}

void add_edge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}