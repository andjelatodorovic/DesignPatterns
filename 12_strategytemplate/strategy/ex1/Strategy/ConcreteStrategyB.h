#ifndef __CONCRETESTRATEGYB_H
#define __CONCRETESTRATEGYB_H

#include "Strategy.h"

/* konkretna strategija / concrete strategy
   daje implementaciju metoda AlgorithmInterface
   u nasem slucaju samo prikazujemo da je metod pozvan */
class ConcreteStrategyB: public Strategy {
public:
    virtual void AlgorithmInterface() {
        cout << "ConcreteStrategyB.AlgorithmInterface()" << endl;
    }
};

#endif // __CONCRETESTRATEGYB_H
