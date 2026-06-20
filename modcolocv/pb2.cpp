#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 150001

class StreamGcdCalculator {
public :
    StreamGcdCalculator () { n = 0; }
    void insert ( int x ) {
        n++;
        p[x].push_back(n-1);
        update(0, 0, NMAX, n-1, x);
    }
    void erase ( int x ) {
        int poz;
        poz = p[x].back();
        p[x].pop_back();
        update(0, 0, NMAX, poz, 0);
    }
    int gcd () {
        return query(0, 0, NMAX, 0, n-1);
    }
private :
    int n;
    int aint[4*NMAX];
    unordered_map<int, vector<int>> p;

    int f (int a, int b) {
        int r;
        while (b>0) {
            r = a%b;
            a = b;
            b = r;
        }
        return a;
    }

    int query(int nod, int st, int dr, int qst, int qdr) {
        if (qst<=st && dr<=qdr) {
            return aint[nod];
        }

        int mijl, sonst, sondr, rez;

        mijl = (st+dr)/2;
        sonst = nod+1;
        sondr = nod + 2*(mijl-st+1);

        rez = 0;
        if (qst<=mijl) {
            rez = f(rez, query(sonst, st, mijl, qst, qdr));
        }
        if (qdr > mijl) {
            rez = f(rez, query(sondr, mijl+1, dr, qst, qdr));
        }

        return rez;
    }

    void update(int nod, int st, int dr, int poz, int val) {
        int mijl, sonst, sondr;

        if (st==dr) {
            aint[nod] = val;
            return;
        }

        mijl = (st+dr)/2;
        sonst = nod+1;
        sondr = nod + 2*(mijl-st+1);

        if (poz<=mijl) {
            update(sonst, st, mijl, poz, val);
        } else {
            update(sondr, mijl+1, dr, poz, val);
        }

        aint[nod] = f(aint[sonst], aint[sondr]);
    }
};

int main() {

    //// DA AM GENERAT MAINUL CU GEMINI OK OK IDC AIA E IMI PARE RAU PT ALL THE PERFECT SISTERS AND BROTHERS OUT THERE SI IDK NONBINARY PEOPLE HELL YEAH

    StreamGcdCalculator calculator;

    cout << "--- TESTARE StreamGcdCalculator ---\n\n";

    calculator.insert(6);
    cout << "Insert 6   -> GCD: " << calculator.gcd() << " (Asteptat: 6)\n";

    calculator.insert(12);
    cout << "Insert 12  -> GCD: " << calculator.gcd() << " (Asteptat: 6)\n";

    calculator.insert(9);
    cout << "Insert 9   -> GCD: " << calculator.gcd() << " (Asteptat: 3, pt ca gcd(6, 12, 9) = 3)\n";

    calculator.erase(9);
    cout << "Erase 9    -> GCD: " << calculator.gcd() << " (Asteptat: 6, si-a revenit la 6 si 12!)\n";

    calculator.insert(6);
    cout << "Insert 6   -> GCD: " << calculator.gcd() << " (Asteptat: 6)\n";

    calculator.erase(6);
    cout << "Erase 6    -> GCD: " << calculator.gcd() << " (Asteptat: 6, am sters un 6 dar mai e unul!)\n";

    calculator.erase(6);
    cout << "Erase 6    -> GCD: " << calculator.gcd() << " (Asteptat: 12, am sters toti 6, a ramas doar 12!)\n";

    return 0;
}