#include <iostream>
#include <cmath>
#include <memory>

using namespace std;

/* 3D modeli, ima sablon metod GetVolume implementiran pozivajuci metode za racunanje
   povrsine osnove kao i visine modela, ovo radi za vrlo limitiran skup modela */
class IShape3D {
public:
    virtual double GetVolume() {
        return GetBaseArea() * GetHeight();
    }
    virtual double GetBaseArea() = 0;
    virtual double GetHeight() = 0;
};
/* konkretna klasa koja implementira metode koriscene u sablon metodu, GetBaseArea i GetHeight */
class CKocka: public IShape3D {
public:
    CKocka(double side): m_side(side) {}
    virtual double GetBaseArea() { return m_side * m_side; }
    virtual double GetHeight() { return m_side; }
protected:
    double  m_side;
};
/* konkretna klasa koja implementira metode koriscene u sablon metodu, GetBaseArea i GetHeight */
class CKvadar: public IShape3D {
public:
    CKvadar(double length, double width, double height): m_length(length), m_width(width), m_height(height) {}
    virtual double GetBaseArea() { return m_length * m_width; }
    virtual double GetHeight() { return m_height; }
protected:
    double  m_length;
    double  m_width;
    double  m_height;
};
/* konkretna klasa koja implementira metode koriscene u sablon metodu, GetBaseArea i GetHeight */
class CKupa: public IShape3D {
public:
    CKupa(double r, double h): m_r(r), m_height(h) {}
    virtual double GetBaseArea() {
        return 3.141592653589793 * m_r * m_r;
    }
    virtual double GetHeight() { return m_height; }
protected:
    double  m_r;
    double  m_height;
};

int main() {
    unique_ptr<IShape3D> kocka(new CKocka(2.5));
    unique_ptr<IShape3D> kvadar(new CKvadar(1.0, 2.0, 3.0));
    unique_ptr<IShape3D> kupa(new CKupa(2.0, 3.0));
    cout << kocka->GetVolume() << endl;
    cout << kvadar->GetVolume() << endl;
    cout << kupa->GetVolume() << endl;

    return 0;
}
