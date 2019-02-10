#ifndef __CONCRETEELEMENTB_H
#define __CONCRETEELEMENTB_H

#include <iostream>
using namespace std;

#include "Element.h"

/* konkretan element B
   nove operacije ovoj klasi dodane su koriscenjem konkretnih posetilaca
   mora da implementira nasledjeni metod Accept gde na prosledjenom
   posetiocu pozove metod koji tretira instance ove konkretne klase
   preko metoda Accept se prosledjuje ta nova operacija koja ce biti izvrsena
   na konkretnim elementima, a koja je predstavljena u obliku prosledjenog
   konkretnog posetioca/visitora */
class ConcreteElementB: public Element {
public:
    virtual ~ConcreteElementB() {}
    virtual void Accept(Visitor& visitor) {
        cout << "ConcreteElementB.Accept()" << endl;
        visitor.VisitConcreteElementB(*this);
    }
    virtual void OperationB() {
        cout << "ConcreteElementB.OperationB()" << endl;
    }
};

#endif // __CONCRETEELEMENTB_H

