#ifndef __CARETAKER_H
#define __CARETAKER_H

#include <vector>

using namespace std;

class Originator;
/* cuvar podsetnika */
class Caretaker {
public:
    virtual ~Caretaker() {
        for (vector<Originator::Memento*>::iterator it = m_memento.begin(); it != m_memento.end(); ++it) {
            delete *it;
        }
    }
    void RestoreState(unsigned int index) {
        if (index < m_memento.size()) m_memento[m_memento.size() - index - 1]->RestoreState();
        else throw("Undefined index");
    }
    void AddMemento(Originator::Memento* memento) {
        m_memento.push_back(memento);
    }
protected:
    vector<Originator::Memento*>    m_memento;
};

#endif // __CARETAKER_H
