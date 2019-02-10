#ifndef __CREATOR_H
#define __CREATOR_H

#include "Product.h"

/* apstraktni kreator/stvaralac koji u ovom slucaju ima samo jedan fabricki metod
   koji kreira proizvode */
class Creator {
public:
    virtual Product* factoryMethod() = 0;
};
#endif // __CREATOR_H
