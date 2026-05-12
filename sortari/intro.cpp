#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <cstdlib>
#include <ctime>

const int NRMIC = 32;

static inline int parent(int i) {
    return (i-1)/2;
}
static inline int left(int i) {
    return i*2+1;
}
static inline int right(int i) {
    return i*2+2;
}

void downheap(std::vector<int>& a, int stsync, int heapsize, int nod) {
    int aux, st, dr, maxi;

    maxi = nod;
    do {
        nod = maxi; 
        st = left(nod);
        dr = right(nod);
        maxi = nod;

        if (st < heapsize && a[st+stsync] > a[maxi+stsync]) {
            maxi = st;
        }
        if (dr < heapsize && a[dr+stsync] > a[maxi+stsync]) {
            maxi = dr;
        }

        if (maxi != nod) {
            aux = a[maxi+stsync];
            a[maxi+stsync] = a[nod+stsync];
            a[nod+stsync] = aux;
        }
    } while (maxi != nod);
}

void build(std::vector<int>& a, int sync, int heapsize) {
    int i;
    for (i=heapsize/2-1; i>=0; i--) {
        downheap(a, sync, heapsize, i);
    }
}

void heap_sort(std::vector<int>& a, int st, int dr) {
    int aux, heapsize, i;

    heapsize = dr-st+1;
    if (heapsize<=1) {
        return;
    }
    build(a, st, heapsize);

    for (i=heapsize-1; i>=0; i--) {
        aux = a[st];
        a[st] = a[st+i];
        a[st+i] = aux;

        downheap(a, st, i, 0);
    }
}

void insertion_sort(std::vector<int>& a, int st, int dr) {
    int i, key, j;
    for (i=st+1; i<=dr; i++) {
        key = a[i];
        j = i-1;
        while (j>=st && a[j]>key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void introsort(std::vector<int>& a, int left, int right, int maxdepth) {
    int lung, st, dr, pivot, aux, mijl;

    st = left;
    dr = right;
    lung = dr-st+1;

    if (lung <= NRMIC) {
        insertion_sort(a, left, right);
        return;
    }

    if (maxdepth == 0) {
        heap_sort(a, left, right);
        return;
    }

    mijl = st + (dr - st) / 2;
    if (a[st] > a[mijl]) 
        std::swap(a[st], a[mijl]);
    if (a[st] > a[dr]) 
        std::swap(a[st], a[dr]);
    if (a[mijl] > a[dr]) 
        std::swap(a[mijl], a[dr]);

    pivot = a[mijl];

    while (st <= dr) {
        while (a[st] < pivot) {
            st++;
        }
        while (a[dr] > pivot) {
            dr--;
        }
        if (st <= dr) {
            aux = a[st];
            a[st] = a[dr];
            a[dr] = aux;
            st++;
            dr--;
        }
    }

    if (left < dr) {
        introsort(a, left, dr, maxdepth-1);
    }
    if (st < right) {
        introsort(a, st, right, maxdepth-1);
    }
}
void intro_sort(std::vector<int>& a) {
    int maxdepth, aux;

    if (a.size()==0) {
        return;
    }

    std::srand(std::time(nullptr));

    maxdepth = 1;
    aux = a.size();
    while (aux>0) {
        aux/=2;
        maxdepth++;
    }
    maxdepth*=2;
    introsort(a, 0, a.size()-1, maxdepth);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& x : a) {
        std::cin >> x;
    }
    intro_sort(a);
    assert(std::ranges::is_sorted(a));

    return 0;
}