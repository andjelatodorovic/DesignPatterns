#include "Context.h"

/* kreiramo kontekst, u konstruktoru ce se postaviti neko pocetno konkretno
   stanje, kada zovnemo metod Request zahtev ce biti prosledjen putem metoda Handle
   na stanju, trenutnom konkretnom stanju da razresi taj zahtev,
   nakon toga promenimo stanje i opet razresimo neki zahtev,
   i mozemo da pratimo tok izvrsavanja */
int main() {
    Context context;

    context.Request();

    context.ChangeState();
    context.Request();

    context.ChangeState();
    context.Request();

    return 0;
}
