#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

std::vector<int> longest_interval_after_each_update (int l, std::vector <int> splitpoints) {
    std::multiset<int> cap;
    std::multiset<int> lung;
    std::vector<int> rez;
    int q, i, x, dist;

    q = splitpoints.size();

    cap.insert(0);
    cap.insert(l);
    lung.insert(-l);
    for (i=0; i<q; i++) {
        x = splitpoints[i];
        auto idxdr = cap.upper_bound(x);
        auto idxst = prev(idxdr);

        dist = *idxdr-*idxst;

        auto it = lung.find(-dist);
        if (it!=lung.end()) {
            lung.erase(it);
        }
        dist = x-*idxst;
        lung.insert(-dist);
        dist = *idxdr-x;
        lung.insert(-dist);

        cap.insert(x);

        it = lung.begin();
        rez.push_back(-*it);
    }

    return rez;
}

int main() {

    return 0;
}