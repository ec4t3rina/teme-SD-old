#include <iostream>

#define NMAX 100001

int n;
int sef[NMAX];

void init() {
    int i;
    for (i=0; i<n; i++) {
        sef[i] = i;
    }
}

int find(int i) {
    if (sef[i]==i) {
        return i;
    }
    return sef[i] = find(sef[i]);
}

void uneste(int i, int j) {
    int sefi, sefj;

    sefi = find(i);
    sefj = find(j);

    if (sefi==sefj) {
        return;
    }

    sef[sefj] = sefi;
}

int main() {

    return 0;

}