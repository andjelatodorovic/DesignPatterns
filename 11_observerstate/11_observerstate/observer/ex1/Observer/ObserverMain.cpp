#include "ConcreteSubject.h"
#include "ConcreteObserver.h"

/* kreiramo subjekta koji moze da trpi promene internog stanja i obavesti
   registrovane posmatrace o promeni
   kreiramo dva konkretna posmatraca, registrujemo ih kod subjekta
   promenimo stanje subjekta i pozovemo metod Notify spolja
   subjekt ce pri pozivu ovog metoda da pozove Update kod svih registrovanih posmatraca */
int main() {
    Subject* subject = new ConcreteSubject();
    Observer* observer1 = new ConcreteObserver();
    Observer* observer2 = new ConcreteObserver();

    subject->Attach(observer1);
    subject->Attach(observer2);

    subject->SetState("Novo stanje A");
    subject->Notify();

    subject->Detach(observer1);
    subject->SetState("Novo stanje B");
    subject->Notify();

	delete subject;
	delete observer1;
	delete observer2;
    return 0;
}
