#ifndef __OBSERVER_H
#define __OBSERVER_H

#include "Subject.h"

class Subject;
/* apstraktan posmatrac/observer
   poseduje metod Update(subjekt) preko koga subjekt kojem se desila promena od interesa
   moze da obavesti registrovanog posmatraca o dogadjaju */
class Observer {
public:
    Observer() {}
    virtual ~Observer() {}
    virtual void Update(Subject* subject) = 0;
};

#endif // __OBSERVER_H
