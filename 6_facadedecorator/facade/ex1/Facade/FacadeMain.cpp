#include "Facade.h"

/* klijent sada ima jednostavno koriscenje APIja koji nudi fasada
   na raspolaganju
   ne mora da brine o gomili stvari o kojima je trebao kada je
   samostalno trebao da ostvari operaciju koriscenjem razlicitih
   podsistema, ceo taj problem je prepusten fasadi koja nudi
   sada limitiran nacin koriscenja podsistema, ali ono sto je
   klijentu potrebno */
int main() {
    Facade facade;
    facade.doComplexWork();

    return 0;
}
