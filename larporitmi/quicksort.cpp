#include <iostream>

#define NMAX 100001

int v[NMAX];

void myqsort(int begin, int end) {
    int b, e, pivot, aux;

    b = begin;
    e= end;
    pivot = v[(e+b)/2];

    while (v[b]<pivot) {
        b++;
    }
    while (v[e]>pivot) {
        e--;
    }
    while (b<e) {
        aux = v[e];
        v[e] = v[b];
        v[b] = aux;
        do {
            b++;
        } while (v[b]<pivot);
        do {
          e--;
        } while (v[e]>pivot);
    }

    if (begin < e) {
        myqsort(begin, e);
    }
    if (e+1 < end) {
        myqsort(e+1, end);
    }
}

int main() {

    return 0;

}