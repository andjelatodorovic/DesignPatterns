#ifndef __CONCRETE_FLYWEIGHT_H
#define __CONCRETE_FLYWEIGHT_H

#include <iostream>

#include "Flyweight.h"
/* konkretna muva koja je deljiva
   kod konstrukcije muva / flyweight objekata neophodno je uspesno odvojiti interno state / intrinsic state
   koje moze biti deljivo i nezavisno od konteksta u kojem se konkretne muve koriste,
   i spoljasnje stanje koje zavisi od konteksta u kojem se ta muva deli i koje svaki korisnik konkretne muve
   to spoljasnje stanje moze da prosledi objektu konkretne muve */
class ConcreteFlyweight: public Flyweight {
public:
    ConcreteFlyweight(const string& intrinsicState) : Flyweight(intrinsicState) {}
    virtual ~ConcreteFlyweight() {}
    virtual void Operation(const string& extrinsicState) {
        std::cout << "ConcreteFlyweight.Operation(" << extrinsicState << "), intrinsicState = " << GetIntrinsicState() << std::endl;
    }
};

#endif // __CONCRETE_FLYWEIGHT_H
