#include <iostream>

#include "RefinedAbstraction.h"
#include "ConcreteImplementorA.h"
#include "ConcreteImplementorB.h"

using namespace std;

/* testiranje obrasca most/bridge */
int main() {
    /* kreiramo konkretnog implementatora A i prosledimo ga apstrakciji i pozovemo
       metod operation() na apstrakciji,
       koristice implementaciju konkretnog implementora A da realizuje operaciju */
    Implementor *concreteImplementorA = new ConcreteImplementorA();
    Abstraction *abstractionA = new RefinedAbstraction(concreteImplementorA);
    abstractionA->operation();

    /* kreiramo konkretnog implementatora B i prosledimo ga apstrakciji i pozovemo
       metod operation() na apstrakciji,
       koristice implementaciju konkretnog implementora B da realizuje operaciju */
    Implementor *concreteImplementorB = new ConcreteImplementorB();
    Abstraction *abstractionB = new RefinedAbstraction(concreteImplementorB);
    abstractionB->operation();

    /* promenimo implementatora za apstrakciju A i pozovemo operation(),
        sada apstrakcijaA koristi implementaciju konkretnog implementora B,
        u runtime-u/toku izvrsavanja smo zamenili implementaciju,
        sto nije moguce tako lako izvesti da smo koristili princip nasledjivanja
        i tako imali razlicite implementacije metoda */
    abstractionA->setImplementor(concreteImplementorB);
    abstractionA->operation();

    /* u ovom slucaju samostalno vodimo racuna o brisanju implementora,
     u destruktoru apstrakcija ne brisemo implementora, moguce je znaci
     da implementor bude deljen izmedju vise konkretnih apstrakcija */
    delete concreteImplementorA;
    delete concreteImplementorB;
    delete abstractionA;
    delete abstractionB;

    return 0;
}
