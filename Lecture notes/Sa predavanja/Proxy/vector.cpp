//
// Created by Maverick on 5/6/2017.
//

#include<iostream>
using namespace std;

template<class L,class D>
class PlusOp {
    const L& l;
    const D& d;
    int sz;
public:
    PlusOp(const L& ll,const D& dd):l(ll),d(dd),sz(l.getBrEl()){}
    const int operator[](int i) const {
        return l[i]+d[i];
    }
    const int getBrEl() const {
        return sz;
    }
};

class Vector {
    int* niz;
    int sz;
    int top;
public:

    Vector(int n=2):niz(new int[n]),sz(n),top(-1) {
        cout << "KONSTRUKTOR" << endl;
    }

    template<class L, class D>
    Vector(const PlusOp<L,D>& p):niz(new int[p.getBrEl()]),sz(p.getBrEl()),top(p.getBrEl()-1) {
        cout << "KONSTRUKTOR PLUSOP" << endl;
        for (int i=0; i<=top; i++) {
            niz[i]=p[i];
        }
    }

    ~Vector() {
        delete [] niz;
    }

    Vector(const Vector& o):niz(new int[o.sz]),sz(o.sz),top(o.top) {
        cout << "KONSTRUKTOR KOPIJE" << endl;
        for (int i=0; i<=top; i++) {
            niz[i]=o.niz[i];
        }
    }

    Vector& operator=(const Vector& o) {
        cout << "OPERATOR =" << endl;
        if (this!=&o) {
            delete [] niz;
            niz = new int[o.sz];
            top = o.top;
            sz = o.sz;
            for (int i=0; i<=top; i++) {
                niz[i]=o.niz[i];
            }
        }
        return *this;
    }

    template<class L, class D>
    Vector& operator=(const PlusOp<L,D>& p) {
        cout << "OPERATOR PlusOp=" << endl;
        delete [] niz;
        niz = new int[p.getBrEl()];
        top = p.getBrEl()-1;
        sz = p.getBrEl();
        for (int i=0; i<=top; i++) {
            niz[i]=p[i];
        }
        return *this;
    }

    void add(int el) {
        if (top+1==sz)
            Reallocate();
        niz[++top]=el;
    }

    void ispisi() const {
        for (int i=0; i<=top; i++) {
            cout << niz[i] << " ";
        }
        cout << endl;
    }

    const int getBrEl() const {
        return top+1;
    }

    const int cap() const {
        return sz;
    }

    int& operator[](int i) {
        return niz[i];
    }

    const int& operator[](int i) const {
        return niz[i];
    }

private:
    void Reallocate() {
        int* tmp = new int[sz << 2];
        for (int i=0; i<sz; i++) {
            tmp[i]=niz[i];
        }
        delete [] niz;
        niz = tmp;
        sz<<=1;
    }
};

const PlusOp< Vector,Vector > operator+(const Vector& v1,const Vector& v2){
    return PlusOp< Vector,Vector >(v1,v2);
}

template<class L,class D>
const PlusOp< PlusOp<L,D>,Vector > operator+(const PlusOp<L,D>& v1,const Vector& v2){
    return PlusOp< PlusOp<L,D>,Vector >(v1,v2);
}

template<class L,class D>
const PlusOp< Vector,PlusOp<L,D> > operator+(const Vector& v1,const PlusOp<L,D>& v2){
    return PlusOp< Vector,PlusOp<L,D> >(v1,v2);
}

template<class L,class D>
const PlusOp< PlusOp<L,D>,PlusOp<L,D> > operator+(const PlusOp<L,D>& v1,const PlusOp<L,D>& v2){
    return PlusOp< PlusOp<L,D>,PlusOp<L,D> >(v1,v2);
}

int main() {

    Vector v;
    v.add(3);
    v.add(2);
    v.add(1);
    v.add(4);
    v.add(6);
    v.add(2);
    cout << "Vector" << endl;
    v.ispisi();

    Vector v2=v;
    Vector v3=v;
    Vector v4=v;
    Vector v5=v;
    Vector v6=v;
    cout << "-----------------------------------" << endl;
    cout << "SABIRANJE" << endl;
    v=(v2+v3)+(v5+v6);
    cout << "Vector" << endl;
    v.ispisi();

}
