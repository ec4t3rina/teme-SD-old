#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define NMAX 100001

int n;
int v[NMAX];
int aint[4*NMAX];

static inline int f(int x, int y) {
    if (x>y) {
        return x;
    }
    return y;
}

void build(int nod, int st, int dr) {
    int mijl, sonst, sondr;

    if (st==dr) {
        aint[nod] = v[st];
        return;
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    build(sonst, st, mijl);
    build(sondr, mijl+1, dr);

    aint[nod] = f(aint[sonst], aint[sondr]);
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
        rez = f(rez, query(sonst, st, mijl, qst, qdr));
    }
    if (qdr > mijl) {
        rez = f(rez, query(sondr, mijl+1, dr, qst, qdr));
    }

    return rez;
}

void update(int nod, int st, int dr, int poz, int val) {
    int mijl, sonst, sondr;

    if (st==dr) {
        aint[nod] = val;
        return;
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    if (poz <= mijl) {
        update(sonst, st, mijl, poz, val);
    } else {
        update(sondr, mijl+1, dr, poz, val);
    }

    aint[nod] = f(aint[sonst], aint[sondr]);
}

int main() {
    ifstream fin("arbint.in");
    ofstream fout("arbint.out");

    int i, q, qq, op, st, dr, poz, x;

    fin >> n >> q;
    for (i=0; i<n; i++) {
        fin >> v[i];
    }

    build(0, 0, n-1);

    for (qq=0; qq<q; qq++) {
        fin >> op;
        if (op==0) {
            fin >> st >> dr;
            fout << query(0, 0, n-1, st-1, dr-1) << '\n';
        } else {
            fin >> poz >> x;
            update(0, 0, n-1, poz-1, x);
        }
    }

    fin.close();
    fout.close();
    return 0;
}