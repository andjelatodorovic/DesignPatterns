#ifndef __CONCRETE_CREATOR_H
#define __CONCRETE_CREATOR_H

#include "Creator.h"

/* konkretan kreator/stvaralac koji ima fabricki metod za stvaranje konkretnog proizvoda */
class ConcreteCreator: public Creator {
public:
    Product* factoryMethod();
};
#endif // __CONCRETE_CREATOR_H
