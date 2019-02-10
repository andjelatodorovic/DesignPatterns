#ifndef __DIRECTOR_H
#define __DIRECTOR_H

#include "Builder.h"
#include "Product.h"

/* upravljac / director koji koristi graditelja (builder) da napravi proizvod postavljajuci deo po deo */
class Director {
private:
    Builder *builder;
public:
    Director(Builder *builder) {
        this->builder = builder;
    }
    Product* construct() {
        builder->buildPart();
        return builder->getProduct();
    }
};

#endif // __DIRECTOR_H
