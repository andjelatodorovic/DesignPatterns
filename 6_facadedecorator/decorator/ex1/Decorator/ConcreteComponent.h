#ifndef __CONCRETE_COMPONENT_H
#define __CONCRETE_COMPONENT_H

#include <iostream>

#include "Component.h"

/* konkretna komponenta, implementira operaciju koju nasledjuje */
class ConcreteComponent: public Component {
public:
    virtual void operation() {
        std::cout << "ConcreteComponent.operation() executed" << std::endl;
    }
    virtual ~ConcreteComponent() { }
};
#endif // __CONCRETE_COMPONENT_H
