#include<iostream>

int n, m;
int a[1001][1001];

int main() {
    int x, l, c, pas;

    std::cin >> n >> m;
    for (l=0; l<n; l++) {
        for (c=0; c<m; c++) {
            std::cin >> a[l][c];
        }
    }

    std::cin >> x;

    c = m-1;
    l = 0;
    pas = 1;
    while (l<n && c>=0 && pas == 1 && a[l][c]!=x) {
        pas = 0;
        if (a[l][c]<x && l<n-1) {
            l++;
            pas = 1;
        }
        if (a[l][c]>x && c>0) {
            c--;
            pas = 1;
        }
    }

    if (a[l][c]==x) {
        std::cout << l << ' ' << c;
    } else {
        std::cout << "womp womp nu exista :c";
    }

    return 0;
}