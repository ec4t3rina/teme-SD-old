#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <algorithm>
#include <ranges>

struct card {
    int val;
    int idx;

    bool operator<(const card& other) const {
        return val > other.val;
    }
};

void patience_sort(std::vector<int>& a) {
    int subcarte, n;

    if (a.empty()!=0) {
        return;
    }
    n = a.size();
    
    std::vector<int> piletops; 
    std::vector<int> sub(n, -1); 
    
    int i, j, st, dr, mijl;
    card now;

    piletops.push_back(0);

    for (i = 1; i < n; i++) {
        st = 0;
        dr = piletops.size();
        j = dr;
        
        while (dr - st > 1) {
            mijl = (st + dr)/2;
            if (a[piletops[mijl]] > a[i]) {
                dr = mijl;
            } else {
                st = mijl;
            }
        }
        if (a[piletops[st]] > a[i]) {
            j = st;
        }

        if (j < piletops.size()) {
            sub[i] = piletops[j];
            piletops[j] = i;           
        } else {
            piletops.push_back(i);
        }
    }

    std::priority_queue<card> heap;
    
    for (i=0; i<piletops.size(); i++) {
        heap.push({a[piletops[i]], piletops[i]});
    }

    std::vector<int> tmp(n);

    i = 0;
    while (heap.size() > 0) {
        now = heap.top();
        heap.pop();

        tmp[i] = now.val;
        i++;

        subcarte = sub[now.idx];
        if (subcarte != -1) {
            heap.push({a[subcarte], subcarte});
        }
    }
    a.swap(tmp);
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
    patience_sort(a);
    assert(std::ranges::is_sorted(a));

    /*
    for (int& x : a) {
        std::cout << x << ' ';
    }
    */

    return 0;
}