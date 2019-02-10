#ifndef __ABSTRACTEXPRESSION_H
#define __ABSTRACTEXPRESSION_H

#include "Context.h"

/* apstraktna klasa svih izraza koji mogu da se nadju u gramatici,
   ako se radi o gramatici za aritmeticke izraze mozemo da imamo:
   E->E+E
   E->E*E
   E->(E)
   E->ime_promenljive    (u ovom slucaju ime_promenljive bi bio naziv neke promenljive/terminalni izraz)
   E->vrednost           (u ovom slucaju vrednost je neka konstanta)
   i za vrednost i za naziv promenljivih bi bili dati neki regularni izrazi koji definisu
   kako se generise vrednost (realan broj) ili naziv promenljive */
class AbstractExpression {
public:
    virtual ~AbstractExpression() {}
    virtual void Interpret(Context* context) = 0;
};

#endif // __ABSTRACTEXPRESSION_H
