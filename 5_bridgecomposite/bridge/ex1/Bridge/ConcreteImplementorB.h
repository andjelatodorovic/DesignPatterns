#ifndef __CONCRETE_IMPLEMENTORB_H
#define __CONCRETE_IMPLEMENTORB_H

#include <iostream>

#include "Implementor.h"

/* konkretna implementacija B */
class ConcreteImplementorB: public Implementor {
public:
    ConcreteImplementorB() {}
    virtual ~ConcreteImplementorB() {}
    void operationImpl() {
        std::cout << "Izvrsavam metod operationImpl() unutar konkretnog implementatora B" << std::endl;
    }
};
#endif // __CONCRETE_IMPLEMENTORB_H
