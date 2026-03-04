/// asa cum quicksort e pe cazul mediu O(nlogn), desi worst case este O(n^2),
/// algoritmul asta este O(n) pe cazul mediu (pentru ca eliminam un branch)
/// o sa avem pe cazul mediu n + n/2 + n/4 + ... care tinde la 2n
/// o sa avem O(n) spatiu de la vector + ce va fi pe stiva,
/// deci O(n+logn) pe cazul mediu sau O(n+n) worst case

#include<iostream>

int v[1001];
int n;

void quickselect(int begin, int end, int k) {
    int aux, b, e, pivot;

    b = begin;
    e = end;
    pivot = v[(b+e)/2];

    while (v[b] < pivot) {
        b++;
    }

    while (v[e] > pivot) {
        e--;
    }

    while (b<e) {
        aux = v[b];
        v[b] = v[e];
        v[e] = aux;

        do {
            b++;
        } while (v[b] < pivot);

        do {
            e--;
        } while (v[e] > pivot);
    }

    if (k<=e && begin<e) {
        quickselect(begin, e, k);
    }

    if (k>=b && e+1 < end) {
        quickselect(e+1, end, k);
    }
}

int main() {
    int k, i;

    std::cin >> n;
    for (i=0; i<n; i++) {
        std::cin >> v[i];
    }

    std::cin >> k;
    k--;
    quickselect(0, n-1, k);

    std::cout << v[k];

    return 0;
}