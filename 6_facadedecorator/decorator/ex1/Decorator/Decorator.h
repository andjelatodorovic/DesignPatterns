#ifndef __DECORATOR_H
#define __DECORATOR_H

#include "Component.h"

/* dopuna/dekorator apstraktna klasa koju implementiraju sve konkretne
   dopune/dekorateri
   pomocu dopune/dekoratera mozemo da dodamo komponentama neka svojstva
   bez da pravimo posebne potklase komponente sa tim svojstvom
   ako npr. imamo N svojstava S1,S2,..,SN ukoliko bismo zeleli da imamo
   izvedenu klasu od komponente sa svakim podskupom svojstava
   morali bismo da imamo otprilike 2^N (zavisno da li racunamo i bez svojstava)
   izvedenih potklasa
   sa dekoraterom/dopunom ovo je moguce izvesti sa N izvedenih konkretnih
   dopuna/dekoratera koji je za sebe zasebna celina / postuje princip
   jedinstvene odgovornosti - jedna klasa - jedna odgovornost /
   i mozemo po potrebi da ih dodamo komponenti i tako joj pridruzimo zeljeno
   svojstvo
   posto sve dopune/dekorateri implementiraju isti interfejs / Decorator
   moramo paziti na koji nacin cemo izvrsiti ugnjezdenost poziva
   istog metoda i paziti na redosled dodeljivanja dekoratera
   klasa Decorator poseduje objekat tipa Component koji cemo da obogatimo
   novim svojstvom
   */
class Decorator: public Component {
public:
    virtual void operation() = 0;
    Decorator(Component *component) : m_component(component) {}
    virtual ~Decorator() { if (m_component != NULL) delete m_component; }
protected:
    /* objekat komponente koji cemo da obogatimo novim svojstvom */
    Component *m_component;
};
#endif // __DECORATOR_H
