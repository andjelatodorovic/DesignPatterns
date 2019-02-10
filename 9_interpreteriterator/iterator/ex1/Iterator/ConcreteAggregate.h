#ifndef __CONCRETEAGGREGATE_H
#define __CONCRETEAGGREGATE_H

#include "ConcreteIterator.h"

/* konkretni agregat, cuva kolekciju u vektoru
   GetData jednostavno vraca referencu na vektor,
   a CreateIterator kreira konkretan iterator ConcreteIterator */
class ConcreteAggregate: public Aggregate {
public:
    virtual Iterator* CreateIterator() {
        return new ConcreteIterator(this);
    }
    virtual vector<int>& GetData() {
        return m_data;
    }
    virtual void Add(int v) {
        m_data.push_back(v);
    }
protected:
    vector<int> m_data;
};

#endif // __CONCRETEAGGREGATE_H
