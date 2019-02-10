/* primer iz knjige Design Patterns Explained Simply */

#include <iostream>
#include <vector>

using namespace std;

/* imamo apstraktnu klasu zivotinja i konkretne nasledne Pas, Riba, Ptica, prilikom izvrsenja programa
   pitani smo da odaberemo koje cemo sve tipove zivotinja da kreiramo i nakon toga bude prikazano sta
   rade te zivotinje koje smo kreirali
   zivotinje su kreirane tako sto u glavnom programu direktno pozivamo konstruktor za odgovorajuci tip
   zivotinje (konkretan proizvod je kreiran unutar glavnog programa) i nije koristen nijedan sablon
   za kreiranje objekata */
class Zivotinja {
public:
    virtual void mrdaj() = 0;
};

class Pas: public Zivotinja {
public:
    void mrdaj() {
        cout << "Pas: trcim po parku..." << endl;
    }
};
class Riba: public Zivotinja {
public:
    void mrdaj() {
        cout << "Riba: plivam po dubinama okeana..." << endl;
    }
};
class Ptica: public Zivotinja {
public:
    void mrdaj() {
        cout << "Ptica: letim nebom visoko..." << endl;
    }
};

int main() {
    vector<Zivotinja*> uloge;
    int odabir;
    while (true) {
        cout << "Odaberi ulogu (1-3) ili startuj simulaciju (0)\nPas(1), Riba(2), Ptica(3), Startuj(0): ";
        cin >> odabir;
        if (odabir == 0) {
            break;
        } else if (odabir == 1) {
            uloge.push_back(new Pas());
        } else if (odabir == 2) {
            uloge.push_back(new Riba());
        } else {
            uloge.push_back(new Ptica());
        }
    }
    for (int i = 0; i < uloge.size(); i++) {
        uloge[i]->mrdaj();
    }
    for (int i = 0; i < uloge.size(); i++) {
        delete uloge[i];
    }
    return 0;
}
