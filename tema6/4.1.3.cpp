#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

#define NMAX 250001
#define LOGMAX 25

int n;
int pops[NMAX];
int t[NMAX][LOGMAX];

void build() {
    int i, lg;

    for (i=1; i<=n; i++) {
        t[i][0] = pops[i];
    }

    for (lg=1; lg<LOGMAX; lg++) {
        for (i=1; i<=n; i++) {
            t[i][lg] = t[t[i][lg-1]][lg-1];
        }
    }
}

int query(int k, int dist) {
    int lg, rez;

    lg = log2(dist);
    rez = k;
    do {
        lg = log2(dist);
        rez = t[rez][lg];
        dist = dist-(1<<lg);
    } while (dist>0);

    return rez;
}

int main() {
    ifstream fin("stramosi.in");
    ofstream fout("stramosi.out");

    int i, q, qq, k, dist, tata;

    fin >> n >> q;
    for (i=1; i<=n; i++) {
        fin >> tata;
        pops[i] = tata;
    }

    build();

    for (qq=0; qq<q; qq++) {
        fin >> k >> dist;
        fout << query(k, dist) << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}