#ifndef __CONCRETEOBSERVER_H
#define __CONCRETEOBSERVER_H

#include <iostream>
#include <string>

#include "Observer.h"

using namespace std;

/* konkretan posmatrac
   metod Update je implementiran tako da prikaze da je izvrsen i sacuva
   interno stanje subjekta koje je najsvezije */
class ConcreteObserver: public Observer {
public:
    ConcreteObserver(): m_state("") {}
    virtual ~ConcreteObserver() {}
    virtual void Update(Subject* subject) {
        cout << "ConcreteObserver.Update(" << subject->GetState() << ")" << endl;
        m_state = subject->GetState();
    }
protected:
    string      m_state;
};

#endif // __CONCRETEOBSERVER_H
