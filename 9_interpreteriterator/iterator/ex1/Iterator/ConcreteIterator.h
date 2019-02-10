#ifndef __CONCRETEITERATOR_H
#define __CONCRETEITERATOR_H

#include "Iterator.h"

/* konkretan iterator, implementira sve metode nasledjene
   iz klase Iterator koristeci internu strukturu agregata
   koju dobija pozivajuci zasticeni metod GetData */
class ConcreteIterator: public Iterator {
public:
    ConcreteIterator(Aggregate* aggregate): Iterator(aggregate) {
        m_current = 0;
    }
    virtual ~ConcreteIterator() {}
    virtual void First() {
        m_current = 0;
    }
    virtual void Next() {
        if ((unsigned int) m_current < GetData().size()) m_current++;
        else throw("Next() Out of bounds.");
    }
    virtual bool IsDone() {
        return (unsigned int) m_current >= GetData().size();
    }
    virtual int CurrentItem() {
        if ((unsigned int) m_current < GetData().size())
            return GetData()[m_current];
        throw("CurrentItem() Out of bounds.");
    }
private:
    int     m_current;
};

#endif // __CONCRETEITERATOR_H
