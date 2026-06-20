#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define NMAX 100001

int n;
int v[NMAX];
int aint[4*NMAX];
int lazy[4*NMAX];

static inline int f(int x, int y) {
    if (x>y) {
        return x;
    }
    return y;
}

inline void push(int nod, int sonst, int sondr) {
    if (lazy[nod] != 0) {
        aint[sonst] += lazy[nod];
        aint[sondr] += lazy[nod];
        lazy[sonst] += lazy[nod];
        lazy[sondr] += lazy[nod];
        lazy[nod] = 0;
    }
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

int query(int nod, int st, int dr, int qst, int qdr) {
    int mijl, sonst, sondr, rez;

    if (qst<=st && dr<=qdr) {
        return aint[nod];
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    push(nod, sonst, sondr);

    rez = 0;
    if (qst <= mijl) {
        rez = f(rez, query(sonst, st, mijl, qst, qdr));
    }
    if (qdr > mijl) {
        rez = f(rez, query(sondr, mijl+1, dr, qst, qdr));
    }

    return rez;
}

void update(int nod, int st, int dr, int a, int b, int val) {
    int mijl, sonst, sondr;

    if (a<=st && dr<=b) {
        aint[nod] += val;
        lazy[nod] += val;
        return;
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    push(nod, sonst, sondr);

    if (a <= mijl) {
        update(sonst, st, mijl, a, min(mijl, b), val);
    }
    if (b > mijl) {
        update(sondr, mijl+1, dr, max(a, mijl+1), b, val);
    }

    aint[nod] = f(aint[sonst], aint[sondr]);
}

int main() {
    ifstream fin("mit.in");
    ofstream fout("mit.out");

    int i, q, qq, op, st, dr, a, b, x;

    fin >> n >> q;
    for (i=0; i<n; i++) {
        fin >> v[i];
    }

    build(0, 0, n-1);

    for (qq=0; qq<q; qq++) {
        fin >> op;
        if (op==1) {
            fin >> st >> dr;
            fout << query(0, 0, n-1, st-1, dr-1) << '\n';
        } else {
            fin >> a >> b >> x;
            update(0, 0, n-1, a-1, b-1, x);
        }
    }

    fin.close();
    fout.close();
    return 0;
}