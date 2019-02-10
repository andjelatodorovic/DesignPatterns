#ifndef __COMPONENT_H
#define __COMPONENT_H

/* komponenta koja ima razlicite operacije
   moguce je imati metode za dodelu, uklanjanje potkomponenti
   vec u ovoj apstraktnoj klasi komponente a ne u izvedenoj Composite
   ali u tom slucaju bi i proste komponente/listovi Leaf nasledili iste
   metode i morali bi da ih nadjacamo/override-ujemo i upravljamo/handle-ujemo
   taj slucaj ili sa izuzecima/exception ili na neki drugi nacin jer ne smemo
   da dozvolimo dodavanje ili uklanjanje potkomponenti od prostih komponenti
   drugi nacin je da sve komponente tretiramo kao slozene i omogucimo im
   da mogu da dobiju potkomponente, u tom slucaju bi se kao prosta komponenta
   tretirao onaj koji nema potkomponente, ali bi mu tip bio jednak kako i
   onima koji imaju potkomponente
   u nasem slucaju metode za dodavanje/uklanjanje potkomponenti nalaze se
   samo u Composite */
class Component {
public:
    virtual void operation() = 0;
    virtual ~Component() {}
};

#endif // __COMPONENT_H
