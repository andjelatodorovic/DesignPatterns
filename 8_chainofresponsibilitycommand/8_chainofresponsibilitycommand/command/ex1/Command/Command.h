#ifndef __COMMAND_H
#define __COMMAND_H

#include "Receiver.h"

/* apstraktna klasa koja je interfejs Komande
   nudi samo metode Execute koji se poziva na Komandi od strane
   pokretaca akcije/Invoker-a,
   moguce je menjati primaoca akcije/Receiver-a putem metoda
   SetReceiver (npr. dodeliti komandi dokument nad kojim ce
   da vrsi neke konkretne operacije) */
class Command {
public:
    Command() {}
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void SetReceiver(Receiver* receiver) = 0;
protected:
};

#endif // __COMMAND_H
