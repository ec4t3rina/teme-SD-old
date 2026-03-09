#include <iostream>
#include <vector>

using namespace std;

int* vec;
int size = 0;
int capacity = 0;

void init() {
    vec = new int[2];
    capacity = 2;
}

int get_size() {
    return size;
}

void pop_back() {
    size--;
}

void resize() {
    int i;
    int* newvec = new int[2*capacity];

    capacity *= 2;
    for (i=0; i<size; i++) {
        newvec[i] = vec[i];
    }

    delete[] vec;
    vec = newvec;
    capacity *= 2;
}

void push_back(int x) {
    if (size==capacity) {
        resize();
    }
    vec[size] = x;
    size++;
}

vector<int> v;

int main() {
    int i, n;

    init();

    push_back(1);
    push_back(2);
    push_back(4);
    push_back(8);

    cout << get_size() << '\n';

    pop_back();
    cout << get_size() << '\n';

    n = get_size();
    for (i=0; i<n; i++) {
        cout << vec[i] << " ";
    }

    return 0;
}