#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "ConcreteStateA.h"
#include "ConcreteStateB.h"

/* kontekst
   poseduje neko svoje interno stanje
   u zavisnosti od stanja u kojem se trenutno nalazi zavisi i nacin na koji metodi
   treba da budu uradjeni,
   umesto da imamo u svakom od metoda konktesta neki switch/case kojim cemo da selektujemo
   nacin na koji cemo da uradimo neki metod, u zavisnosti od stanja u kojem se kontekst nalazi,
   mi jednostavno pozovemo na jedinstven nacin (za sva razlicita stanja isti metod) metod na
   konkretnoj instanci nekog konkretnog stanja, a zadatak konkretnog stanja je da ima odgovarajucu
   implementaciju za taj metod koji odgovara ponasanju u tom stanju
   kontekst poseduje atribut koji je objekat stanja koji ima implementiran metod Handle
   kada se pozove metod Request, umesto da se interno pita koje je trenutno stanje konteksta
   mi jednostavno pozovemo method Handle na trenutno postalvljenom konkretnom stanju konteksta
   kontekst ima i metod za promenu stanja, u nasem slucaju imamo samo dva stanja pa ih
   menjamo A, B, A, B... u nasem slucaju prilikom svake promene stanja brisemo i prethodno stanje
   prilikom koriscenja obrasca Stanje pogodno je imati fabriku stanja, sledeci muva obrazac,
   i u tom slucaju stanja mogu biti deljenja izmedju vise konteksta */
class Context {
public:
    Context() {
        m_state = new ConcreteStateA();
    }
    virtual ~Context() { delete m_state; }

    virtual void Request() {
        cout << "Context.Request()" << endl;
        m_state->Handle();
    }
    virtual void ChangeState() {
        State* oldState = m_state;
        if (dynamic_cast<ConcreteStateA*>(m_state)) m_state = new ConcreteStateB();
        else m_state = new ConcreteStateA();
        delete oldState;
    }
protected:
    State*  m_state;
};

#endif // __CONTEXT_H
