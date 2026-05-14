/// link submisie accepted: https://codeforces.com/gym/104009/submission/374554601

#include <iostream>
#include <vector>

using namespace std;

#define QMAX 500002
#define ALFAMAX 27
#define KMAX 11

int q, k;

int qop[QMAX];
int qval[QMAX];

int parent[QMAX];
int trie[QMAX][ALFAMAX];
int triesize;

int id[QMAX];
int f[QMAX];

int aint[4*QMAX][KMAX];
int lenaint[4*QMAX];
int knod;
int treesize;

int limst[QMAX];
int limdr[QMAX];
int poz[QMAX];
int idx;

vector<int> rec;
vector<int> reclit;

struct sret {
    int lung;
    int val[KMAX];
};

static inline int left(int i) {
    return i*2+1;
}
static inline int right(int i) {
    return i*2+2;
}

void update(int nod, int lft, int rght, int p, int word_id) {
    int mijl, st, dr, i, j, idst, iddr;

    if (lft == rght) {
        lenaint[nod] = 1;
        aint[nod][0] = word_id;
        return;
    }
    mijl = (lft+rght)/2;
    st = left(nod);
    dr = right(nod);

    if (p <= mijl) {
        update(st, lft, mijl, p, word_id);
    } else {
        update(dr, mijl+1, rght, p, word_id);
    }

    lenaint[nod] = 0;
    i = 0;
    j = 0;
    while (lenaint[nod] < k && (i < lenaint[st] || j < lenaint[dr])) {
        if (i == lenaint[st]) {
            aint[nod][lenaint[nod]] = aint[dr][j];
            lenaint[nod]++;
            j++;
        } else {
            if (j == lenaint[dr]) {
                aint[nod][lenaint[nod]] = aint[st][i];
                lenaint[nod]++;
                i++;
            } else {
                idst = aint[st][i];
                iddr = aint[dr][j];

                if (f[idst] > f[iddr] || (f[idst] == f[iddr] && idst < iddr)) {
                    aint[nod][lenaint[nod]] = idst;
                    lenaint[nod]++;
                    i++;
                } else {
                    aint[nod][lenaint[nod]] = iddr;
                    lenaint[nod]++;
                    j++;
                }
            }
        }
    }
}

sret query(int nod, int lft, int rght, int qlft, int qrght) {
    sret rez, rezst, rezdr;
    int mijl, st, dr, i, j, idst, iddr;

    rez.lung = 0;
    if (qlft > rght || qrght < lft || qlft > qrght) {
        return rez;
    }

    if (qlft <= lft && rght <= qrght) {
        rez.lung = lenaint[nod];
        for (i=0; i<rez.lung; i++) {
            rez.val[i] = aint[nod][i];
        }
        return rez;
    }

    st = left(nod);
    dr = right(nod);
    mijl = (lft+rght)/2;

    rezst = query(st, lft, mijl, qlft, qrght);
    rezdr = query(dr, mijl+1, rght, qlft, qrght);

    i = 0;
    j = 0;
    while (rez.lung<k && (i < rezst.lung || j < rezdr.lung)) {
        if (i == rezst.lung) {
            rez.val[rez.lung] = rezdr.val[j];
            rez.lung++;
            j++;
        } else if (j == rezdr.lung) {
            rez.val[rez.lung] = rezst.val[i];
            rez.lung++;
            i++;
        } else {
            idst = rezst.val[i];
            iddr = rezdr.val[j];

            if (f[idst] > f[iddr] || (f[idst] == f[iddr] && idst < iddr)) {
                rez.val[rez.lung] = idst;
                rez.lung++;
                i++;
            } else {
                rez.val[rez.lung] = iddr;
                rez.lung++;
                j++;
            }
        }
    }
    return rez;
}

int main() {
    int op, qq, nod, i;
    char lit;
    sret rez;

    cin >> q >> k;
    triesize = 1;
    nod = 0;
    for(i=0; i<QMAX; i++) {
        id[i] = -1;
    }
    for (qq=0; qq<q; qq++) {
        cin >> op;
        qop[qq] = op;
        if (op==1) {
            cin >> lit;
            qval[qq] = lit;

            lit = int(lit-'a');
            if (trie[nod][lit]==0) {
                parent[triesize] = nod;
                trie[nod][lit] = triesize;
                triesize++;
            }
            nod = trie[nod][lit];


        } else if (op==2) {
            nod = 0;
        } else if (op==3) {
            nod = parent[nod];
        } else {
            if (id[nod]==-1) {
                id[nod] = qq;
            }
        }
    }

    idx = 0;
    limst[0] = idx;
    if (id[0] != -1) {
        poz[id[0]] = idx;
        idx++;
    }
    rec.push_back(0);
    reclit.push_back(0);
    while (rec.size()>0) {
        nod = rec.back();
        lit = reclit.back();

        if (lit<ALFAMAX-1) {
            reclit.back()++;

            if (trie[nod][lit]!=0) {
                limst[trie[nod][lit]] = idx;
                if (id[trie[nod][lit]]!=-1) {
                    poz[id[trie[nod][lit]]] = idx;
                    idx++;
                }
                rec.push_back(trie[nod][lit]);
                reclit.push_back(0);
            }
        } else {
            limdr[nod] = idx-1;
            rec.pop_back();
            reclit.pop_back();
        }
    }
    treesize = idx;

    nod = 0;
    for (qq=0; qq<q; qq++) {
        op = qop[qq];

        if (op == 1) {
            lit = int(qval[qq]-'a');
            nod = trie[nod][lit];

            if (treesize==0 || limst[nod]>limdr[nod]) {
                cout << -1 << '\n';
            } else {
                rez = query(0, 0, treesize-1, limst[nod], limdr[nod]);
                if (rez.lung == 0) {
                    cout << -1 << '\n';
                } else {
                    for (i=0; i<rez.lung; i++) {
                        cout << rez.val[i];
                        if (i < rez.lung-1) {
                            cout << " ";
                        }
                    }
                    cout << '\n';
                }
            }
        } else if (op == 2) {
            nod = 0;
        } else if (op == 3) {
            nod = parent[nod];
        } else {
            f[id[nod]]++;
            update(0, 0, treesize-1, poz[id[nod]], id[nod]);
        }
    }

    return 0;
}