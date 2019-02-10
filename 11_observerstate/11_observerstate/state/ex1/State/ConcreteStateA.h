#ifndef __CONCRETESTATEA_H
#define __CONCRETESTATEA_H

#include <iostream>

#include "State.h"

using namespace std;

/* konkretno stanje / concrete state
   implementira metod handle koji konktekst zove prilikom razresavanja nekog
   zahteva */
class ConcreteStateA: public State {
public:
    ConcreteStateA() {}
    virtual ~ConcreteStateA() {}
    virtual void Handle() {
        cout << "ConcreteStateA.Handle()" << endl;
    }
};

#endif // __CONCRETESTATEA_H
