#ifndef __TARGET_H
#define __TARGET_H

/* ciljani interfejs koji zelimo da podrzava klasa
   koju treba da adaptiramo */
class Target {
public:
    virtual void Request() = 0;
};
#endif // __TARGET_H
