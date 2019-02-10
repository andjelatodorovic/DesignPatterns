#ifndef __PROTOTYPE_H
#define __PROTOTYPE_H

/* apstraktan prototip koji ima metod za kloniranje objekta */
class Prototype {
public:
    virtual Prototype* clone() = 0;
    virtual void use() = 0;
};
#endif // __PROTOTYPE_H
