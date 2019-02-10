#ifndef __CONCRETECOLLEAGUE2_H
#define __CONCRETECOLLEAGUE2_H

#include "Colleague.h"

/* konkretan kolega
   implementira metod Send tako sto pozove metod SendMessage na posredniku/medijatoru
   implementira i metod Receive preko koga mu se dopremaju poruke (u nasem slucaju
   ce posrednik pomocu ovog metoda da mu prosledjuje poruke) */
class ConcreteColleague2: public Colleague {
public:
    ConcreteColleague2(Mediator* mediator): Colleague(mediator) {}
    virtual void Send(const string& message) {
        cout << "ConcreteColleague2.Send(" << message << ")" << endl;
        m_mediator->SendMessage(message, this);
    }
    virtual void Receive(const string& message) {
        cout << "ConcreteColleague2.Receive(" << message << ")" << endl;
    }
};

#endif // __CONCRETECOLLEAGUE2_H

