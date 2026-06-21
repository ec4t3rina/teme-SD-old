#include <iostream>

#define NMAX 100001
#define SQMAX 317

int v[NMAX];
int batog[SQMAX];
int bonus[SQMAX];
int n, sq;

void build() {
    int i;
    for (i=0; i<n; i++) {
        if (v[i]>batog[i/sq]) {
            batog[i/sq] = v[i];
        }
    }
}

void update(int st, int dr, int val) {
    int prim, ultim, i;

    prim = (st+sq-1)/sq*sq;
    ultim = dr/sq*sq;

    while (st<prim && st<=dr) {
        v[st] += val;
        if (batog[(prim-1)/sq] < v[st]) {
            batog[(prim-1)/sq] = v[st];
        }
        st++;
    }

    while (st<=dr && dr>=ultim) {
        v[dr]+=val;
        if (batog[ultim/sq] < v[dr]) {
            batog[ultim/sq] = v[dr];
        }
        dr--;
    }

    prim/=sq;
    ultim/=sq;
    for (i=prim; i<ultim; i++) {
        bonus[i]+=val;
    }
}

int query(int st, int dr) {
    int rez, prim, ultim, i;

    prim = (st+sq-1)/sq*sq;
    ultim = dr/sq*sq;
    rez = 0;

    while(st<prim && st<=dr) {
        if (rez < v[st]+bonus[(prim-1)/sq]) {
            rez = v[st]+bonus[(prim-1)/sq];
        }
        st++;
    }

    while (dr>=ultim && st<=dr) {
        if (rez < v[dr]+bonus[ultim/sq]) {
            rez = v[dr]+bonus[ultim/sq];
        }
        dr--;
    }

    prim/=sq;
    ultim/=sq;
    for (i=prim; i<ultim; i++) {
        if (rez < batog[i]+bonus[i]) {
            rez = batog[i]+bonus[i];
        }
    }

    return rez;
}


int main() {

    return 0;

}