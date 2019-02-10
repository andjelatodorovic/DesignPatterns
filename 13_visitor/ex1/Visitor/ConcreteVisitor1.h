#ifndef __CONCRETEVISITOR1_H
#define __CONCRETEVISITOR1_H

#include <iostream>
using namespace std;

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"

/* konkretan posetioc / concrete visitor
   u sustini predstavlja jednu novu konkretnu operaciju/metod dodan
   hierarhiji elemenata, u ovom slucaju konkretnim elementima A i B
   mora da implementira nasledjene metode i u oba slucaja samo prikazuje
   naziv metoda koji se poziva
   metodima je prosledjena i instanca konkretne klase tako da posetilac
   moze da koristi metode na elementu kako bi implementirao tu operaciju
   neophodno je nekad da posetilac ima pristup internim (zasticenim,
   privatnim) podacima elementa. To je moguce postici metodima na konkretnim
   elementima kojima se dobija pristup internoj strukturi, time se vrsi onda
   eksponiranje/izlaganje unutrasnjosti elementa spolja, a drugi nacin
   je da se konkretni posetioci nacine prijateljem klase konkretnog elementa
   to kasnije komplikuje dodavanje novih posetioca */
class ConcreteVisitor1: public Visitor {
public:
    virtual ~ConcreteVisitor1() {}
    virtual void VisitConcreteElementA(ConcreteElementA& element) {
        cout << "ConcreteVisitor1.VisitConcreteElementA()" << endl;
    }
    virtual void VisitConcreteElementB(ConcreteElementB& element) {
        cout << "ConcreteVisitor1.VisitConcreteElementB()" << endl;
    }
};

#endif // __CONCRETEVISITOR1_H
