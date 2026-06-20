#include <iostream>
#include <vector>
#include <algorithm>

#define NMAX 200002


void apply_optimal_removals(std::string& s, int k) {
    char build[NMAX];
    int n, i, nr, nfin, j;

    n = s.size();
    nfin = n-k;
    build[0] = s[0];
    nr = 1;
    i = 1;
    while (i<n) {
        while (k>0 && nr>0 && s[i]<build[nr-1]) {
            nr--;
            k--;
        }

        build[nr] = s[i];
        nr++;
        i++;
    }

    s.resize(nfin);

    for (i=0; i<nfin; i++) {
        s[i] = build[i];
    }
}

int main() {

    // Un test simplu
    std::string test = "cba";
    int k = 1;

    apply_optimal_removals(test, k);
    std::cout << test << "\n"; // Ar trebui sa afiseze "ba"
    
    return 0;
}
