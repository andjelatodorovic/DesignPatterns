#ifndef __FACADE_H
#define __FACADE_H

#include <iostream>

#include "Class1.h"
#include "Class2.h"
#include "Class3.h"

/* umesto da klijent sam koristi 'haoticnu' kombinaciju
   podsistema i time poveca sanse da napravi gresku,
   napravimo interfejs fasada kojim cemo da klijentu
   napravimo dostupno nekoliko metoda
   koji su potrebni klijentu a za realizaciju tih metoda
   fasada ce koristiti podsisteme
   na ovaj nacin stepen slobode koriscenja podsistema
   je limitiran za klijenta, dostupno mu je samo sto
   API fasada nudi, naravno uvek je moguce prosiriti
   kolekciju metoda koju nudi fasada kada za to postoji
   potreba od strane klijenta */
class Facade {
public:
    virtual void doComplexWork() {
        Class1 c1;
        Class2 c2;
        Class3 c3;
        std::cout << "Facade.doComplexWork()" << std::endl;
        c1.do1();
        c2.do2();
        c3.do3();
    }
};
#endif // __FACADE_H
