#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define NMAX 501
#define LOGMAX 9

int n;
int a[NMAX][NMAX];
int t[NMAX][NMAX][LOGMAX];

static inline int f(int x, int y, int z, int w) {
    int max = 0;
    if (max < x) {
        max = x;
    }
    if (max < y) {
        max = y;
    }
    if (max < z) {
        max = z;
    }
    if (max < w) {
        max = w;
    }
    return max;
}

void build() {
    int lg, l, c;

    for (l=0; l<n; l++) {
        for (c=0; c<n; c++) {
            t[l][c][0] = a[l][c];
        }
    }

    for (lg=1; lg<LOGMAX; lg++) {
        for (l=0; l+(1<<lg)-1<n; l++) {
            for (c=0; c+(1<<lg)-1<n; c++) {
                t[l][c][lg] = f(t[l][c][lg-1], t[l+(1<<(lg-1))][c][lg-1], t[l][c+(1<<(lg-1))][lg-1], t[l+(1<<(lg-1))][c+(1<<(lg-1))][lg-1]);
            }
        }
    }
}

int query(int l, int c, int k) {
    int lg, lung, rez, ll, cc;

    lung = k;
    lg = log2(lung);
    ll = l+k-1;
    cc = c+k-1;
    rez = f(t[l][c][lg], t[ll-(1<<lg)+1][c][lg], t[l][cc-(1<<lg)+1][lg], t[ll-(1<<lg)+1][cc-(1<<lg)+1][lg]);

    return rez;
}

int main() {
    ifstream fin("plantatie.in");
    ofstream fout("plantatie.out");
    int l, c, q, qq, k;

    fin >> n >> q;
    for (l=0; l<n; l++) {
        for (c=0; c<n; c++) {
            fin >> a[l][c];
        }
    }

    build();

    for (qq=0; qq<q; qq++) {
        fin >> l >> c >> k;
        fout << query(l-1, c-1, k) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}