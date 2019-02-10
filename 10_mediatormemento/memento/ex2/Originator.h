#ifndef __ORIGINATOR_H

#include <iostream>
#include <string>

using namespace std;
/* u ovom slucaju subjekt/originator
   ima klasu clanicu Memento/podsetnik
   u ovom slucaju ne izlazemo stanje sacuvano u podsetniku javno putem nekog metod,
   moguce je i prvi primer (ex1) izmeniti kako bi sledio taj princip */
class Originator {
public:
    class Memento {
    public:
        Memento(Originator* originator, const string& state): m_state(state), m_originator(originator) {}
        void RestoreState() { m_originator->m_state = m_state; }
    protected:
        string       m_state;
        Originator*  m_originator;
    };
    Memento* CreateMemento() {
        return new Memento(this, m_state);
    }
    void Do(string newState) { m_state = newState; }
    void Display() { cout << "[Originator] state = " << m_state << endl; }
protected:
    string  m_state;
};

#endif // __ORIGINATOR_H
