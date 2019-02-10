#ifndef __CONCRETEHANDLER2_H
#define __CONCRETEHANDLER2_H

#include "Handler.h"

/* konkretni razresavac 2 */
class ConcreteHandler2: public Handler {
public:
    ConcreteHandler2() {}
    virtual ~ConcreteHandler2() {}
    void HandleRequest(const Request& request) {
        if (CanHandle(request)) {
            cout << "ConcreteHandler2 handled the request." << endl;
        } else {
            Handler::HandleRequest(request);
        }
    }
    virtual bool CanHandle(const Request& request) {
        // uslovi da ovaj handler moze da razresi
        // trenutni zahtev
        // ovde prosto stavljamo false za ConcreteHandler2
        return false;
    }
};

#endif // __CONCRETEHANDLER2_H

