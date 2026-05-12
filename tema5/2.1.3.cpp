#include <iostream>

using namespace std;

#define LOGMAX 16
#define NMAX 100001

int trie[NMAX*LOGMAX][2];
int triesize;

int a[NMAX];
int n;

void init() {
    triesize = 1;
}

int checkmatch(int k) {
    int i, bit, nod, rez;

    nod = 0;
    rez = 0;
    for (i=LOGMAX; i>=0; i--) {
        bit = (k>>i) & 1;

        if (trie[nod][1-bit]!=0) {
            rez += (1<<i);
            nod = trie[nod][1-bit];
        } else {
            nod = trie[nod][bit];
        }

    }

    return rez;
}

void insert(int k) {
    int i, bit, nod;

    nod = 0;
    for (i=LOGMAX; i>=0; i--) {
        bit = (k>>i) & 1;

        if (trie[nod][bit]==0) {
            trie[nod][bit] = triesize;
            triesize++;
        }
        nod = trie[nod][bit];
    }
}

int main() {
    int i, fullxor, max, xorpart;

    init();
    insert(0);

    cin >> n;
    for (i=0; i<n; i++) {
        cin >> a[i];
    }

    fullxor = 0;
    max = 0;
    for (i=0; i<n; i++) {
        fullxor = fullxor ^ a[i];
        xorpart = checkmatch(fullxor);
        insert(fullxor);

        if (xorpart > max) {
            max = xorpart;
        }
    }

    cout << max << '\n';

    return 0;
}