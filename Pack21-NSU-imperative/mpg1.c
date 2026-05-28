#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 105
#define MAXK 10005

int cap[MAXN][MAXN];
int parent[MAXN], queue[MAXN];
int n, k;

int bfs(int s, int t);
int max_flow(int s, int t);

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &n, &k);

    memset(cap, 0, sizeof(cap));

    for (int i = 0; i < k; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        cap[u][v] += c;
        cap[v][u] += c;
    }

    printf("%d\n", max_flow(1, n));

    return 0;
}


int bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    int front = 0, rear = 0;
    queue[rear++] = s;
    parent[s] = s;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= n; v++) {
            if (parent[v] == -1 && cap[u][v] > 0) {
                parent[v] = u;
                if (v == t) return 1;
                queue[rear++] = v;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int min_cap = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (cap[u][v] < min_cap)
                min_cap = cap[u][v];
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= min_cap;
            cap[v][u] += min_cap;
        }
        flow += min_cap;
    }
    return flow;
}