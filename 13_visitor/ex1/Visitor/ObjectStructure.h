#ifndef __OBJECTSTRUCTURE_H
#define __OBJECTSTRUCTURE_H

#include <vector>
#include <iostream>
using namespace std;

#include "Element.h"

/* objektna struktura / kompozicija
   moze da se sastoji od vise elemenata i moguce je
   pozvati novu operaciju na svim elementima strukture prosledjujuci
   posetioca/visitora putem metoda Accept koji kasnije
   prosledi posetioca svim elementima strukture */
class ObjectStructure {
public:
    typedef vector<Element*>::iterator ElementIter;

    virtual ~ObjectStructure() {
        for (ElementIter it = m_elements.begin(); it != m_elements.end(); ++it) {
            delete *it;
        }
        m_elements.clear();
    }
    virtual void Accept(Visitor& visitor) {
        cout << "ObjectStructure.Accept()" << endl;
        for (ElementIter it = m_elements.begin(); it != m_elements.end(); ++it) {
            (*it)->Accept(visitor);
        }
    }
    virtual void AddElement(Element* element) {
        m_elements.push_back(element);
    }
protected:
    vector<Element*>    m_elements;
};
#endif // __OBJECTSTRUCTURE_H
