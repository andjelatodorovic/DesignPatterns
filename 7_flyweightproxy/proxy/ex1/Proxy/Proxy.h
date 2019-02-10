#ifndef __PROXY_H
#define __PROXY_H

#include <iostream>
using namespace std;

#include "RealSubject.h"

/* zastupnik/proxy za realni subjekt, klijent vidi realni objekat preko ovog 'omotaca'/wrappera za RealSubject i poziva
   metod Request na proxiju, proxy ovaj metod implementira tako sto vrsi cache-iranje podataka, ili proveru pristupa
   ili racunanje nekog medju rezultata pre nego sto pozove konkretan metod Request na pravom objektu tipa RealSubject
   za koga je posredni. Zato je neophodno da proxy ima interno ima referencu na objekat tipa RealSubject ciju instancu
   cemo da napravimo tek kada nam je neophodna da bi se konkretan metod Request pozvao na njemu */
class Proxy: public Subject {
public:
    Proxy(): m_subject(NULL) {}
    virtual ~Proxy() { if (m_subject != NULL) delete m_subject; }
    virtual void Request() {
        cout << "Proxy.Request()" << endl;
        if (m_subject == NULL) {
            m_subject = new RealSubject();
        }
        m_subject->Request();
    }
protected:
    Subject*    m_subject;
};
#endif // __PROXY_H
