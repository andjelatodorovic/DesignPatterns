#ifndef __CONTEXT_H
#define __CONTEXT_H

#include <iostream>
#include "Strategy.h"

using namespace std;

/* kontekst
   poseduje objekat konkretne strategije koji realizuje neki algoritam koji ce
   konktekst da koristi da bi resio neki problem,
   konkretna strategija moze da se prosledi preko konstruktora, ali i da se izmeni
   tokom izvrsavanja preko metoda SetStrategy,
   u nasem slucaju izmena strategije dovodi do brisanja prethodne,
   konkretne strategije su pogodne da budu realizovane sledeci muva/flyweight obrazac
   i onda da preko konkretne fabrike dobijamo instance konkretnih strategija
   koje bi bile deljenje izmedju vise razlicitih konteksta
   metod ContextInterface u kontekstu treba da resi neki problem i koristi
   dodeljenu strategiju i metod AlgorithmInterface da prosledi problem da ga resi */
class Context {
public:
    Context(Strategy* strategy): m_strategy(strategy) {}
    virtual ~Context() { if (m_strategy != NULL) delete m_strategy; }
    virtual void ContextInterface() {
        cout << "Context.ContextInterface()" << endl;
        if (m_strategy == NULL) cout << "ERROR: strategy not set up" << endl;
        else m_strategy->AlgorithmInterface();
    }
    virtual void SetStrategy(Strategy *strategy) {
        if (m_strategy != NULL) delete m_strategy;
        m_strategy = strategy;
    }

protected:
    Strategy*    m_strategy;
};

#endif // __CONTEXT_H
