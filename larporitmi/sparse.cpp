#include <iostream>

#define NMAX 100001
#define LOGMAX 20

int n;
int v[NMAX];
int t[NMAX][LOGMAX];
int lg2[NMAX];

int f(int x, int y) {
    return x+y;
}

void init() {
    int i, lg, p2;

    lg = 0;
    p2 = 2;
    for (i=2; i<NMAX; i++) {
        if (i>=p2) {
            lg++;
            p2*=2;
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
    int lg, lung, p2, rez;

    lung = dr-st+1;

    rez = 0;
    do {
        lg = lg2[lung];
        rez = f(rez, t[st][lg]);
        lung -= (1<<lg);
        st += (1<<lg);
    } while (lung>0);

    return rez;
}

int main() {

    return 0;

}