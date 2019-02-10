#include <vector>
#include <iostream>

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
    odstampaj(v);
    v.insert(v.begin() + 1, 5);
    v.insert(v.begin() + 1, 6);
    v.insert(v.begin() + 1, 7);
    v.insert(v.begin() + 1, 8);
    odstampaj(v);
    v.erase(v.begin() + 3);
    odstampaj(v);
    v.erase(v.begin()+1, v.begin()+3);
    odstampaj(v);
    cout << v.front() << "," << v.back() << endl;
    v.clear();
    odstampaj(v);
    v.push_back(10);
    odstampaj(v);


    return 0;
}

