#ifndef __SUBJECT_H
#define __SUBJECT_H

/* zajednicki interfejs realnog subjekta (klasa RealSubject) za koga pravimo zastupnika/proxy i
   zastupnika/proxy-ja (Proxy klasa) */
class Subject {
public:
    virtual ~Subject() {}
    virtual void Request() = 0;
};

#endif // __SUBJECT_H
