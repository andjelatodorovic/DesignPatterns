#ifndef __RECEIVER_H
#define __RECEIVER_H

#include <iostream>

using namespace std;

/* primalac akcija/nad kojim se realizuju konkretni efekti komande,
   to moze da bude neki dokument (npr. komanda za paste ce na dokumentu da doda kopirani
   tekst)
   u nasem slucaju primalac/receiver ima metod za manipulaciju nad njim to je Action() */
class Receiver {
public:
    Receiver() { }
    virtual ~Receiver() {}
    virtual void Action () {
        cout << "Receiver.Action()" << endl;
    }
};

#endif // __RECEIVER_H
