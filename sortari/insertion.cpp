#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ranges>

void insertion_sort(std::vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int cheie = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > cheie) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = cheie;
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
    insertion_sort(a);
    assert(std::ranges::is_sorted(a));
    return 0;
}