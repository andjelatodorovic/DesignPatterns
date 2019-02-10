#ifndef __HANDLER_H
#define __HANDLER_H

#include <iostream>
#include "Request.h"

using namespace std;

/* lanac odgovornosti - ima apstraktnu klasu razresavaca / handler
   u kojem se kreira i lanac razresavaca, pomocu atributa naredni_upravljac/m_successor
   kada upravljac dobije neki zahtevi da razresi (Request request) konkretni upravljaci
   implementiraju metod HandleRequest gde vrse resavanje zahteva na sebi svojstven nacin
   ako su u stanju da razrese zahtev u suprotnom zovu HandleRequest od nasledjene klase
   (u ovom slucaju Handler) koji jednostavno prosledi zahtev narednom upravljacu
   u lancu koji je kreiran
   ako ne postoji naredni upravljac u lancu moze da vrati neki specifican rezultat ili
   da jednostavno ignorise ovu situaciju kada zahtev nije razresen ni od jednog konkretnog
   razresavaca */
class Handler {
public:
    Handler(): m_successor(NULL) {}
    virtual ~Handler() {}
    virtual void HandleRequest(const Request& request) {
        if (m_successor != NULL) {
            m_successor->HandleRequest(request);
        } else {
            // proverili smo sve upravljace zahteva
            // mozemo da ne radimo nista
            // mozemo da damo exception
            // mozemo da vratimo neki uopsten rezultat kao odgovor
            // ..
            cout << "Request can't be handled." << endl;
        }
    }
    virtual void SetSuccessor(Handler* successor) {
        this->m_successor = successor;
    }
protected:
    Handler*    m_successor;
};

#endif // __HANDLER_H
