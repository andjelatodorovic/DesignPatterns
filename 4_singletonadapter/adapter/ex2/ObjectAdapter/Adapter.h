#ifndef __ADAPTER_H
#define __ADAPTER_H

#include "Target.h"
#include "Adaptee.h"
#include <iostream>

/* klasa koja vrsi prilagodjavanje klase Adaptee ciljanom interfejsu,
   apstraktnoj klasi Target,
   vrsi implementaciju svih metoda u interfejsu Target pomocu
   javnih metoda koje poziva na objektu klase Adaptee
   sto znaci da ima pristup instanci objekta Adaptee
   u ovom slucaju treba da implementira metod Request iz interfejsa
   Target a to radi pozivom metoda SpecificRequest od objekta tipa Adaptee */
class Adapter: public Target {
private:
    Adaptee *adaptee;
public:
    Adapter() {
        adaptee = new Adaptee();
    }
    ~Adapter() { delete adaptee; }
    void Request() {
        std::cout << "Adapter.Request() called, is using SpecificRequest method of Adaptee object to complete Request" << std::endl;
        adaptee->SpecificRequest();
    }
};

#endif // __ADAPTER_H
