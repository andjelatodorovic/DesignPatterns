
#include "ConcreteCommand.h"
#include "Invoker.h"

/* kreiramo primaoca akcije / Receiver, i konkretnu komandu kojoj
   postavimo primaoca akcije
   zatim kreiramo dva razlicita pokretaca akcije / Invoker kojima
   dodelimo istu konkretnu komandu i nakon toga izazovemo akciju
   na pokretacima akcije / Invoker-ima pozivom metoda Invoke()
   u oba slucaja isti efekat na primaocu ce biti ostvaren jer je
   koriscena ista konkretna komanda */
int main() {
    Receiver* receiver = new Receiver();
    Command* command = new ConcreteCommand();
    command->SetReceiver(receiver);

    Invoker* invokerA = new Invoker();
    Invoker* invokerB = new Invoker();
    invokerA->SetCommand(command);
    invokerB->SetCommand(command);
    cout << "Invoking object invokerA" << endl;
    invokerA->Invoke();
    cout << "Invoking object invokerB" << endl;
    invokerB->Invoke();

    delete invokerA;
    delete invokerB;
    delete command;
    delete receiver;

    return 0;
}
