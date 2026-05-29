#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

#define NMAX 100001

int q[NMAX];
std::atomic<int> st;
std::atomic<int> dr;

int flag = -1;

bool push(int x) {
    int nxtst;

    nxtst = (st.load()+1)%NMAX;

    if (nxtst == dr.load()) {
        return false;
    }

    q[st.load()] = x;
    st.store(nxtst);
    return true;
}

bool pop(int &x) {
    int nxtdr;

    nxtdr = (dr.load()+1)%NMAX;

    if (dr.load() == st.load()) {
        return false;
    }
    x = q[dr.load()];
    dr.store(nxtdr);
    return true;
}

void producer() {
    int x;

    while (std::cin >> x) {
        while (push(x)==false) {}
    }

    while (!push(flag)) {}
}

void consumer() {
    int x;

    while (true) {
        while (pop(x) ==false) {
            std::this_thread::yield();
        }
        if (x == flag) {
            break;
        }
    }
}
 
int main() {
    st = 0;
    dr = 0;

    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
