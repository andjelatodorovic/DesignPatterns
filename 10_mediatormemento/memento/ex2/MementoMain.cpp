#include "Originator.h"
#include "Caretaker.h"

/* simulacija kao u prvom primeru */
int main() {
    Originator origin;
    Caretaker caretaker;

    origin.Do("Prva linija");
    caretaker.AddMemento(origin.CreateMemento());
    origin.Display();

    origin.Do("Druga linija");
    origin.Display();

    caretaker.RestoreState(0);
    origin.Display();

    origin.Do("Treca linija");

    caretaker.AddMemento(origin.CreateMemento());
    origin.Display();

    return 0;
}
