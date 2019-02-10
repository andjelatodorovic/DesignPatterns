#ifndef __REFINED_ABSTRACTION_H
#define __REFINED_ABSTRACTION_H

#include "Abstraction.h"

/* prosirena apstrakcija, moze da override-uje/nadjaca metode iz osnovne klase Apstrakcija
   pa na drugaciji nacin da koristi metode unutar implementatora
   u nasem slucaju nismo dali drugaciju implementaciju metoda operation() */
class RefinedAbstraction: public Abstraction {
public:
    RefinedAbstraction(Implementor *implementor) : Abstraction(implementor) {}
    virtual ~RefinedAbstraction() {}
};
#endif // __REFINED_ABSTRACTION_H
