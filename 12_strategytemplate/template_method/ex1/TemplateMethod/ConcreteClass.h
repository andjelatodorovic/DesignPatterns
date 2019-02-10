#ifndef __CONCRETECLASS_H
#define __CONCRETECLASS_H

#include <iostream>
#include "AbstractClass.h"

using namespace std;

/* konkretna klasa koja implementira operacije koriscenje u sablon metodu / template method
   iz apstraktne klase koju nasledjuje,
   taj metod se ne menja u konkretnoj klasi */
class ConcreteClass: public AbstractClass {
public:
    virtual void PrimitiveOperation1() {
        cout << "ConcreteClass.PrimitiveOperation1()" << endl;
    }
    virtual void PrimitiveOperation2() {
        cout << "ConcreteClass.PrimitiveOperation2()" << endl;
    }
};
#endif // __CONCRETECLASS_H
