#ifndef __NONTERMINALEXPRESSION_H
#define __NONTERMINALEXPRESSION_H

#include <iostream>
#include "AbstractExpression.h"

using namespace std;

/* neterminalni izraz iz gramatike koju ce interpereter da interpretira
   koji je izvedena klasa abstraktnog izraza / AbstractExpression
   nudi implementaciju metoda Interpret pomocu kojeg interpretira neki jezik
   neterminalni izrazi su oni koji se dalje izvode u gramatici sve do terminalnih izraza
   koristi se globalno dostupan kontekst context da bi se izraz interpretirao
   npr. kontekst moze da sadrzi trenutne vrednosti nekih promenljivih i trenutni deo
   reci iz jezika koji treba da se interpretira */
class NonterminalExpression: public AbstractExpression {
public:
    virtual void Interpret(Context* context) {
        cout << "NonterminalExpression.Interpret()" << endl;
    }
};

#endif // __NONTERMINALEXPRESSION_H

