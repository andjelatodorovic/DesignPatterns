#include "ConcreteHandler1.h"
#include "ConcreteHandler2.h"

/* kreiramo lanac razresavaca, rucno ih dodajuci jedan na drugi,
   ovo dodavanje i kreiranje lanca moze da se uradi na vise nacina,
   jedan je da se poput lancane liste dodaje novi element na pocetak/kraj liste
   i da cuvamo samo razresavac koji je koren lanca i na njemu pozivamo metod
   za dodavanje novog razresavaca u listu
   nakon kreiranja lanca prvom u lancu prosledjujemo zahtev koji ce
   da nadje odgovarajuci razresavac koji ce da razresi zahtev */
int main() {
    Handler* handler1 = new ConcreteHandler1();
    Handler* handler2a = new ConcreteHandler2();
    Handler* handler2b = new ConcreteHandler2();
    handler2b->SetSuccessor(handler2a);
    handler2a->SetSuccessor(handler1);

    Request request;
    handler2b->HandleRequest(request);

    delete handler1;
    delete handler2a;
    delete handler2b;

    return 0;
}
