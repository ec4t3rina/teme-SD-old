#include <iostream>
#include <vector>

using namespace std;

#define NMAX 250002

vector<int> children[NMAX];
vector<char> trie[NMAX];
int nrcuv[NMAX];
int triesize;

void insert(const string& s) {
    int n, i, j, nod;

    nod = 0;
    n = s.length();
    for (i=0; i<n; i++) {
        j = 0;
        while (j<trie[nod].size() && trie[nod][j] != s[i]) {
            j++;
        }
        if (j < trie[nod].size()) {
            nod = children[nod][j];
        } else {
            children[nod].push_back(triesize);
            triesize++;
            trie[nod].push_back(s[i]);

            nod = children[nod].back();
        }

        nrcuv[nod]++;
    }
}

void erase(const string& s) {
    int n, i, j, nod, last, ok;

    nod = 0;
    n = s.length();
    ok = 0;
    for (i=0; i<n && ok==0; i++) {
        j = 0;
        while (j<trie[nod].size() && trie[nod][j] != s[i]) {
            j++;
        }
        if (nrcuv[children[nod][j]] == 1) {
            children[nod].erase(children[nod].begin() + j);
            trie[nod].erase(trie[nod].begin() + j);
            ok = 1;
        } else {
            nod = children[nod][j];
            nrcuv[nod]--;
        }
    }
}

int count(const string& s) {
    int n, i, j, nod, ok;

    nod = 0;
    n = s.length();
    ok = 0;
    for (i=0; i<n && ok==0; i++) {
        j = 0;
        while (j<trie[nod].size() && trie[nod][j] != s[i]) {
            j++;
        }
        if (j<trie[nod].size()) {
            nod = children[nod][j];
        } else {
            ok = 1;
        }
    }

    if (ok==1) {
        return 0;
    }

    return nrcuv[nod];
}

int longest_prefix(const string& s) {
    int n, i, j, nod, lung, ok;

    nod = 0;
    n = s.length();
    ok = 0;
    lung = 0;
    for (i=0; i<n && ok==0; i++) {
        j = 0;
        while (j<trie[nod].size() && trie[nod][j] != s[i]) {
            j++;
        }
        if (j<trie[nod].size()) {
            nod = children[nod][j];
            lung++;
        } else {
            ok = 1;
        }
    }

    return lung;
}

void init() {
    triesize = 1;
}

int main() {

    init();

    return 0;
}