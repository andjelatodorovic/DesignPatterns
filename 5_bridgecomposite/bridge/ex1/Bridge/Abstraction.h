#ifndef __ABSTRACTION_H
#define __ABSTRACTION_H

#include "Implementor.h"

/* apstrakcija koja definise interfejs koji ima razlicite operacije koje su izvrsene koriscenjem
   implementacije koja je odvojena od same apstrakcije
   metodi apstrakcije su ostvareni pozivajuci konkretne implementacije metoda unutar objekta implementatora
   sadrzanog unutar apstrakcije,
   na ovaj nacin ostvareno je razdvajanje same apstrakcije / interfejsa metoda koje cemo da koristimo
   i njihove implementacije
   unutar destruktora apstrakcije mozemo a i ne moramo da unistimo i objekat implementor,
   zavisno od nacina koriscenja implementora
   u ovom slucaju cemo samostalno da unistimo objekat implementor */
class Abstraction {
protected:
    Implementor *m_implementor;
public:
    Abstraction(Implementor *implementor): m_implementor(implementor) {}
    virtual ~Abstraction() {}
    virtual void operation() {
        m_implementor->operationImpl();
    }

    void setImplementor(Implementor *implementor) {
        m_implementor = implementor;
    }
};
#endif // __ABSTRACTION_H
