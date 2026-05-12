#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>


void gnome_sort(std::vector<int>& a) {
    int n, idx, aux, nextidx;

    n = a.size();
    if (n <= 1) {
        return;
    }

    idx = 1;
    nextidx = 2;
    while (idx < n) {
        if (idx>0 && a[idx-1]>a[idx]) {
            aux = a[idx-1];
            a[idx-1] = a[idx];
            a[idx] = aux;
            idx--;

            if (idx == 0) {
                idx = nextidx;
                nextidx++;
            }
        } else {
            idx = nextidx;
            nextidx++;
        }
    }

    return;
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
    gnome_sort(a);
    assert(std::ranges::is_sorted(a));

    return 0;
}