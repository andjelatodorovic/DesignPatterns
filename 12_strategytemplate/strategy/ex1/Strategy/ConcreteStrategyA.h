#ifndef __CONCRETESTRATEGYA_H
#define __CONCRETESTRATEGYA_H

#include "Strategy.h"

/* konkretna strategija / concrete strategy
   daje implementaciju metoda AlgorithmInterface
   u nasem slucaju samo prikazujemo da je metod pozvan */
class ConcreteStrategyA: public Strategy {
public:
    virtual void AlgorithmInterface() {
        cout << "ConcreteStrategyA.AlgorithmInterface()" << endl;
    }
};

#endif // __CONCRETESTRATEGYA_H
