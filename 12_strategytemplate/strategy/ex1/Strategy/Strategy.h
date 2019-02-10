#ifndef __STRATEGY_H
#define __STRATEGY_H

#include <iostream>

using namespace std;

/* apstraktna strategija / strategy
   poseduje metod AlgorithmInterface kojim se resava neki problem
   razlicite konkretne strategije mogu da ponude sustinski razlicite
   implementacije ovog metoda,
   bilo u razlicitoj efikasnosti, bilo u razlicitim efektima koje
   taj metod moze da izazove na kontekstu */
class Strategy {
public:
    virtual void AlgorithmInterface() = 0;
    virtual ~Strategy() { }
};

#endif // __STRATEGY_H
