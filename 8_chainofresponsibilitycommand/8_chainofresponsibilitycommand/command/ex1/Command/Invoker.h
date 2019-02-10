#ifndef __INVOKER_H
#define __INVOKER_H

/* pokretac komande, zahteva od komande da izvrsi neku operaciju,
   to moze da bude element menija (pa se prilikom klika menija poziva
   komanda da izvrsi neku operaciju) a ista ta komanda moze da bude
   dodeljena nekom drugom pokretacu (npr. dugme koje radi istu tu operaciju
   prilikom klika)
   metod Invoke()/pokreni izaziva izvrsavanje akcije koju definise komanda,
   konkretna komanda se dodeljuje svakom pokretacu, moze preko konstruktora,
   a moze i preko posebnog metoda u nasem slucaju SetCommand
   pa tako u toku izvrsavanja/run-time mozemo da menjamo konkretnu komandu
   dodeljenu nekom pokretacu/Invoker-u */
class Invoker {
public:
    Invoker() {}
    virtual ~Invoker() {}
    virtual void Invoke() {
        if (m_command != NULL) {
            m_command->Execute();
        }
    }
    virtual void SetCommand(Command* command) {
        m_command = command;
    }
protected:
    Command*    m_command;
};

#endif // __INVOKER_H
