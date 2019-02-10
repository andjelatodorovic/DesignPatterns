#ifndef __CONCRETESTRATEGYC_H
#define __CONCRETESTRATEGYC_H

#include "Strategy.h"

/* konkretna strategija / concrete strategy
   daje implementaciju metoda AlgorithmInterface
   u nasem slucaju samo prikazujemo da je metod pozvan */
class ConcreteStrategyC: public Strategy {
public:
    virtual void AlgorithmInterface() {
        cout << "ConcreteStrategyC.AlgorithmInterface()" << endl;
    }
};

#endif // __CONCRETESTRATEGYC_H

