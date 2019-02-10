#include <iostream>

using namespace std;

/* target / ciljani interfejs */
class Izvrsalac {
public:
    virtual ~Izvrsalac(){}
    virtual void izvrsi() = 0;
};

/* adapter - preko objekta, za svaki objekat prosledjujemo i metod pomocu kojeg cemo da vrsimo
  adaptiranje
  u ovom slucaju klase koje su adaptirane ne moraju da nasledjuju istu klasu i da imaju isti
  metod koji cemo da adaptiramo */
template <class T>
class IzvrsalacAdapter: public Izvrsalac {
public:
    IzvrsalacAdapter(T *objekat, void(T:: *metod)()) {
        this->objekat = objekat;
        this->metod = metod;
    }
    ~IzvrsalacAdapter() {
        delete objekat;
    }
    void izvrsi() {
        (objekat->*metod)();
    }
private:
    T *objekat;
    void(T:: *metod)();
};


/* nekompatibilne klase Prvi, Drugi, Treci koje zelimo da adaptiramo, i imaju
  metode razlicitih imena ali istog tipa uradi(), uradi_drugo(), uradi_trece()*/
class Prvi {
public:
    ~Prvi() {
        cout << "Prvi::unisten" << endl;
    }
    void uradi() {
        cout << "Prvi::uradi()" << endl;
    }
};

class Drugi {
public:
    ~Drugi() {
        cout << "Drugi::unisten" << endl;
    }
    void uradi_drugo() {
        cout << "Drugi::uradi_drugo()" << endl;
    }
};

class Treci {
public:
    ~Treci() {
        cout << "Treci::unisten" << endl;
    }
    void uradi_trece() {
        cout << "Treci::uradi_trece()" << endl;
    }
};

Izvrsalac **inicijalizuj() {
    Izvrsalac **izvrsioci = new Izvrsalac *[3];

    izvrsioci[0] = new IzvrsalacAdapter<Prvi>(new Prvi(),
                                                &Prvi::uradi);
    izvrsioci[1] = new IzvrsalacAdapter<Drugi>(new Drugi(),
                                               &Drugi::uradi_drugo);
    izvrsioci[2] = new IzvrsalacAdapter<Treci>(new Treci(),
                                               &Treci::uradi_trece);
    return izvrsioci;
}

int main() {
    Izvrsalac **objekti = inicijalizuj();
    for (int i = 0; i < 3; i++) {
        objekti[i]->izvrsi();
    }
    for (int i = 0; i < 3; i++) {
        delete objekti[i];
    }
    delete objekti;
    return 0;
}
