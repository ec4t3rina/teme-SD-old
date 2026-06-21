#include <iostream>

#define NMAX 100001

int aint[4*NMAX];
int v[NMAX];

int f(int x, int y) {
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

int query(int nod, int st, int dr, int qst, int qdr) {
    if (qst<=st && dr<=qdr) {
        return aint[nod];
    }

    int mijl, sonst, sondr, rez;

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    rez = 0;
    if (qst<=mijl) {
        rez = f(rez, query(sonst, st, mijl, qst, qdr));
    }
    if (qdr > mijl) {
        rez = f(rez, query(sondr, mijl+1, dr, qst, qdr));
    }

    return rez;
}

void update(int nod, int st, int dr, int poz, int val) {
    if (st==dr) {
        aint[nod] = val;
        return;
    }

    int mijl, sonst, sondr;

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

    return 0;

}
