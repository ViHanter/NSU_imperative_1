#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 200005

int head[MAXN], to[MAXM], nxt[MAXM], idx;
int color[MAXN], parent[MAXN], cycle_start, cycle_end;
int stack[MAXN], top;

void add_edge(int u, int v);

int dfs(int u);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));
    idx = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    memset(color, 0, sizeof(color));
    memset(parent, -1, sizeof(parent));
    cycle_start = -1;

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (dfs(i)) break;
        }
    }

    if (cycle_start == -1) {
        printf("-1\n");
        return 0;
    }

    top = 0;
    int v = cycle_end;
    while (v != cycle_start) {
        stack[top++] = v;
        v = parent[v];
    }
    stack[top++] = cycle_start;

    printf("%d\n", top);
    for (int i = top - 1; i >= 0; i--) {
        printf("%d", stack[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");

    return 0;
}
void add_edge(int u, int v) {
    to[idx] = v;
    nxt[idx] = head[u];
    head[u] = idx++;
}

int dfs(int u) {
    color[u] = 1;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (color[v] == 0) {
            parent[v] = u;
            if (dfs(v)) return 1;
        } else if (color[v] == 1) {
            cycle_start = v;
            cycle_end = u;
            return 1;
        }
    }
    color[u] = 2;
    return 0;
}