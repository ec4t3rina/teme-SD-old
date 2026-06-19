#include <iostream>
#include <cmath>

using namespace std;

#define NMAX 100001
#define LOGMAX 17

int n;
int a[NMAX];
int t[NMAX][LOGMAX];

static inline int f(int x, int y) {
    if (x<y) {
        return x;
    }
    return y;
}

void build() {
    int i, lg;

    for (i=0; i<n; i++) {
        t[i][0] = a[i];
    }

    for (lg=1; lg<LOGMAX; lg++) {
        for (i=0; i+(1<<(lg))-1<n; i++) {
            t[i][lg] = f(t[i][lg-1], t[i+(1<<(lg-1))][lg-1]);
        }
    }
}

int query(int st, int dr) {
    int lg, lung, rez;

    lung = dr-st+1;
    lg = log2(lung);

    rez = f(t[st][lg], t[dr-(1<<lg)+1][lg]);

    return rez;
}

int main() {
    int i, q, qq, st, dr;

    cin >> n >> q;
    for (i=0; i<n; i++) {
        cin >> a[i];
    }

    build();

    for (i=0; i<n; i++) {
        cout << t[i][2] << ' ';
    }

    for (qq=0; qq<q; qq++) {
        cin >> st >> dr;
        cout << query(st, dr) << '\n';
    }

    return 0;
}