#include "Originator.h"
#include "Caretaker.h"

/* kreiramo subjekat/originator koji ima svoje interno stanje
 i nudi operacije za promenu internog stanja (metod Do())
   nakon izvrsene neke promene u cuvaru podsetnika / caretaker
   dodamo novokreirani podsetnik subjekta, pozivajuci metod createMemento,
   zatim uradim jos neke operacije na subjektu a zatim vratimo neko od prethodnih
   stanja uzimajuci podsetnik iz cuvara podsetnika */
int main() {
    Originator origin;
    Caretaker caretaker;

    origin.Do("Prva linija");
    caretaker.AddMemento(origin.CreateMemento());
    origin.Display();

    origin.Do("Druga linija");
    origin.Display();

    origin.SetMemento(caretaker.GetMemento(0));
    origin.Display();

    origin.Do("Treca linija");
    caretaker.AddMemento(origin.CreateMemento());
    origin.Display();

    return 0;
}
