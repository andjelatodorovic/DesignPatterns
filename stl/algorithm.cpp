#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


typedef vector<int> VInt;
typedef VInt::iterator VIntIter;


void odstampaj(vector<int> &v) {
    /*
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    */
    for (VIntIter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    v.insert(v.begin() + 1, 5);
    v.insert(v.begin() + 1, 6);
    v.insert(v.begin() + 1, 7);
    v.insert(v.begin() + 1, 8);
    odstampaj(v);
    vector<int>::iterator it = find(v.begin(), v.end(), 5);
    if (it == v.end()) cout << "Nema elementa u nizu" << endl;
    else cout << "Pozicija " << (it - v.begin()) << endl;
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    odstampaj(v);

    return 0;
}

