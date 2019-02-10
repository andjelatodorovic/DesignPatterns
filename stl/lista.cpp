#include <list>
#include <iostream>

using namespace std;

void prikazi(list<int> L) {
    for (list<int>::iterator it = L.begin();it != L.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    list<int> L;
    L.push_front(1);
    L.push_front(2);
    L.push_front(3);
    L.push_back(4);
    L.push_back(5);
    L.push_back(6);
    list<int> P;
    P.push_front(1);
    P.push_front(2);
    P.push_front(3);
    P.push_back(4);
    P.push_back(5);
    P.push_back(6);
    L.sort();
    P.sort();
    prikazi(L);
    prikazi(P);
    L.merge(P);
    prikazi(L);
    L.remove(3);
    prikazi(L);
    L.unique();
    prikazi(L);
    L.reverse();
    prikazi(L);
    L.pop_back();
    L.pop_front();
    prikazi(L);
    L.sort();
    prikazi(L);
}
