#ifndef __COMPOSITE_H
#define __COMPOSITE_H

#include <iostream>
#include <vector>

#include "Component.h"

using namespace std;

/* slozena/kompoziciona komponenta koja u svom sastavu moze da ima
   vise drugih komponenti, mozemo to da posmatramo i kao stablo
   gde je slozena/kompoziciona komponenta ona koja moze da ima i decu/children
   koja su opet neke komponente
   kompozicija mora da ima i metode za dodavanje i uklanjanje potkomponenti/dece */
class Composite: public Component {
private:
    vector<Component*> m_children;
public:
    typedef vector<Component*>::iterator ChildIt;

    /* moguce je ostaviti destrukciju dece klijentu, tj. da unistenjem
       slozene komponente NE unistavamo i njegove potkomponente/decu */
    virtual ~Composite() {
        /*
        // ukoliko bismo hteli da unistenjem slozene/kompozicione komponente
        // unistimo i potkomponente onda bismo imali sledeci kod
        for (int i = 0; i < m_children.size(); i ++) {
            delete m_children[i];
        }
        */
    }
    virtual void operation() {
        cout << "Composite.operation()" << endl;
        for (ChildIt it = m_children.begin(); it != m_children.end(); ++it) {
            (*it)->operation();
        }
    }
    virtual void add(Component *component) {
        m_children.push_back(component);
    }

    virtual void remove(Component *component) {
        for (ChildIt it = m_children.begin(); it != m_children.end(); ++it) {
            if (*it == component) {
                m_children.erase(it);
                return;
            }
        }
    }

    virtual Component* getChild(int index) {
        if ((unsigned int) index >= m_children.size()) {
            return NULL;
        }
        return m_children[index];
    }
};

#endif // __COMPOSITE_H
