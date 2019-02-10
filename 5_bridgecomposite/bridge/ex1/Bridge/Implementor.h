#ifndef __IMPLEMENTOR_H
#define __IMPLEMENTOR_H

/* interfejs konkretne implementacije */
class Implementor {
public:
    Implementor() {}
    virtual ~Implementor() {}
    virtual void operationImpl() = 0;
};

#endif // __IMPLEMENTOR_H
