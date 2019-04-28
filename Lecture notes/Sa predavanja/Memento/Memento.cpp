//
// Created by Maverick on 5/4/2017.
//

#include <iostream>
#include <list>			// list
#include <memory>		// shared_ptr
//#include <stdexcept>	// runtime_error

using namespace std;

template <typename>
class AbsSubjekt;

template <class TipSubjekta>
class Podsetnik {
public:
    TipSubjekta getStanje() { return stanje; }
    virtual ~Podsetnik() {}
private:
    friend AbsSubjekt<TipSubjekta>;
    TipSubjekta stanje;

    Podsetnik(TipSubjekta _st) : stanje(_st) {}

};

template <typename TPodsednik>
class CuvarPodsetnika {
public:
    void push(shared_ptr<TPodsednik> m) { lista.push_back(m); }
    shared_ptr<TPodsednik> pop() {
        if (lista.size() < 1)
            throw runtime_error::runtime_error("Prazna lista podsetnika");
        shared_ptr<TPodsednik> res = lista.front();
        lista.pop_front();
        return res;
    }
private:
    typedef list<shared_ptr<TPodsednik>> listaPodsetnika;
    listaPodsetnika lista;
};

template <typename Izvedena>
class AbsSubjekt {
public:
    typedef Podsetnik<Izvedena> _Podsetnik;                 // Ovde ne treba da stoji `typename` | expected nested-name-specifier
    typedef CuvarPodsetnika<_Podsetnik> _CuvarPodsetnika;   // Ovde ne treba da stoji `typename` | expected nested-name-specifier

    shared_ptr<_Podsetnik> kreirajPodsetnik() {
        return shared_ptr<_Podsetnik>(new _Podsetnik(static_cast<const Izvedena&>(*this)));
    }

    void vratiNaPodsetnik(shared_ptr<_Podsetnik> podsetnik) {
        static_cast<Izvedena&>(*this) = podsetnik->getStanje();
    }
};

class Subjekt : public AbsSubjekt<Subjekt> {
public:
    Subjekt(string s): str(s){}
    void set(string s) { str = s; }
    void prikazi() const { cout << str.c_str() << endl; }
private:
    string str;
};

int main() {
    Subjekt s("String 1");
    Subjekt::_CuvarPodsetnika cuvar;
    cuvar.push(s.kreirajPodsetnik());
    s.set("String 2");

    s.prikazi();
    s.vratiNaPodsetnik(cuvar.pop());

    s.prikazi();
}