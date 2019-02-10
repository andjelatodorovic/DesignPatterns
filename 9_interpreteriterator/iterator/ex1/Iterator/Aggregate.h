#ifndef __AGREGATE_H
#define __AGREGATE_H

#include <vector>

using namespace std;

class Iterator;
/* agregat / kolekcija/zbirka elemenata,
   u njoj cuvamo neki skup elemenata,
   ovo je samo interfejs agregata, i u nasem slucaju imamo samo jedan metod
   za spoljasnju manipulaciju, Add(int) kojim cemo da dodajemo novi element u kolekciju
   ima i fabricki metod CreateIterator kojim se kreira konkretan iterator koji ce da nam
   sluzi da agregat, svaki konkretan agregat treba da implementira ovaj metod
   iterator treba da ima pristup internoj strukturi agregata kako bi mogao da se "seta"
   po kolekciji, ovo je moguce uraditi na vise nacina, u ovom slucaju
   napravicemo apstraktnu klasu Iterator (koju nasledjuju svi konkretni iteratori) prijateljem
   klase Aggregate, na taj nacin ce Iterator moci da poziva zasticeni metod GetData kako bi dobio
   pristup internoj strukturi kolekcije, sve nasledjene klase od Iterator ce moci da koriste neki
   zasticeni/protected metod klase Iterator kojom ce moci da dobiju interne podatke kolekcije */
class Aggregate {
public:
    friend class Iterator;
    virtual Iterator* CreateIterator() = 0;
    virtual void Add(int v) = 0;
protected:
    virtual vector<int>& GetData() = 0;
};

#endif // __AGREGATE_H
