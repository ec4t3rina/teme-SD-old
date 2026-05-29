#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>

#define NMAX 100001
#define MOD 1000000009

using namespace std;

long long int v[NMAX];
int n;

long long int a1, b1;
vector<long long int> h1[NMAX];

long long int a2[NMAX];
long long int b2[NMAX];
int m2[NMAX];
vector<long long int> h2[NMAX];

long long int hasheaza(long long int val, long long int a, long long int b, int m) {
    long long int h;
    h = ((a*val+b)%MOD);
    if (h < 0) {
        h += MOD;
    }
    return h % m;
}

void init(int n) {
    int i, j, idx, lung, ok;
    long long int val, h;

    a1 = rand()%MOD;
    b1 = (1LL*rand()*rand()%MOD)%MOD;

    for (i=0; i<n; i++) {
        idx = hasheaza(v[i], a1, b1, n);
        h1[idx].push_back(v[i]);
    }

    for (i=0; i<n; i++) {
        lung = h1[i].size();
        if (lung == 0) {
            m2[i] = 0;
            h2[i].assign(m2[i], -1);
        } else {
            m2[i] = lung*lung;

            ok = 0;
            while (ok == 0) {
                a2[i] = rand()%MOD;
                b2[i] = (1LL*rand()*rand()%MOD)%MOD;

                h2[i].assign(m2[i], -1);
                ok = 1;
                for (j=0; j<lung; j++) {
                    val = h1[i][j];
                    h = hasheaza(val, a2[i], b2[i], m2[i]);
                    if (h2[i][h] != -1) {
                        ok = 0;
                        break;
                    } else {
                        h2[i][h] = val;
                    }
                }
            }
        }
    }
}

int exista(long long int x) {
    int idx1, idx2;

    idx1 = hasheaza(x, a1, b1, n);
    if (m2[idx1] == 0) {
        return 0;
    }
    idx2 = hasheaza(x, a2[idx1], b2[idx1], m2[idx1]);
    if (h2[idx1][idx2] == x) {
        return 1;
    }

    return 0;
}


int main() {
    int i, nrq, x, rez;

    cin >> n;
    for (i=0; i<n; i++) {
        cin >> v[i];
    }

    init(n);

    cin >> nrq;
    for (i=0; i<nrq; i++) {
        cin >> x;
        if (exista(x)) {
            rez = 1;
        } else {
            rez = 0;
        }
        cout << rez << '\n';
    }

    return 0;
}
