#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ranges>

#define BAZA 256


void counting_sort_for_radix(std::vector<int>& a, std::vector<int>& output, int shift) {
    int n = a.size();
    int count[BAZA] = {0};
    for (int i = 0; i < n; i++)
        count[(a[i] >> shift) & (BAZA - 1)]++;
    for (int i = 1; i < BAZA; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] >> shift) & (BAZA - 1)] - 1] = a[i];
        count[(a[i] >> shift) & (BAZA - 1)]--;
    }
}
void radix_sort(std::vector<int>& a) {
    if (a.empty()) return;
    int max_val = *std::max_element(a.begin(), a.end());
    std::vector<int> output(a.size());
    for (int shift = 0; max_val >> shift > 0; shift += 8) {
        counting_sort_for_radix(a, output, shift);
        a.swap(output);
        if ((max_val >> shift) < 256) {
            break;
        }
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
    radix_sort(a);
    assert(std::ranges::is_sorted(a));

    return 0;
}