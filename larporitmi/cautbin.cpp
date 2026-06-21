#include <iostream>
#include <vector>
#include <algorithm>

#define NMAX 100001

int n;
std::vector<int> v;

//// var clasica
int cautbin(int e) {
    int st, dr, mijl;

    st = 0;
    dr = n;
    while (dr-st>1) {
        mijl = (st+dr)/2;
        if (v[mijl]>e) {
            dr = mijl;
        } else {
            st = mijl;
        }
    }
    return st;
}


/// var cu vectori
int cautbinvec(int e) {
    int dist, idx, nrap;

    /// primul elem >= cu val:
    auto idxst = std::lower_bound(v.begin(), v.end(), e);
    /// primul elem > val:
    auto idxdr = std::upper_bound(v.begin(), v.end(), e);

    idx = idxst - v.begin();

    /// ca sa verifici daca exista in vector:
    if (idxst != v.end() && *idxst == e) {
        ///....
    }

    nrap = idxdr-idxst;
}

int manual_lb(int e) {
    int st, dr, mijl;
    st = -1;
    dr = n;
    while (dr-st>1) {
        mijl = (st+dr)/2;
        if (v[mijl]>=e) {
            dr = mijl;
        } else {
            st = mijl;
        }
    }
    return dr;
}

int manual_ub(int e) {
    int st, dr, mijl;

    st = -1;
    dr = n;
    while (dr-st>1) {
        mijl = (st+dr)/2;
        if (v[mijl]>e) {
            dr = mijl;
        } else {
            st = mijl;
        }
    }

    return dr;
}

int main() {

    return 0;
}