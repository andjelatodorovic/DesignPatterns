/* primer iz knjige Design Patterns Explained Simply */

#include <iostream>
#include <vector>

using namespace std;

/* sada je primenjen sablon fabricki metod kako bi se kreacija zivotinja (konkretnih proizvoda) delegirala
   klasi koja ima implementiran fabricki metod, u ovom slucaju fabricki metod je stavljen unutar apstraktnog
   proizvoda */

/* apstraktan kreator/stvaraoc koji ima fabricki metod napraviZivotinju */
class Zivotinja {
public:
    static Zivotinja *napraviZivotinju(int odabir);
    virtual void mrdaj() = 0;
};
/* konkretan proizvod */
class Pas: public Zivotinja {
public:
    void mrdaj() {
        cout << "Pas: trcim po parku..." << endl;
    }
};
/* konkretan proizvod */
class Riba: public Zivotinja {
public:
    void mrdaj() {
        cout << "Riba: plivam po dubinama okeana..." << endl;
    }
};
/* konkretan proizvod */
class Ptica: public Zivotinja {
public:
    void mrdaj() {
        cout << "Ptica: letim nebom visoko..." << endl;
    }
};
/* implementacija fabrickog metoda */
Zivotinja *Zivotinja::napraviZivotinju(int odabir) {
    if (odabir == 1) {
        return new Pas();
    } else if (odabir == 2) {
        return new Riba();
    } else {
        return new Ptica();
    }
}
/* upotreba sablona fabricki metod, primetiti da nigde nisu vidljivi konkretni proizvodi */
int main() {
    vector<Zivotinja*> uloge;
    int odabir;
    while (true) {
        cout << "Pas(1) Riba(2) Ptica(3) Go(0): ";
        cin >> odabir;
        if (odabir == 0) {
            break;
        }
        uloge.push_back(Zivotinja::napraviZivotinju(odabir));
    }
    for (int i = 0; i < uloge.size(); i++) {
        uloge[i]->mrdaj();
    }
    for (int i = 0; i < uloge.size(); i++) {
        delete uloge[i];
    }
    return 0;
}


