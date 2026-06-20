#include <iostream>
#include <vector>
#include <algorithm>

#define NMAX 200002

int sef[NMAX];
int lung[NMAX];

int max;

struct cutmaxxing {
    int poz;
    int id;
};

int find(int i) {
    if (sef[i]==i) {
        return i;
    }
    return sef[i] = find(sef[i]);
}

void uneste(int i, int j) {
    int sefi, sefj;

    sefi = find(i);
    sefj = find(j);

    if (sefi==sefj) {
        return;
    }

    sef[sefj] = sefi;
    lung[sefi]+=lung[sefj];

    if (lung[sefi] > max) {
        max = lung[sefi];
    }
}

std::vector<int> longest_interval_after_each_update (int l, std::vector<int> splitpoints) {
    int n, i, st, dr;

    n = splitpoints.size();

    std::vector<cutmaxxing> sh(n);
    for (i=0; i<n; i++) {
        sh[i].poz = splitpoints[i];
        sh[i].id = i;
    }

    std::sort(sh.begin(), sh.end(), [](const cutmaxxing& a, const cutmaxxing& b) {
        return a.poz < b.poz;
    });

    std::vector<int> pct;
    pct.push_back(0);
    for (i=0; i<n; i++) {
        pct.push_back(sh[i].poz);
    }
    pct.push_back(l);

    std::vector<int> idxst(n);
    for (i=0; i<n; i++) {
        idxst[sh[i].id] = i;
    }

    max = 0;
    for (i=0; i<=n; i++) {
        sef[i] = i;
        lung[i] = pct[i+1]-pct[i];

        if (lung[i]>max) {
            max = lung[i];
        }
    }

    std::vector<int> rez(n);
    for (i=n-1; i>=0; i--) {
        rez[i] = max;

        st = idxst[i];
        dr = st+1;

        uneste(st, dr);
    }

    return rez;
}


int main() {

    std::cout << "--- TESTARE LUNGIME MAXIMA INTERVALE ---\n\n";

    // TESTUL 1: Taieturi asimetrice
    // Interval [0, 10]. Taiem pe rand la 4, 7 si 2.
    int l1 = 10;
    std::vector<int> splits1;
    splits1.push_back(4);
    splits1.push_back(7);
    splits1.push_back(2);
    std::vector<int> rez1 = longest_interval_after_each_update(l1, splits1);

    std::cout << "Test 1 (L=10, splits={4, 7, 2}):\n";
    std::cout << "Rezultat obtinut:  ";
    for (int x : rez1) {
        std::cout << x << " ";
    }
    std::cout << "\nRezultat asteptat: 6 4 3\n";
    std::cout << "Explicatie: \n";
    std::cout << "- Dupa 4: avem [0,4] si [4,10]. Maxim e 6.\n";
    std::cout << "- Dupa 7: avem [0,4], [4,7], [7,10]. Maxim e 4.\n";
    std::cout << "- Dupa 2: avem [0,2], [2,4], [4,7], [7,10]. Maxim e 3.\n\n";


    // TESTUL 2: Taieturi fix pe jumatate
    // Interval [0, 20]. Taiem la 10, apoi la 5, apoi la 15.
    int l2 = 20;
    std::vector<int> splits2;
    splits2.push_back(10);
    splits2.push_back(5);
    splits2.push_back(15);
    std::vector<int> rez2 = longest_interval_after_each_update(l2, splits2);

    std::cout << "Test 2 (L=20, splits={10, 5, 15}):\n";
    std::cout << "Rezultat obtinut:  ";
    for (int x : rez2) {
        std::cout << x << " ";
    }
    std::cout << "\nRezultat asteptat: 10 10 5\n";
    std::cout << "Explicatie:\n";
    std::cout << "- Dupa 10: avem [0,10] si [10,20]. Maxim e 10.\n";
    std::cout << "- Dupa 5: avem [0,5], [5,10], [10,20]. Maxim ramane 10 (din dreapta).\n";
    std::cout << "- Dupa 15: toate bucatile au fix lungimea 5. Maxim e 5.\n";

    return 0;
}