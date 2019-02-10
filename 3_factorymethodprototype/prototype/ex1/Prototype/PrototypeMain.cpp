#include <iostream>
#include "ConcretePrototype1.h"
#include "ConcretePrototype2.h"

using namespace std;

/* primer upotrebe sablona prototip,
   kreiramo dva konkretna proizvoda (direktnim pozivom njihovih konstruktora) koji ce da imaju
   tip apstraktnog proizvoda a zatim kreiramo njihove kopije pozivajuci metod za kloniranje, clone */
int main() {
    Prototype *prototype1 = new ConcretePrototype1();
    Prototype *prototype2 = new ConcretePrototype2();
    cout << "Koristim originalne prototipove: " << endl;
    prototype1->use();
    prototype2->use();

    Prototype *clonePrototype1 = prototype1->clone();
    Prototype *clonePrototype2 = prototype2->clone();

    cout << "Koristim klonirane prototipove: " << endl;
    clonePrototype1->use();
    clonePrototype2->use();

    delete prototype1;
    delete prototype2;
    delete clonePrototype1;
    delete clonePrototype2;
    return 0;
}

