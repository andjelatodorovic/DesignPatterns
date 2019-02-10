#include <iostream>
#include <cstring>

using namespace std;

enum TipPice { CETIRI_DOBA, MARGERITA };

/* apstraktan proizvod */
class Pica {
public:
    virtual void jedi() = 0;
};

/* konkretan proizvod */
class CetiriDoba: public Pica {
public:
    void jedi() {
        cout << "Jedem picu CetiriDoba" << endl;
    }
};
/* konkretan proizvod */
class Margerita: public Pica {
public:
    void jedi() {
        cout << "Jedem picu Margerita" << endl;
    }
};
/* apstraktan kreator */
class Picerija {
public:
    virtual Pica* dajPicu(TipPice tip) = 0;
};
/* konkretan kreator */
class MojaPicerija: public Picerija {
public:
    Pica* dajPicu(TipPice tip) {
        switch (tip) {
        case CETIRI_DOBA: return new CetiriDoba();
        case MARGERITA: return new Margerita();
        default: return NULL;
        }
    }
};
/* primer koriscenja sablona */
int main() {
    Picerija *picerija = new MojaPicerija();
    Pica *pica;
    cout << "Koju picu hocete (C - Cetiri godisnja doba, M - margerita)? ";
    char ch;
    cin >> ch;
    if (ch == 'c' || ch == 'C') pica = picerija->dajPicu(CETIRI_DOBA);
    else pica = picerija->dajPicu(MARGERITA);

    pica->jedi();
    return 0;
}
