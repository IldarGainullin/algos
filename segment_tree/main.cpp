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
const int INF = (int) 1e9 + 7;
int t[4 * MAXN];
int d[4 * MAXN];
int a[MAXN];
const int NEUTRAL = 0;
const int BLOCKED = -INF;

int op(int x, int l, int r) {
    return (r - l) * x;
}

int func(int a, int b) {
    return a + b;
}

int mod(int a, int b) {
    a = b;
}

void push(int v, int l, int r) {
    if (d[v] != BLOCKED) {
        int m = (l + r) / 2;
        t[v * 2 + 1] = op(d[v], l, m);
        t[v * 2 + 2] = op(d[v], m, r);
        d[v * 2 + 1] = mod(d[v * 2 + 1], d[v]);
        d[v * 2 + 2] = mod(d[v * 2 + 2], d[v]);
        d[v] = BLOCKED;
    }
}

void build(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = a[l];
        d[v] = BLOCKED;
    } else {
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m);
        build(v * 2 + 2, m, r);
        t[v] = func(t[v * 2 + 1], t[v * 2 + 2]);
        d[v] = BLOCKED;
    }
}

int get(int v, int l, int r, int tl, int tr) {
    if (tl >= r || tr <= l) {
        return NEUTRAL;
    } else if (tl >= l && tr <= r) {
        return t[v];
    } else {
        int tm = (tl + tr) / 2;
        push(v, tl, tr);
        return func(get(v * 2 + 1, l, r, tl, tm), get(v * 2 + 2, l, r, tm, tr));
    }
}

void upd(int v, int l, int r, int tl, int tr, int x) {
    if (tl >= r || tr <= l) {
        return;
    } else if (tl >= l && tr <= r) {
        t[v] = op(x, tl, tr);
        d[v] = mod(d[v], x);
    } else {
        int tm = (tl + tr) / 2;
        push(v, tl, tr);
        upd(v * 2 + 1, l, r, tl, tm, x);
        upd(v * 2 + 2, l, r, tm, tr, x);
        t[v] = func(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
}

