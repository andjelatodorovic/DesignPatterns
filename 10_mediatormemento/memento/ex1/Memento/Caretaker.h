#ifndef __CARETAKER_H
#define __CARETAKER_H

#include <vector>
#include "Memento.h"

using namespace std;

/* cuvar stanja/ caretaker
   cuva listu kreiranih podsetnika/memento
   moguce je uzeti neki podsetnik iz istorije kreiranih podsetnika
   i na taj nacin vratiti stanje objekta unazad kroz istoriju,
   imati opciju undo */
class Caretaker {
public:
    virtual ~Caretaker() {
        for (vector<Memento*>::iterator it = m_memento.begin(); it != m_memento.end(); ++it) {
            delete *it;
        }
    }
    Memento* GetMemento(unsigned int index = 0) {
        if (index < m_memento.size()) return m_memento[m_memento.size() - index - 1];
        return NULL;
    }
    void AddMemento(Memento* memento) {
        m_memento.push_back(memento);
    }
protected:
    vector<Memento*>    m_memento;
};

#endif // __CARETAKER_H
