#include <iostream>

#define NMAX 100001
#define LOGMAX 20

int n;
int v[NMAX];
int t[NMAX][LOGMAX];
int lg2[NMAX];

int f(int x, int y) {
    if (x<y) {
        return x;
    }
    return y;
}

void init() {
    int i, lg, p2;

    lg = 0;
    lg2[1] = 0;
    p2 = 2;
    for (i=2; i<NMAX; i++) {
        if (i==p2) {
            p2*=2;
            lg++;
        }
        lg2[i] = lg;
    }

    for (i=0; i<n; i++) {
        t[i][0] = v[i];
    }

    for (lg=1; lg<LOGMAX; lg++) {
        for (i=0; i+(1<<lg)-1<n; i++) {
            t[i][lg] = f(t[i][lg-1], t[i+(1<<(lg-1))][lg-1]);
        }
    }
}

int query(int st, int dr) {
    int lg, lung, rez;

    lung = dr-st+1;
    lg = lg2[lung];

    rez = f(t[st][lg], t[dr-(1<<lg)+1][lg]);

    return rez;
}

int main() {

    return 0;

}