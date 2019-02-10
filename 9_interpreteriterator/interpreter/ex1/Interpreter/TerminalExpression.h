#ifndef __TERMINALEXPRESSION_H
#define __TERMINALEXPRESSION_H

#include <iostream>
#include "AbstractExpression.h"

using namespace std;

/* terminalni izraz iz gramatike koju ce interpereter da interpretira
   koji je izvedena klasa abstraktnog izraza / AbstractExpression
   nudi implementaciju metoda Interpret pomocu kojeg interpretira neki jezik
   terminalni izrazi su oni koji se vise ne izvode u gramatici
   koristi se globalno dostupan kontekst context da bi se izraz interpretirao
   npr. kontekst moze da sadrzi trenutne vrednosti nekih promenljivih i trenutni deo
   reci iz jezika koji treba da se interpretira */
class TerminalExpression: public AbstractExpression {
public:
    virtual void Interpret(Context* context) {
        cout << "TerminalExpression.Interpret()" << endl;
    }
};

#endif // __TERMINALEXPRESSION_H
