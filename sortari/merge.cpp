#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ranges>

void merge(std::vector<int>& a, std::vector<int>& tmp, int st, int mij, int dr) {
    int i = st;
    int j = mij + 1;
    int k = st;
    int p;

    while (i <= mij && j <= dr) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }

    while (i <= mij)
        tmp[k++] = a[i++];
    while (j <= dr)
        tmp[k++] = a[j++];
}

void merge_sort_rec(std::vector<int>& a, std::vector<int>& tmp, int st, int dr) {
    if (st < dr) {
        int mij = st + (dr - st) / 2;
        merge_sort_rec(tmp, a, st, mij);
        merge_sort_rec(tmp, a, mij + 1, dr);
        merge(a, tmp, st, mij, dr);
    }
}

void merge_sort(std::vector<int>& a) {
    if (a.empty()) return;

    std::vector<int> tmp = a;

    merge_sort_rec(tmp, a, 0, a.size() - 1);
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
    merge_sort(a);
    assert(std::ranges::is_sorted(a));
    return 0;
}