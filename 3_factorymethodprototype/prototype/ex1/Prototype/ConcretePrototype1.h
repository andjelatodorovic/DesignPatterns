#ifndef __CONCRETE_PROTOTYPE1_H
#define __CONCRETE_PROTOTYPE1_H

#include "Prototype.h"

/* konkretan prototip koji implementira metod za kloniranje */
class ConcretePrototype1: public Prototype {
public:
    Prototype* clone();
    void use();
};
#endif // __CONCRETE_PROTOTYPE1_H
