#ifndef __ABSTRACT_FACTORY_H
#define __ABSTRACT_FACTORY_H

#include "AbstractProductA.h"
#include "AbstractProductB.h"

class AbstractFactory {
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
};
#endif // __ABSTRACT_FACTORY_H
