#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100001

int triesize;
vector<int> children[NMAX];
vector<int> trie[NMAX];
int nrcuv[NMAX];

void init() {
    triesize = 1;
}

void insert(const string& s) {
    int n, i, nod, j;

    n = s.size();
    nod = 0;
    for (i=0; i<n; i++) {
        j = 0;
        while (j<children[nod].size() && trie[nod][j]!=s[i]) {
            j++;
        }
        if (j<children[nod].size()) {
            nod = children[nod][j];
        } else {
            children[nod].push_back(triesize);
            trie[nod].push_back(s[i]);
            nod = triesize;
            triesize++;
        }
        nrcuv[nod]++;
    }
}

void erase(const string& s) {
    int i, j, n, nod, ok;

    n = s.size();
    ok = 0;
    nod = 0;
    for (i=0; i<n && ok==0; i++) {
        j = 0;
        while (j<children[nod].size() && trie[nod][j]!=s[i]) {
            j++;
        }
        if (nrcuv[children[nod][j]]==1) {
            trie[nod].erase(trie[nod].begin() + j);
            children[nod].erase(children[nod].begin() + j);
            ok = 1;
        } else {
            nod = children[nod][j];
            nrcuv[nod]--;
        }
    }
}

int main() {

    return 0;
}