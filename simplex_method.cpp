

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <iomanip>

using namespace std;


typedef long long ll;
typedef unsigned long long ull;

typedef long double ld;

const int N = 5000 + 7;
const ld EPS = 1e-9;

int pos[N];
ld a[N][N], b[N], c[N], oc[N], x[N], ansx[N];
int n, m;
mt19937 kok(1488);

void del(int e, int n)
{
    for (int i = 0; i < n + m; i++)
    {
        c[i] -= a[pos[e]][i] * c[e];
    }
    c[e] = 0;
}

void pivot(int e, int l, int n)
{
    a[pos[l]][l] = 1;
    for (int i = 0; i < n + m; i++)
    {
        if (i != e)
        {
            a[pos[l]][i] /= a[pos[l]][e];
        }
    }
    b[pos[l]] /= a[pos[l]][e];
    a[pos[l]][e] = 0;
    swap(pos[l], pos[e]);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n + m; j++)
        {
            a[i][j] -= a[i][e] * a[pos[e]][j];
        }
        b[i] -= a[i][e] * b[pos[e]];
        a[i][e] = 0;
    }
    for (int i = 0; i < n + m; i++)
    {
        c[i] -= a[pos[e]][i] * c[e];
    }
    c[e] = 0;
    del(e, n);
}

void init(int _n, int _m)
{
    n = _n, m = _m;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j <= n + m; j++)
        {
            if (j >= n)
            {
                a[i][j] = 0;
            }
        }
    }
    for (int i = 0; i <= n + m; i++)
    {
        oc[i] = 0, pos[i] = -1;
    }
    for (int i = 0; i < m; i++)
    {
        pos[n + i] = i;
    }
    for (int i = 0; i < n; i++)
    {
        oc[i] = c[i];
    }
}

ld inc_number(int e)
{
    ld lval = 1e100;
    for (int i = 0; i < n + m; i++)
    {
        if (pos[i] != -1)
        {
            ld val;
            if (a[pos[i]][e] > EPS)
            {
                val = b[pos[i]] / a[pos[i]][e];
            }
            else
            {
                val = 1e100;
            }
            lval = min(lval, val);
        }
    }
    return lval;
}

int hack()
{
    n++;
    while (true)
    {
        int ind = -1;
        ld cur = -1e100;
        for (int e = 0; e < n + m; e++)
        {
            if (c[e] >= EPS)
            {
                ld go = inc_number(e);
                if (go > cur)
                {
                    cur = go;
                    ind = e;
                }
            }
        }
        if (ind == -1)
        {
            break;
        }
        if (cur < EPS)
        {
            vector<int> kek;
            for (int e = 0; e < n + m; e++)
            {
                if (c[e] >= EPS)
                {
                    kek.push_back(e);
                }
            }
            ind = kek[kok() % (int) (kek.size())];
        }
        int e = ind;
        ld lval = 1e100;
        int l = -1;
        for (int i = 0; i < n + m; i++)
        {
            if (pos[i] != -1)
            {
                ld val;
                if (a[pos[i]][e] > EPS)
                {
                    val = b[pos[i]] / a[pos[i]][e];
                }
                else
                {
                    val = 1e100;
                }
                if (lval > val)
                {
                    lval = val, l = i;
                }
            }
        }
        if (lval > 5e99)
        {
            return 1;
        }
        pivot(e, l, n);
    }
    for (int i = 0; i < n + m; i++)
    {
        if (pos[i] != -1)
        {
            x[i] = b[pos[i]];
        }
        else
        {
            x[i] = 0;
        }
    }
    n--;
    return 0;
}

int solve(int n)
{
    int j = -1;
    for (int i = 0; i < m; i++)
    {
        if (b[i] <= -EPS)
        {
            if (j == -1 || b[i] < b[j])
            {
                j = i;
            }
        }
    }
    if (j != -1)
    {
        for (int i = 0; i < n + m; i++)
        {
            c[i] = 0;
        }
        c[n + m] = -1;
        for (int i = 0; i < m; i++)
        {
            a[i][n + m] = -1;
        }
        pivot(n + m, n + j, n + 1);
        int res = hack();
        if (x[n + m] > EPS)
        {
            return -1;
        }
        if (pos[n + m] != -1)
        {
            int ind = 0;
            for (int i = 0; i < n + m; i++)
            {
                if (abs(a[pos[n + m]][i]) > EPS)
                {
                    ind = i;
                }
            }
            pivot(ind, n + m, n + 1);
        }
    }
    for (int i = 0; i < n + m; i++)
    {
        c[i] = oc[i];
    }
    for (int i = 0; i < n + m; i++)
    {
        if (pos[i] != -1)
        {
            del(i, n);
        }
    }
    while (true)
    {
        int ind = -1;
        ld cur = -1e100;
        for (int e = 0; e < n + m; e++)
        {
            if (c[e] >= EPS)
            {
                ld go = inc_number(e);
                if (go > cur)
                {
                    cur = go;
                    ind = e;
                }
            }
        }
        if (ind == -1)
        {
            break;
        }
        if (cur < EPS)
        {
            vector<int> kek;
            for (int e = 0; e < n + m; e++)
            {
                if (c[e] >= EPS)
                {
                    kek.push_back(e);
                }
            }
            ind = kek[kok() % (int) (kek.size())];
        }
        int e = ind;
        ld lval = 1e100;
        int l = -1;
        for (int i = 0; i < n + m; i++)
        {
            if (pos[i] != -1)
            {
                ld val;
                if (a[pos[i]][e] > EPS)
                {
                    val = b[pos[i]] / a[pos[i]][e];
                }
                else
                {
                    val = 1e100;
                }
                if (lval > val)
                {
                    lval = val, l = i;
                }
            }
        }
        if (lval > 5e99)
        {
            return 1;
        }
        pivot(e, l, n);
    }
    for (int i = 0; i < n + m; i++)
    {
        if (pos[i] == -1)
        {
            x[i] = 0;
        }
        else
        {
            x[i] = b[pos[i]];
        }
    }
    for (int i = 0; i < n; i++)
    {
        ansx[i] = x[i];
    }
    return 0;
}

class Main
{
public:
    void solve(std::istream &in, std::ostream &out)
    {
        int n;
        in >> n;
        vector<int> lol(n * n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int x;
                in >> x;
                lol[i * n + j] = x;
                c[i * n + j] = x;
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                a[4 * i][i * n + j] = 1;
                a[4 * i + 1][i * n + j] = -1;
            }
            b[4 * i] = 1;
            b[4 * i + 1] = -1;
        }
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                a[4 * j + 2][i * n + j] = 1;
                a[4 * j + 3][i * n + j] = -1;
            }
            b[4 * j + 2] = 1;
            b[4 * j + 3] = -1;
        }
        init(n * n, 4 * n);
        int kek = ::solve(n * n);
        int res = 0;
        for (int i = 0; i < n * n; i++)
        {
            if (ansx[i] >= 0.5)
            {
                res += lol[i];
            }
        }
        out << res << '\n';
        for (int i = 0; i < n * n; i++)
        {
            if (ansx[i] >= 0.5)
            {
                out << i / n + 1 << ' ' << i % n + 1 << '\n';
            }
        }
    }
};
