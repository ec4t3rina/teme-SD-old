#include <iostream>
#include <vector>
#include <algorithm>

#define NMAX 150001

struct node {
    int cand = 0;
    int bm = 0;
};

node aint[4*NMAX];

node f(node x, node y) {
    node rez;
    if (x.cand == y.cand) {
        rez.cand = x.cand;
        rez.bm = x.bm + y.bm;
    } else {
        if (x.bm > y.bm) {
            rez.cand = x.cand;
            rez.bm = x.bm-y.bm;
        } else {
            rez.cand = y.cand;
            rez.bm = y.bm-x.bm;
        }
    }
    return rez;
}

void build(int nod, int st, int dr, const std::vector<int>& a) {
    if (st==dr) {
        aint[nod].cand = a[st];
        aint[nod].bm = 1;
        return;
    }

    int mijl, sonst, sondr;

    mijl = (st+dr)/2;
    sonst = nod + 1;
    sondr = nod + 2*(mijl-st+1);

    build(sonst, st, mijl, a);
    build(sondr, mijl+1, dr, a);

    aint[nod] = f(aint[sonst], aint[sondr]);
}

node query(int nod, int st, int dr, int qst, int qdr) {
    if (qst<=st && dr<=qdr) {
        return aint[nod];
    }

    int mijl, sonst, sondr;

    mijl = (st+dr)/2;
    sonst = nod + 1;
    sondr = nod + 2*(mijl-st+1);

    node rez;
    if (qst <= mijl) {
        rez = f(rez, query(sonst, st, mijl, qst, qdr));
    }
    if (qdr > mijl) {
        rez = f(rez, query(sonst, mijl+1, dr, qst, qdr));
    }

    return rez;
}

std::vector <int> solve_majority_queries (std::vector <int> a, std::vector <int> l, std::vector <int> r) {
    std::vector<int> rez;
    std::vector<std::vector<int>> poz(NMAX);
    int n, q, qq, i, lung, candi, cnt;

    n = a.size();
    q = l.size();

    for (i=0; i<n; i++) {
        poz[a[i]].push_back(i);
    }

    build(0, 0, n-1, a);

    for (qq=0; qq<q; qq++) {
        lung = r[qq]-l[qq]+1;
        candi = query(0, 0, n-1, l[qq], r[qq]).cand;
        auto idxst = std::lower_bound(poz[candi].begin(), poz[candi].end(), l[qq]);
        auto idxdr = std::upper_bound(poz[candi].begin(), poz[candi].end(), r[qq]);

        cnt = idxdr-idxst;

        if (cnt > lung/2) {
            rez.push_back(candi);
        } else {
            rez.push_back(-1);
        }
    }

    return rez;
}

int main() {

    return 0;
}