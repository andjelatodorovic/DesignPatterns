#ifndef __CONCRETEELEMENTA_H
#define __CONCRETEELEMENTA_H

#include <iostream>
using namespace std;

#include "Element.h"

/* konkretan element A
   nove operacije ovoj klasi dodane su koriscenjem konkretnih posetilaca
   mora da implementira nasledjeni metod Accept gde na prosledjenom
   posetiocu pozove metod koji tretira instance ove konkretne klase
   preko metoda Accept se prosledjuje ta nova operacija koja ce biti izvrsena
   na konkretnim elementima, a koja je predstavljena u obliku prosledjenog
   konkretnog posetioca/visitora */
class ConcreteElementA: public Element {
public:
    virtual ~ConcreteElementA() {}
    virtual void Accept(Visitor& visitor) {
        cout << "ConcreteElementA.Accept()" << endl;
        visitor.VisitConcreteElementA(*this);
    }
    virtual void OperationA() {
        cout << "ConcreteElementA.OperationA()" << endl;
    }
};

#endif // __CONCRETEELEMENTA_H
