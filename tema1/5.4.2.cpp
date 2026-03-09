#include<iostream>

int main() {
    long long int n, st, dr, mijl;

    std::cin >> n;

    /* -- metoda basic
    st = 0;
    dr = n;
    while (dr-st>1) {
        mijl = (st+dr)/2;
        if (mijl*mijl>n) {
            dr = mijl;
        } else {
            st = mijl;
        }
    }
    std::cout << st;
    */

    /// metoda lui newton:
    st = n;
    do {
        dr = st;
        st = (dr+n/dr)/2;
        std::cout << st << ' ' << dr << '\n';
    } while (dr>st);
    std::cout << dr;


    return 0;
}