#ifndef __MEMENTO_H
#define __MEMENTO_H

#include <string>
#include <iostream>

using namespace std;
/* podsetnik/memento
   putem konstruktora postavljamo interno stanje objekta koje zelimo da sacuvamo
   metodom GetState mozemo da pristupimo tom internom stanju, sto bas i nije dobra praksa
   jer je tako to stanje izlozeno javno */
class Memento {
public:
    Memento(const string& state): m_state(state) {}
    string GetState() { return m_state; }
protected:
    string  m_state;
};

#endif // __MEMENTO_H
