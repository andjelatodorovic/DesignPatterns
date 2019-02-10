#include <iostream>
#include <memory>

using namespace std;

class C {
public:
    string m_a;
    C(string a): m_a(a) { cout << "Konstruktor " << a << endl;}
    virtual ~C() { cout << "Brisem " << m_a << endl; }
};

int main() {
    shared_ptr<C> sc = make_shared<C>("A");
    shared_ptr<C> pc = (shared_ptr<C>) new C("B");
    pc = make_shared<C>("C");
    cout << "X" << endl;
    shared_ptr<C> t = sc;
}
