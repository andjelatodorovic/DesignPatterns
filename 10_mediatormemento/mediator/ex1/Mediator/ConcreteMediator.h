#ifndef __CONCRETEMEDIATOR_H

#include "ConcreteColleague1.h"
#include "ConcreteColleague2.h"

/* konkretan posrednik / konkretan mediator
   posetuje metod za registrovanje kolega koje ce da komuniciraju, u ovom slucaju
   omogucava se samo komunikacija izmedju dva korisnika kolega1 i kolega2,
   uobicajenije je da posrednik poseduje listu kolega koji medjusobno mogu da komuniciraju
   i da korisnik koji zeli da komunicira sa ostalima se pre toga registruje kod posrednika
   SendMessage metod jednostavno proveri ko je posiljalac poruke i onda prosledi drugom ucesniku */
class ConcreteMediator: public Mediator {
public:
    ConcreteMediator() {}
    virtual ~ConcreteMediator() {}
    virtual void SetColleague1(ConcreteColleague1* concreteColleague) {
        m_concreteColleague1 = concreteColleague;
    }
    virtual void SetColleague2(ConcreteColleague2* concreteColleague) {
        m_concreteColleague2 = concreteColleague;
    }
    virtual void SendMessage(const string& message, Colleague* colleague) {
        cout << "ConcreteMediator.SendMessage(" << message << ", " << colleague << ")" << endl;
        if (colleague == m_concreteColleague1) {
            if (m_concreteColleague2 == NULL) cout << "ConcreteColleague2 not set up" << endl;
            else  m_concreteColleague2->Receive(message);
        } else if (colleague == m_concreteColleague2) {
            if (m_concreteColleague1 == NULL) cout << "ConcreteColleague1 not set up" << endl;
            else m_concreteColleague1->Receive(message);
        }
    }
protected:
    ConcreteColleague1* m_concreteColleague1;
    ConcreteColleague2* m_concreteColleague2;
};

#endif // __CONCRETEMEDIATOR_H
