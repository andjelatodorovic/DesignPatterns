#ifndef __CONCRETE_FACTORY1_H
#define __CONCRETE_FACTORY1_H

#include "AbstractFactory.h"

class ConcreteFactory1: public AbstractFactory {
public:
    AbstractProductA* createProductA();
    AbstractProductB* createProductB();
};
#endif // __CONCRETE_FACTORY1_H
