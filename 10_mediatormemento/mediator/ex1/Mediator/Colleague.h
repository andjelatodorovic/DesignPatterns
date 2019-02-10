#ifndef __COLLEAGUE_H
#define __COLLEAGUE_H

#include "Mediator.h"

/* interfejs kolega/ucesnika u komunikaciji
   poseduje metode za slanje Send(msg) i primanje Receive(msg) poruka
   poseduje i referencu na posrednika/mediatora koga koristi prilikom komunikacije
   sa ostalim ucesnicima */
class Colleague {
public:
    Colleague(Mediator* mediator): m_mediator(mediator) {}
    virtual ~Colleague() {}
    virtual void Send(const string& message) = 0;
    virtual void Receive(const string& message) = 0;
protected:
    Mediator*   m_mediator;
};

#endif // __COLLEAGUE_H
