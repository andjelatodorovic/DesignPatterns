#ifndef __UNSHAREDCONCRETEFLYWEIGHT_H
#define __UNSHAREDCONCRETEFLYWEIGHT_H

#include <iostream>

#include "Flyweight.h"
/* konkretne muva koja nije deljiva */
class UnsharedConcreteFlyweight: public Flyweight {
public:
    UnsharedConcreteFlyweight(const string& intrinsicState): Flyweight(intrinsicState) {}
    void Operation(const string& extrinsicState) {
        std::cout << "UnsharedConcreteFlyweight.Operation(" << extrinsicState << "), intrinsicState = " << GetIntrinsicState() << std::endl;
    }
};

#endif // __UNSHAREDCONCRETEFLYWEIGHT_H

