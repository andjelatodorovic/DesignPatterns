#ifndef __ITERATOR_H
#define __ITERATOR_H

#include <vector>

#include "Aggregate.h"

using namespace std;

/* apstraktna klasa koju nasledjuju svi iteratori,
   ima zasticeni metod GetData koji nasleduju svi konkretni iteratori
   a koji im sluzi da pristupe internim podacima agregata i tako mogu
   da realizuju obilazak kolekcije
   interfejs iteratora nudi neke klasicne metode za iterator:
   First - da se postavi iterator (ili jos kursor) na pocetak agregata,
   Next - da predje na naredni element, IsDone - da pitamo da li smo
   dosli do kraja kolekcije, CurrentItem - vraca trenutni element
   kolekcije na kojoj se iterator/kursor nalazi */
class Iterator {
public:
    Iterator(Aggregate* const aggregate): m_aggregate(aggregate) {}
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual int CurrentItem() = 0;
protected:
    Aggregate*  m_aggregate;
    virtual vector<int>& GetData() {
        return m_aggregate->GetData();
    }
};
#endif // __ITERATOR_H
