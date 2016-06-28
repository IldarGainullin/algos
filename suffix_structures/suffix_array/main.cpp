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

int l;
int n;

const int MAXN = (int) 1e5 + 7;

int safe(int i) {
    if (i >= n) {
        i -= n;
    }
    return i;
}

int c[MAXN], h[MAXN], sa[MAXN], nc[MAXN], n_sa[MAXN];

void build_sa(string s) {
    n = s.size();
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        c[i] = s[i] - 31;
        h[c[i] + 1]++;
    }
    for (int i = 0; i < 255; i++) {
        h[i + 1] += h[i];
    }
    int head = 0;
    for (l = 0; l < n && head < n; l = (l ? l << 1 : 1)) {
        for (int i = 0; i < n; i++) {
            int right = safe(sa[i] - l + n);
            n_sa[h[c[right]]++] = right;
        }
        head = 0;
        for (int i = 0; i < n; i++) {
            if (!i || (c[n_sa[i - 1]] != c[n_sa[i]]) || ((c[safe(n_sa[i - 1] + l)] != c[safe(n_sa[i] + l)]))) {
                h[head++] = i;
            }
            nc[n_sa[i]] = head - 1;
        }
        memcpy(c, nc, n * sizeof(nc[0]));
        memcpy(sa, n_sa, n * sizeof(n_sa[0]));
    }
}

int main() {
    ios_base::sync_with_stdio(0);
}

