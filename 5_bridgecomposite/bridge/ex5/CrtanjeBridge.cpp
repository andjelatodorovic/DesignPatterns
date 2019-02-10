#include <iostream>

using namespace std;

/* implementator */
class Crtac {
public:
    virtual ~Crtac() { }
    virtual void nacrtajKrug(double x, double y, double r) = 0;
    virtual void nacrtajLiniju(double x1, double y1, double x2, double y2) = 0;
};

/* konkretan implementator */
class Crtac1: public Crtac {
public:
    virtual ~Crtac1() { }
    virtual void nacrtajKrug(double x, double y, double r) {
        cout << "<CRTAC 1> " << "crtam krug (" << x << ", " << y << ")   R = " << r << endl;
    }
    virtual void nacrtajLiniju(double x1, double y1, double x2, double y2) {
        cout << "<CRTAC 1> " << "crtam liniju (" << x1 << ", " << y1 << ") - (" << x2 << ", " << y2 << ")" << endl;
    }
};

/* konkretan implementator */
class Crtac2: public Crtac {
public:
    virtual ~Crtac2() { }
    virtual void nacrtajKrug(double x, double y, double r) {
        cout << "<CRTAC 2> " << "crtam krug (" << x << ", " << y << ")   R = " << r << endl;
    }
    virtual void nacrtajLiniju(double x1, double y1, double x2, double y2) {
        cout << "<CRTAC 2> " << "crtam liniju (" << x1 << ", " << y1 << ") - (" << x2 << ", " << y2 << ")" << endl;
    }
};

/* apstrakcija */
class Oblik {
protected:
    Crtac *m_crtac;
public:
    Oblik() { m_crtac = NULL; }
    Oblik(Crtac *crtac) : m_crtac(crtac) {}
    virtual ~Oblik() { if (m_crtac != NULL) delete m_crtac; }
    virtual void nacrtaj() = 0;
    virtual void promeniVelicinu(double k) = 0;
    virtual void postaviCrtaca(Crtac *crtac) {
        if (m_crtac != NULL) {
            delete m_crtac;
        }
        m_crtac = crtac;
    }
};

/* rafinirana apstrakcija */
class Krug: public Oblik {
protected:
    double m_x, m_y, m_r;
public:
    Krug(double x, double y, double r) : m_x(x), m_y(y), m_r(r) { }
    Krug(double x, double y, double r, Crtac *crtac) : m_x(x), m_y(y), m_r(r), Oblik(crtac) {}
    virtual ~Krug() {}
    virtual void nacrtaj() {
        cout << "<KRUG> " << "nacrtaj()" << endl;
        if (m_crtac != NULL) {
            m_crtac->nacrtajKrug(m_x, m_y, m_r);
        } else {
            cout << "Nije postavljen crtac." << endl;
        }
    }
    virtual void promeniVelicinu(double k) {
        if (k > 0) {
            m_r *= k;
        }
    }
};

int main() {
    Krug *krug1 = new Krug(5.0, 5.0, 10.0, new Crtac1());
    Krug *krug2 = new Krug(30.0, 30.0, 20.0);
    krug2->postaviCrtaca(new Crtac2());

    krug1->nacrtaj();
    krug2->nacrtaj();

    krug2->postaviCrtaca(new Crtac1());
    krug2->promeniVelicinu(0.5);
    krug2->nacrtaj();

    delete krug1;
    delete krug2;

    return 0;
}
