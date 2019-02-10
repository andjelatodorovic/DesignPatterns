#include "ConcreteCreator.h"
#include "ConcreteProduct.h"

Product* ConcreteCreator::factoryMethod() {
    return new ConcreteProduct();
}
