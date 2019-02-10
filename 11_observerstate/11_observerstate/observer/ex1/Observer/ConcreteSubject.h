#ifndef __CONCRETESUBJECT_H
#define __CONCRETESUBJECT_H

#include <iostream>
#include <string>

#include "Subject.h"

using namespace std;
/* konkretan subjekt,
   implementira virtuelne metode
   u ovom slucaju SetState je implementiran tako da prilikom promene stanja
   ne poziva se automatski Notify na subjektu,
   vec je to zadatak korisnika konkretnog subjekta da nakon poziva SetState
   pozove Notify ako misli da je bitno da posmatraci budu obavesteni o dogadjaju */
class ConcreteSubject: public Subject {
public:
    ConcreteSubject() {}
    virtual ~ConcreteSubject() {}
    virtual string GetState() {
        return m_state;
    }
    virtual void SetState(const string& state) {
        cout << "ConcreteSubject.SetState(" << state << ")" << endl;
        m_state = state;
    }
protected:
    string  m_state;
};

#endif // __CONCRETESUBJECT_H
