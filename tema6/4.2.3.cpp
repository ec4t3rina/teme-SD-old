#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 200001

int n;
long long int v[NMAX];

struct node {
    long long int sum = 0;
    long long int max = 0;
    long long int maxst = 0;
    long long int maxdr = 0;
};

node aint[4*NMAX];

void f(int nod, int sonst, int sondr) {
    aint[nod].sum = aint[sonst].sum + aint[sondr].sum;
    aint[nod].max = max(max(aint[sonst].max, aint[sondr].max), aint[sonst].maxdr+aint[sondr].maxst);
    aint[nod].maxst = max(aint[sonst].maxst, aint[sonst].sum+aint[sondr].maxst);
    aint[nod].maxdr = max(aint[sondr].maxdr, aint[sondr].sum+aint[sonst].maxdr);
}

void build(int nod, int st, int dr) {
    int mijl, sonst, sondr;

    if (st==dr) {
        aint[nod].sum = v[st];
        aint[nod].max = v[st];
        aint[nod].maxst = v[st];
        aint[nod].maxdr = v[st];
        return;
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    build(sonst, st, mijl);
    build(sondr, mijl+1, dr);

    f(nod, sonst, sondr);
}

node query(int nod, int st, int dr, int qst,int qdr) {
    int mijl, sonst, sondr;
    node rez, rezst, rezdr;

    if (qst<=st && dr<=qdr) {
        return aint[nod];
    }

    mijl = (st+dr)/2;
    sonst = nod+1;
    sondr = nod + 2*(mijl-st+1);

    if (qst <= mijl) {
        rezst = query(sonst, st, mijl, qst, qdr);
    }
    if (qdr > mijl) {
        rezdr = query(sondr, mijl+1, dr, qst, qdr);
    }

    rez.sum = rezst.sum + rezdr.sum;
    rez.max = max(max(rezst.max, rezdr.max), rezdr.maxst+rezst.maxdr);
    rez.maxst = max(rezst.maxst, rezst.sum+rezdr.maxst);
    rez.maxdr = max(rezdr.maxdr, rezdr.sum+rezst.maxdr);

    return rez;
}

void update(int nod, int st, int dr, int poz, int val) {
    int mijl, sonst, sondr;

    if (st==dr) {
        aint[nod].sum = val;
        aint[nod].max = val;
        aint[nod].maxst = val;
        aint[nod].maxdr = val;
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

    f(nod, sonst, sondr);
}

int main() {
    ifstream fin("maxq.in");
    ofstream fout("maxq.out");

    int i, q, qq, op, st, dr, poz;
    long long int val;

    fin >> n;
    for (i=0; i<n; i++) {
        fin >> v[i];
    }

    build(0, 0, n-1);

    fin >> q;
    for (qq=0; qq<q; qq++) {
        fin >> op;
        if (op==1) {
            fin >> st >> dr;
            fout << max(0LL, query(0, 0, n-1, st, dr).max) << '\n';
        } else {
            fin >> poz >> val;
            update(0, 0, n-1, poz, val);
        }
    }

    fin.close();
    fout.close();
    return 0;
}