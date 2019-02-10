#include <memory>

#include "ConcreteComponent.h"
#include "ConcreteDecorator.h"


int main() {
   /* kreiramo komponentu component koja je objekat tipa ConcreteDecorator cijem
      konstruktoru je prosledjen objekat tipa ConcreteComponent */
    std::unique_ptr<Component> component(new ConcreteDecorator(new ConcreteComponent()));
    /* pozivamo operaciju na komponenti koja je u stvari omotac/wrapper oko konkretnog
    objekta, pozivamo metod konkretnog dekoratera koji ce unutar sebe da pozove i metod
    objekta tipa ConcreteComponent */
    component->operation();
    /* kreiramo drugi objekat tipa ConcreteComponent i pozivamo operaciju */
    Component *component2 = new ConcreteComponent();
    component2->operation();
    /* kreiramo 'obogacenu' komponentu sa novim svojstvom koje nudi ConcreteDecorator
    dopuna, konstruktoru prosledjujemo objekat koji zelimo da obogatimo */
    Component *enhancedComponent = new ConcreteDecorator(component2);
    /* i pozivamo operaciju na obogacenom objektu */
    enhancedComponent->operation();

    delete enhancedComponent;

    return 0;
}
