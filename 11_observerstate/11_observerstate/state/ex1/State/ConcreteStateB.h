#ifndef __CONCRETESTATEB_H
#define __CONCRETESTATEB_H

#include <iostream>

#include "State.h"

using namespace std;

/* konkretno stanje / concrete state
   implementira metod handle koji konktekst zove prilikom razresavanja nekog
   zahteva */
class ConcreteStateB: public State {
public:
    ConcreteStateB() {}
    virtual ~ConcreteStateB() {}
    virtual void Handle() {
        cout << "ConcreteStateB.Handle()" << endl;
    }
};

#endif // __CONCRETESTATEB_H

