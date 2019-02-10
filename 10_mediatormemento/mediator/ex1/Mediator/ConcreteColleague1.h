#ifndef __CONCRETECOLLEAGUE1_H
#define __CONCRETECOLLEAGUE1_H

#include "Colleague.h"

/* konkretan kolega
   implementira metod Send tako sto pozove metod SendMessage na posredniku/medijatoru
   implementira i metod Receive preko koga mu se dopremaju poruke (u nasem slucaju
   ce posrednik pomocu ovog metoda da mu prosledjuje poruke) */
class ConcreteColleague1: public Colleague {
public:
    ConcreteColleague1(Mediator* mediator): Colleague(mediator) {}
    virtual void Send(const string& message) {
        cout << "ConcreteColleague1.Send(" << message << ")" << endl;
        m_mediator->SendMessage(message, this);
    }
    virtual void Receive(const string& message) {
        cout << "ConcreteColleague1.Receive(" << message << ")" << endl;
    }
};

#endif // __CONCRETECOLLEAGUE1_H
