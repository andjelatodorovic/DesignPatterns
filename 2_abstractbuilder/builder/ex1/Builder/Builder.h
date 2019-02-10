#ifndef __BUILDER_H
#define __BUILDER_H

#include "Product.h"

/* apstraktan graditelj / abstract builder */
class Builder {
public:
    virtual void buildPart() = 0;
    virtual Product* getProduct() = 0;
};
#endif // __BUILDER_H
