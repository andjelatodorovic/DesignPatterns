#ifndef __CONCRETE_PROTOTYPE2_H
#define __CONCRETE_PROTOTYPE2_H

#include "Prototype.h"

/* konkretan prototip koji implementira metod za kloniranje */
class ConcretePrototype2: public Prototype {
public:
    Prototype* clone();
    void use();
};
#endif // __CONCRETE_PROTOTYPE2_H
