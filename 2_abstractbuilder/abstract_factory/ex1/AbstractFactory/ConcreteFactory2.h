#ifndef __CONCRETE_FACTORY2_H
#define __CONCRETE_FACTORY2_H

#include "AbstractFactory.h"

class ConcreteFactory2: public AbstractFactory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};
#endif // __CONCRETE_FACTORY2_H
