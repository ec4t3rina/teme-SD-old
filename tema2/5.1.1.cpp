#include <iostream>

const int NMAX = 10001;

int st[NMAX];
int v[NMAX];
int rez[NMAX];

int main() {
    int n, i, k, j;

    std::cin >> n;
    v[0] = 0;
    st[0] = 0;
    k = 1;
    for (i=1; i<=n; i++) {
        std::cin >> v[i];
        while (k>0 && v[i]<v[st[k-1]]) {
            k--;
        }
        rez[i] = st[k-1];
        st[k] = i;
        k++;
    }

    for (i=1; i<=n; i++) {
        std::cout << rez[i] << ' ';
    }

    return 0;
}
