#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <ranges>

static inline int parent(int i) {
    return (i-1)/2;
}
static inline int left(int i) {
    return i*2+1;
}
static inline int right(int i) {
    return i*2+2;
}

void downheap(std::vector<int>& a, int heapsize, int nod) {
    int aux, st, dr, maxi;

    maxi = nod;
    do {
        nod = maxi; 
        st = left(nod);
        dr = right(nod);
        maxi = nod;

        if (st < heapsize && a[st] > a[maxi]) {
            maxi = st;
        }
        if (dr < heapsize && a[dr] > a[maxi]) {
            maxi = dr;
        }

        if (maxi != nod) {
            aux = a[maxi];
            a[maxi] = a[nod];
            a[nod] = aux;
            

        }
    } while (maxi!=nod);
}

void build(std::vector<int>& a) {
    int i;
    for (i = a.size()/2 - 1; i >= 0; --i) {
        downheap(a, a.size(), i);
    }
}

void heap_sort(std::vector<int>& a) {
    int aux, heapsize, i;

    build(a);
    heapsize = a.size();

    for (i=heapsize-1; i>=0; i--) {
        aux = a[0];
        a[0] = a[i];
        a[i] = aux;

        downheap(a, i, 0);
    }
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
    heap_sort(a);
    assert(std::ranges::is_sorted(a));

    /*
    for (int& x : a) {
        std::cout << x << ' ';
    }
    */

    return 0;
}