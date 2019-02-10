#ifndef __MEDIATOR_H
#define __MEDIATOR_H

#include <iostream>
#include <cstring>

#include "Colleague.h"

using namespace std;

class Colleague;

/* mediator / posrednik
   apstraktna klasa, nudi metode koji omogucavaju da korisnici, kolete / Colleague
   komuniciraju medjusobno,
   tako se broj medjusobnih veza za komunikaciju izmedju n ucesnika redukuje sa
   n * (n - 1) / 2 na samo n veza (veze izmedju konkretnih posrednika/mediatora i kolega/Collegaues)
   interfejs nudi jedan metod koji se koristi za slanje poruka SendMessage gde se kao parametri
   stavljaju poruka koju korisnik/kolega salje i sam posiljalac colleague
   ovaj metod SendMessage pozivaju kolege da bi poslali poruku drugim ucesnicima */
class Mediator {
public:
    virtual void SendMessage(const string& message, Colleague* colleague) = 0;
};
#endif // __MEDIATOR_H
