/*
Kreirate apstraktnu klasu Celija
i dve konkretne CelijaA i CelijaB
sa nekim poljem int velicina
i implementirati ih po sablonu
prototip.
Napraviti i neku klasu FabrikaCelija
koja ce da ima skup prototipova
i metod dajCeliju(TIP_CELIJE)
koji ce da vrati klon celije
tog tipa
*/

#include <iostream>

using namespace std;

/* apstraktan prototip */
class Celija {
protected:
    int m_cellSize;
public:
    virtual Celija* clone() = 0;
    virtual void moveAround() = 0;
    void setSize(int cellSize) {
        m_cellSize = cellSize;
    }
    int getSize() {
        return m_cellSize;
    }
};
/* konkretan prototip */
class CelijaA: public Celija {
public:
    Celija* clone() {
        Celija *cloneCell = new CelijaA();
        cloneCell->setSize(getSize());
        return cloneCell;
    }
    void moveAround() {
        cout << "CelijaA se pomera okolo. Velika sam " << getSize() << endl;
    }
};
/* konkretan prototip */
class CelijaB: public Celija {
public:
    Celija* clone() {
        Celija *cloneCell = new CelijaB();
        cloneCell->setSize(getSize());
        return cloneCell;
    }
    void moveAround() {
        cout << "CelijaB se pomera okolo. Velika sam " << getSize() << endl;
    }
};
/* primer koriscenja sablona prototip, kreiramo konkretne prototipove pozivajuci njihove konstruktore
   postavimo neke osobine, koristimo ih zatim ih kloniramo i kopijamo izmenimo osobine i njih prikazemo */
int main() {
    Celija *prototipA = new CelijaA();
    prototipA->setSize(20);
    Celija *prototipB = new CelijaB();
    prototipB->setSize(40);
    cout << "Pomeraju se originalne celije:" << endl;
    prototipA->moveAround();
    prototipB->moveAround();

    Celija *klonA = prototipA->clone();
    klonA->setSize(klonA->getSize() * 2);
    Celija *klonB = prototipB->clone();
    klonB->setSize(klonB->getSize() * 3);
    cout << "Pomeraju se klonirane celije:" << endl;
    klonA->moveAround();
    klonB->moveAround();

    return 0;
}
