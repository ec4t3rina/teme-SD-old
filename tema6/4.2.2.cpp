#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 100001
#define MOD 9917

int n;
int v[NMAX];
int vv[NMAX];
int vvv[NMAX];
int aint[4*NMAX];

static inline int f(int x, int y) {
    return x+y;
}

int query(int nod, int st, int dr, int qst,int qdr) {
    int mijl, sonst, sondr, rez;

    if (qst<=st && dr<=qdr) {
        return aint[nod];
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    rez = 0;
    if (qst <= mijl) {
        rez = f(rez, query(sonst, st, mijl, qst, qdr))%MOD;
    }
    if (qdr > mijl) {
        rez = f(rez, query(sondr, mijl+1, dr, qst, qdr))%MOD;
    }

    return rez;
}

void update(int nod, int st, int dr, int poz) {
    int mijl, sonst, sondr;

    if (st==dr) {
        aint[nod]++;
        return;
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    if (poz <= mijl) {
        update(sonst, st, mijl, poz);
    } else {
        update(sondr, mijl+1, dr, poz);
    }

    aint[nod] = f(aint[sonst], aint[sondr]);
}

int main() {
    ifstream fin("inv.in");
    ofstream fout("inv.out");

    int i,  rez, st, dr, mijl, nrdis;

    fin >> n;
    for (i=0; i<n; i++) {
        fin >> v[i];
        vv[i] = v[i];
    }

    sort(vv, vv+n);

    vvv[0] = vv[0];
    nrdis = 1;
    for (i=1; i<n; i++) {
        if (vv[i]>vv[i-1]) {
            vvv[nrdis] = vv[i];
            nrdis++;
        }
    }

    for (i=0; i<n; i++) {
        st = 0;
        dr = nrdis;
        while (dr-st>1) {
            mijl = (st+dr)/2;
            if (vvv[mijl]>v[i]) {
                dr = mijl;
            } else {
                st = mijl;
            }
        }
        v[i] = st;
    }

    update(0, 0, nrdis-1, v[0]);
    rez = 0;
    for (i=1; i<n; i++) {
        update(0, 0, nrdis-1, v[i]);
        rez += query(0, 0, nrdis-1, v[i]+1, nrdis-1);
        rez %= MOD;
    }

    fout << rez;

    fin.close();
    fout.close();
    return 0;
}