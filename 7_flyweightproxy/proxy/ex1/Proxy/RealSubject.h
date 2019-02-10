#ifndef __REALSUBJECT_H
#define __REALSUBJECT_H

#include <iostream>
using namespace std;

#include "Subject.h"

/* realni subjekt koji ima neki metod (u ovom slucaju npr. Request()) cije konkretno pozivanje zelimo da odlozimo sto je vise moguce
   jer je 'skupo' u smislu resursa (bilo vremenskih, memorijskih itd), ili pak zelimo da kontrolisemo pristup ovom metodu itd
   zato klijenti ovaj metod pozivaju preko zastupnika/proxy-ja za realnog subjekta */
class RealSubject: public Subject {
public:
    virtual ~RealSubject() {}
    virtual void Request() {
        cout << "RealSubject.Request()" << endl;
    }
};
#endif // __REALSUBJECT_H
