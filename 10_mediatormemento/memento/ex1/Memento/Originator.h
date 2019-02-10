#ifndef __ORIGINATOR_H

#include "Memento.h"
/* originator/subjekat
   poseduje neko interno stanje koje ne zeli da izlaze spolja,
   kako bismo sacuvali interno stanje tokom evolucije objekta
   kreiramo memento/podsetnik, koristeci metod CreateMemento, koji ce da sacuva trenutno
   interno stanje objekta
   da bismo vratili stanje objekta na neko prethodno koristimo metod SetMemento
   koji koristeci prosledjeni memento/podsetnik postavi trenutno interno stanje
   objekta na ono koje je sacuvano u podsetniku/mementu */
class Originator {
public:
    Memento* CreateMemento() {
        return new Memento(m_state);
    }
    void SetMemento(Memento* m) {
        m_state = m->GetState();
    }
    void Do(string newState) { m_state = newState; }
    void Display() { cout << "[Originator] state = " << m_state << endl; }
protected:
    string  m_state;
};

#endif // __ORIGINATOR_H
