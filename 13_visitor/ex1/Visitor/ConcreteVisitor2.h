#ifndef __CONCRETEVISITOR2_H
#define __CONCRETEVISITOR2_H

#include <iostream>
using namespace std;

#include "ConcreteElementA.h"
#include "ConcreteElementB.h"

/* konkretan posetioc / concrete visitor
   za razliku od konkretnog posetioca 1 ovde se pozivaju neke
   operacije na instancama konkretnih klasa */
class ConcreteVisitor2: public Visitor {
public:
    virtual ~ConcreteVisitor2() {}
    virtual void VisitConcreteElementA(ConcreteElementA& element) {
        cout << "ConcreteVisitor2.VisitConcreteElementA()" << endl;
        element.OperationA();
    }
    virtual void VisitConcreteElementB(ConcreteElementB& element) {
        cout << "ConcreteVisitor2.VisitConcreteElementB()" << endl;
        element.OperationB();
    }
};

#endif // __CONCRETEVISITOR1_H
