#ifndef __CONCRETE_IMPLEMENTORA_H
#define __CONCRETE_IMPLEMENTORA_H

#include <iostream>

#include "Implementor.h"

/* konkretna implementacija A */
class ConcreteImplementorA: public Implementor {
public:
    ConcreteImplementorA() {}
    virtual ~ConcreteImplementorA() {}
    void operationImpl() {
        std::cout << "Izvrsavam metod operationImpl() unutar konkretnog implementatora A" << std::endl;
    }
};
#endif // __CONCRETE_IMPLEMENTORA_H
