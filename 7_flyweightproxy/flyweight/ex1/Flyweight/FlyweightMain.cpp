#include "FlyweightFactory.h"
#include "UnsharedConcreteFlyweight.h"

/* testiramo koriscenje muva uzorka,
   koristimo fabriku muva da kreiramo instance muva tipa koji zelimo prosledjujuci
   fabrickom metodu fabrike muva kljuc po kome cemo da biramo tip instance muve koja nam treba
   kada pozivamo operaciju na instanci muve prosledjujemo i spoljasnje stanje / kontekst u kojem
   se ta konkretna muva koristi
   primer poseduje i instancu muve koja nije deljiva / UnsharedConcreteFlyweight */
int main() {
    FlyweightFactory flyweightFactory;

    Flyweight *flyweight1 = flyweightFactory.GetFlyweight("Flyweight 1");
    Flyweight *flyweight2 = flyweightFactory.GetFlyweight("Flyweight 2");
    cout << "Executing Operation() on Flyweight 1" << endl;
    flyweight1->Operation("Extrinsic State 1");
    cout << "Executing Operation() on Flyweight 2" << endl;
    flyweight2->Operation("Extrinsic State 2");

    UnsharedConcreteFlyweight *unsharedFlyweight = new UnsharedConcreteFlyweight("Unshared Flyweight");
    cout << "Executing Operation() on Unshared Flyweight" << endl;
    unsharedFlyweight->Operation("Extrinsic State Unshared");

    delete unsharedFlyweight;

    return 0;
}
