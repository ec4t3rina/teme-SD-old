#include <iostream>
#include <vector>

using namespace std;

#define LOGMAX 16
#define NMAX 100001


int trie[NMAX*LOGMAX*4][2];
int triesize;

int a[NMAX];
int n;

int ord[NMAX];
int rez[NMAX];
int xp[NMAX];
int root[NMAX];

vector<int> elem[NMAX];

int sef[100001];

int find(int i) {
    if (sef[i] == i) {
        return i;
    }
    return sef[i] = find(sef[i]);
}

void insert(int &node, int k) {
    int i, bit, nod;

    if (node == 0) {
        node = triesize;
        triesize++;
    }

    nod = node;
    for (i=LOGMAX; i>=0; i--) {
        bit = (k>>i) & 1;
        if (trie[nod][bit]==0) {
            trie[nod][bit] = triesize;
            triesize++;
        }
        nod = trie[nod][bit];
    }
}
int checkmatch(int node, int k) {
    int i, bit, nod, rez;

    nod = node;
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

int uneste(int i, int j) {
    int sefi, sefj, aux, max, minimax;

    sefi = find(i);
    sefj = find(j);

    if (sefj == sefi) {
        return 0;
    }

    if (elem[sefi].size() < elem[sefj].size()) {
        aux = sefi;
        sefi = sefj;
        sefj = aux;
    }

    max = 0;
    for (i=0; i<elem[sefj].size(); i++) {
        minimax = checkmatch(root[sefi], elem[sefj][i]);
        if (minimax > max) {
            max = minimax;
        }
    }

    for (i=0; i<elem[sefj].size(); i++) {
        insert(root[sefi], elem[sefj][i]);
        elem[sefi].push_back(elem[sefj][i]);
    }

    elem[sefj].clear();
    sef[sefj] = sefi;

    return max;
}




int main() {
    int i, fullxor, max, xorpart, maxlocal;

    cin >> n;
    xp[0] = 0;
    for (i=1; i<=n; i++) {
        cin >> a[i];
        xp[i] = xp[i-1] ^ a[i];
    }

    for (i=1; i<=n; i++) {
        cin >> ord[i];
    }

    triesize = 1;
    for (i=0; i<=n; i++) {
        sef[i] = i;
        root[i] = 0;
        insert(root[i], xp[i]);
        elem[i].push_back(xp[i]);
    }

    max = 0;
    for (i=n; i>=1; i--) {
        rez[i] = max;

        maxlocal = uneste(ord[i]-1, ord[i]);

        if (maxlocal > max) {
            max = maxlocal;
        }
    }

    for (i=1; i<=n; i++) {
        cout << rez[i] << ' ';
    }

    return 0;
}