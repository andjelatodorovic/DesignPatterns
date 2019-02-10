#ifndef __CONCRETE_DECORATOR_H
#define __CONCRETE_DECORATOR_H

#include <iostream>

#include "Decorator.h"

/* konkretna dopuna/dekorator
   implementira jedno svojstvo / nacin na koji ce biti ostvarena operacija
   na ovaj nacin imamo i odvojenost razlicitih implementacija od objekta
   konkretni dekorateri operaciju (u ovom slucaju operation()) implementiraju
   tako sto pozivaju metod operation() na objektu koji obogacuju ali uz to
   imaju i neku dodatnu implementaciju koja predstavlja to svojstvo koje
   konkretna dopuna nudi */
class ConcreteDecorator: public Decorator {
public:
    virtual void operation() {
        std::cout << "ConcreteDecorator.operation()" << std::endl;
        m_component->operation();
    }
    ConcreteDecorator(Component *component) : Decorator(component) {}
    virtual ~ConcreteDecorator() { }
};
#endif // __CONCRETE_DECORATOR_H
