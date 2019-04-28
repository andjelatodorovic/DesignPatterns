//
// Created by Maverick on 4/21/2017.
//

#include <iostream>
#include <typeinfo>

using namespace std;

template <typename L, typename D>
class PlusOP {
public:
    PlusOP(const L &l, const D &d) : levi(l), desni(d){}
    int getX() const { return levi.getX() + desni.getX(); }
    int getY() const { return levi.getY() + desni.getY(); }
private:
    const L levi;
    const D desni;
};

class Tacka {
public:
    Tacka(int _x = 0, int _y = 0) : x(_x), y(_y) {
        cout << "Konstruktor Tacka" << endl;
    }
    template <typename L, typename D>
    Tacka(const PlusOP<L,D> &op) : x(op.getX()), y(op.getY()) {};

    template <typename L, typename D>
    Tacka& operator= (const PlusOP<L,D>& op) {
        x = op.getX();
        y = op.getY();
        return *this;
    };

    int getX() const { return x; }
    int getY() const { return y; }
private:
    int x, y;
};

PlusOP<Tacka, Tacka> operator+ (const Tacka& levi, const Tacka& desni) {
    cout << "Tacka + Tacka" << endl;
    return PlusOP<Tacka, Tacka>(levi, desni);
};

template <typename L, typename D>
PlusOP<PlusOP<L, D>, Tacka> operator+ (const PlusOP<L, D>& levi, Tacka& desni) {
    cout << "PlusOP<" << typeid(L).name() << "," << typeid(D).name() << "> + Tacka" << endl;
    return PlusOP<PlusOP<L, D>, Tacka>(levi, desni);
}

template <typename L, typename D>
PlusOP<Tacka, PlusOP<L, D>> operator+ (const Tacka& levi, const PlusOP<L, D>& desni) {
    cout << "Tacka + PlusOP<" << typeid(L).name() << "," << typeid(D).name() << ">" << endl;
    return PlusOP<Tacka, PlusOP<L, D>>(levi, desni);
};

template <typename LL, typename LD, typename DL, typename DD>
PlusOP<PlusOP<LL, LD>, PlusOP<DL, DD>> operator+ (const PlusOP<LL, LD>& levi, PlusOP<DL, DD>& desni) {
    cout << "PlusOP<" << typeid(LL).name() << "," << typeid(LD).name() << "> + " << "PlusOP<" << typeid(DL).name() << "," << typeid(DD).name() << ">" << endl;
    return PlusOP<PlusOP<LL, LD>, PlusOP<DL, DD>>(levi, desni);
};

int main() {
    Tacka t1(1,2), t2(3,4), t3(5,6);
    Tacka t = (t1 + t2) + (t3 + t1);
    cout << "(" << t.getX() << ", " << t.getY() << ")" << endl;
    return 0;
}