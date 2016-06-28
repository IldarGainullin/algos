#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fc first
#define sc second
#define endl '\n'
#define ll long long
#define forn(i, n) for(int i = 0; i < (int) (n); i++)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const int MAXN = (int) 1e5 + 7;
const int MAXV = 2 * MAXN + 7;
const int ALPHA = 255;

int to[MAXV][ALPHA];
int len[MAXV];
int link[MAXV];
int last = 0, sz = 0;

void init() {
    len[0] = 0;
    link[0] = -1;
    memset(to, 0, sizeof to);
    sz = 1;
    last = 0;
}

void add_char(char c) {
    int cur = sz++;
    int p = last;
    len[cur] = len[p] + 1;
    while (p != -1 && !to[p][c]) {
        to[p][c] = cur;
        p = link[p];
    }
    if (p == -1) {
        link[cur] = 0;
    } else {
        int q = to[p][c];
        if (len[q] == len[p] + 1) {
            link[cur] = q;
        } else {
            int suf = sz++;
            len[suf] = len[p] + 1;
            link[suf] = link[q];
            forn (t, ALPHA) {
                to[suf][t] = to[q][t];
            }
            while (p != -1 && to[p][c] == q) {
                to[p][c] = suf;
                p = link[p];
            }
            link[cur] = link[q] = suf;
        }
    }
    last = cur;
}

ll diff_substr(string s) {
    init();
    for (auto c : s) {
        add_char(c);
    }
    ll ans = 0;
    forn (v, sz) {
        ans += len[v] - len[link[v]];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout << diff_substr("abacaba") << endl;
}

