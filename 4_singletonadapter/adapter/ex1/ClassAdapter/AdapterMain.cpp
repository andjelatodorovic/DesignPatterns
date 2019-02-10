#include "Adapter.h"

/* kreiramo instancu klase Adapter i pozivamo
   adaptirani metod Request */
int main() {
    Target *target = new Adapter();
    target->Request();

    delete target;
    return 0;
}
