#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>
#include <cstdlib>
#include <ctime>
#include <random>


void quick_sort_rec(std::vector<int>& a, int st, int dr) {
    if (st >= dr) return;

    int mijl;

    mijl = st + (dr - st) / 2;

    if (a[st] > a[mijl]) 
        std::swap(a[st], a[mijl]);
    if (a[st] > a[dr]) 
        std::swap(a[st], a[dr]);
    if (a[mijl] > a[dr]) 
        std::swap(a[mijl], a[dr]);
    
    int pivot = a[mijl];

    int s = st;
    int d = dr;

    while (s <= d) {
        while (a[s] < pivot)
            s++;
        while (a[d] > pivot)
            d--;

        if (s <= d) {
            std::swap(a[s], a[d]);
            s++;
            d--;
        }
    }

    if (st < d)
        quick_sort_rec(a, st, d);
    if (s < dr)
        quick_sort_rec(a, s, dr);
}

void quick_sort(std::vector<int>& a) {
    if (a.empty()) return;
    quick_sort_rec(a, 0, a.size() - 1);
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
    quick_sort(a);
    assert(std::ranges::is_sorted(a));

    return 0;
}