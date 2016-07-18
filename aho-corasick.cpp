
#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000000;
const int ALPHABET = 26;

int sz = 1;
int to[MAXV][ALPHABET];
int link[MAXV];
bool leaf[MAXV];
int pr[MAXV];
int ch[MAXV];
vector <int> ind[MAXV];

void add(string s, int j) {
    int v = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        if (to[v][(int) s[i] - 'a'] == -1) { 
            pr[sz] = v;
            ch[sz] = s[i] - 'a';
            to[v][(int) s[i] - 'a'] = sz++;
        }
        v = to[v][(int) s[i] - 'a'];
    }
    ind[v].push_back(j);
}

void calc_good() {
    queue <int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < (int) ind[link[v]].size(); i++) {
            ind[v].push_back(ind[link[v]][i]);
        }
        for (int i = 0; i < ALPHABET; i++) {
            if (to[v][i] != -1) {
                q.push(to[v][i]);
            }
        }
    }
}

void calc_links() {
    queue <int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (v != 0) {
            int cur = pr[v];
            int c = ch[v];
            while (cur != 0) {
                cur = link[cur];
                if (to[cur][c] != -1) {
                    break; 
                }
            }
            if (pr[v] == 0) {
                link[v] = 0;
            } else if (to[cur][c] != -1) {
                link[v] = to[cur][c];
            } else {
                link[v] = 0;
            }
        }
        for (int i = 0; i < ALPHABET; i++) {
            if (to[v][i] != -1) {
                q.push(to[v][i]);
            }
        }
    }
}

int go(int v, int c) {
    int cur = v;
    while (cur != 0 && to[cur][c] == -1) {
        cur = link[cur];
    }
    string s;
    if (to[cur][c] == -1) {
        return 0;
    } else {
        to[v][c] = to[cur][c];
        return to[cur][c];
    }
}

bool ans[1000000];

int n, v;

int main() {
    string s;
    cin >> n;
    memset(to, -1, sizeof to);
    for (int i = 0; i < n; i++) {
        cin >> s;
        add(s, i);
    }
    calc_links();
    calc_good();
    cin >> s;
    for (int i = 0; i < (int) s.length(); i++) {
        v = go(v, (int) s[i] - 'a'); 
        for (int j = 0; j < (int) ind[v].size(); j++) {
            ans[ind[v][j]] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
