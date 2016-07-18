#include <bits/stdc++.h>

using namespace std;

const int MAXV = 20003;

short int f[MAXV][MAXV], c[MAXV][MAXV];
bool used[MAXV];
int pr[MAXV];
int MIN_C = INT_MAX;
int n, m, x;
int S = 20001;
int T = 20002;

bool bfs(int s, int t) {
    memset(used, 0, sizeof used);
    queue <int> q;
    q.push(s);
    used[s] = 1;
    pr[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        if (v == t) 
            return true;
        q.pop();
        for (int i = 1; i <= n + n + 2; i++) {
            if (c[v][i] && c[v][i] - f[v][i] > 0) {
                if (!used[i]) {
                    q.push(i);
                    used[i] = 1;
                    pr[i] = v;
                }
            }
        }
    }
    return false;
}

int edkarp(int s, int t) {
    memset(f, 0, sizeof f);
    while (bfs(s, t)) {
        MIN_C = 32767;
        int v = t;
        while (v != s) {
            MIN_C = min(c[pr[v]][v] - f[pr[v]][v], MIN_C);
            v = pr[v];
        }
        v = t;
        while (v != s) {
            int u = pr[v];
            f[u][v] += MIN_C;
            f[v][u] -= MIN_C;
            v = pr[v];
        }
    }
    int flow = 0;
    for (int i = 1; i <= n + n + 2; i++)
        if (c[s][i] > 0) {
            flow += f[s][i];
        }
    return flow;
}

int main() {
    int k, u, v;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> c[S][i];
    }
    for (int i = n + 1; i <= n + n; i++) {
        cin >> c[i][T];
    }
    for (int i = 0; i < k; i++) {
        cin >> u >> v;
        c[u][v + n] = 32767;
        c[v + n][u] = 32767;
    }
    cout << edkarp(S, T) << endl;
}
