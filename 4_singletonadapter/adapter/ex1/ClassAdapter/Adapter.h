#ifndef __ADAPTER_H
#define __ADAPTER_H

#include "Target.h"
#include "Adaptee.h"
#include <iostream>

/* klasa koja vrsi prilagodjavanje klase Adaptee ciljanom interfejsu,
   apstraktnoj klasi Target,
   vrsi implementaciju svih metoda u interfejsu Target pomocu
   nasledjenih metoda klase koju adaptira Adaptee
   u ovom slucaju treba da implementira metod Request iz interfejsa
   Target a to radi pozivom nasledjenog metoda SpecificRequest iz
   klase Adaptee
   nasledjivanje iz Target je public/javno
   dok je nasledjivanje Adaptee privatno/private jer ne zelimo
   da nasledjene klase od Adapter imaju pristup metodima/poljima
   iz Adaptee */
class Adapter: public Target, private Adaptee {
public:
    void Request() {
        std::cout << "Adapter.Request() called, is using inherited SpecificRequest to complete Request" << std::endl;
        SpecificRequest();
    }
};

#endif // __ADAPTER_H
