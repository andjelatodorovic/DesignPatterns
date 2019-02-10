#include "ConcreteMediator.h"

/* kreiramo posrednika/mediatora
   dva ucesnika u komunikaciji kolegu1 i kolegu2
   nakon toga posredniku postavimo ucesnike komunikacije setColl1 i setColl2
   posle toga kolega1 posalje poruku, nakon toga kolega 2 i mozemo da vidimo
   rezultate komunikacije */
int main() {
    ConcreteMediator* mediator = new ConcreteMediator();
    ConcreteColleague1* colleague1 = new ConcreteColleague1(mediator);
    ConcreteColleague2* colleague2 = new ConcreteColleague2(mediator);

    mediator->SetColleague1(colleague1);
    mediator->SetColleague2(colleague2);

    colleague1->Send("Pozdrav od kolege C1");
    colleague2->Send("Evo i ja se javljam, tvoj drugar C2");

    delete mediator;
    delete colleague1;
    delete colleague2;

    return 0;
}
