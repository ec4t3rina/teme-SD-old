#include <iostream>

#define NMAX 100001

int heap[NMAX];
int heapsize;

////// DE FACUT FUNCTIA BUILD!!!!!

static inline int parent(int i) {
    return (i-1)/2;
}
static inline int left(int i) {
    return i*2+1;
}
static inline int right(int i) {
    return i*2+2;
}

void downheap(int nod) {
    int maxi, st, dr, aux;

    st = left(nod);
    dr = right(nod);
    maxi = nod;

    if (st<heapsize && heap[st] > heap[maxi]) {
        maxi = st;
    }
    if (dr<heapsize && heap[dr] > heap[maxi]) {
        maxi = dr;
    }

    if (maxi != nod) {
        aux = heap[maxi];
        heap[maxi] = heap[nod];
        heap[nod] = aux;
        downheap(maxi);
    }
}

void upheap(int nod) {
    int aux;
    while (nod > 0 && heap[parent(nod)] < heap[nod]) {
        aux = heap[parent(nod)];
        heap[parent(nod)] = heap[nod];
        heap[nod] = aux;
        nod = parent(nod);
    }
}

void pop() {
    heapsize--;
    heap[0] = heap[heapsize];
    downheap(0);
}

void insert(int val) {
    heap[heapsize] = val;
    heapsize++;
    upheap(heapsize-1);
}

int main() {

    return 0;

}