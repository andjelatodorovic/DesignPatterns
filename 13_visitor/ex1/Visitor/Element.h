#ifndef __ELEMENT_H
#define __ELEMENT_H

#include "Visitor.h"

/* apstraktni element
   nudi metod Accept koji ce da nasledjuju svi konkretni elementi
   a putem kojeg se prosledjuju posetioci */
class Element {
public:
    virtual ~Element() {}
    virtual void Accept(Visitor& visitor) = 0;
};

#endif // __ELEMENT_H
