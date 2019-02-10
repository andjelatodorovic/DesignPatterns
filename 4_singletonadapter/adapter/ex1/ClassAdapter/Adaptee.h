#ifndef __ADAPTEE_H
#define __ADAPTEE_H

#include <iostream>

/* klasa koju treba da adaptiramo interfejsu Target,
   poseduje metode koji ne odgovaraju metodima Target,
   zato nam je potreban adapter koji ce nam omoguciti da ovu klasu
   Adaptee koristimo kao vidljiv interfejs Target,
   implementacija metoda iz Target koju radi Adapter se vrsi
   pomocu dostupnih metoda iz Adaptee */
class Adaptee {
public:
    void SpecificRequest() {
        std::cout << "Adaptee.SpecificRequest() called" << std::endl;
    }
};
#endif // __ADAPTEE_H

