#ifndef __CONCRETECOMMAND_H
#define __CONCRETECOMMAND_H

#include "Command.h"

/* konkretna komanda, nudi implementaciju metoda Execute
   koji pokretac/Invoker poziva na dodeljenoj instanci Komande
   metod Execute je implementiran tako da se izvrsi modifikacija
   primaoca akcije/Receiver-a putem pozivanja metoda Action
   na primaocu akcije,
   to znaci da Komanda poseduje referencu na primaoca akcije/Receiver-a
   (npr. to moze da bude neki Dokument) */
class ConcreteCommand: public Command {
public:
    ConcreteCommand() {}
    virtual ~ConcreteCommand() {}
    virtual void Execute() {
        cout << "Executing command" << endl;
        m_receiver->Action();
    }

    virtual void SetReceiver(Receiver* receiver) {
        m_receiver = receiver;
    }
protected:
    Receiver*   m_receiver;
};

#endif // __CONCRETECOMMAND_H
