#ifndef __CONCRETEHANDLER1_H
#define __CONCRETEHANDLER1_H

#include "Handler.h"

/* konkretni razresavac 1, implementira metod za razresenje zahteva,
   HandleRequest tako sto se pita da li je u mogucnosti da razresi trenutni
   zahtev, ako nije u stanju da razresi zahtev zove HandleRequest od nasledjene
   klase (Handler) koja ce da se pobrine da prosledi zahtev narednom
   razresavacu u lancu */
class ConcreteHandler1: public Handler {
public:
    ConcreteHandler1() {}
    virtual ~ConcreteHandler1() {}
    void HandleRequest(const Request& request) {
        if (CanHandle(request)) {
            cout << "ConcreteHandler1 handled the request." << endl;
        } else {
            Handler::HandleRequest(request);
        }
    }
    virtual bool CanHandle(const Request& request) {
        // uslovi da ovaj handler moze da razresi
        // trenutni zahtev
        // ovde prosto stavljamo true za ConcreteHandler1
        return true;
    }
};

#endif // __CONCRETEHANDLER1_H
