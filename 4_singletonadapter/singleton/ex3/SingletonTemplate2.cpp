#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

/* sablon klasa Singleton koja prati unikat obrazac / singleton pattern,
   kod ovog primera koristimo staticki objekat unutar funkcije getInstance koji
   ce biti inicijaliziran prilikom prvog poziva funkcije getInstance,
   u ovom slucaju ne moramo da brinemo o destruktoru
   od standarda C++11 je garantovano da prilikom paralelnog ulaska u deklaraciju
   promenljiva je inicijalizirana pre nego sto se desi izvrsavanje,
   to nam garantuje da ce prvo biti inicijaliziran objekat u static T singleton
   tako da je ovaj kod sasvim zadovoljavajuci sa aspekta paralelizma u C++11 i nije neophodno
   koristiti mutex-e
   Naravno prilikom implementacije unikat obrasca u nekom drugom jeziku (ili drugom standardu C++)
   neophodno je napraviti kod da bude siguran prilikom paralelnog izvrsavanja
   */
template<class T>
class Singleton {
public:
    static T& getInstance() {
        static T singleton;
        return singleton;
    }
private:
    int vrednost;
    ~Singleton();
    Singleton() {}
    Singleton(const Singleton& s) {}
    Singleton& operator=(const Singleton& s) {}
};

/* ovo je test klasa koja sluzi da isprobamo Singleton<T> klasu koja treba da kreira jedinstven
primerak objekta klase Test, posto su konstruktori od klase Test privatni neophodno je
napraviti prijateljem klasu Singleton<Test> kako bi Singleton<Test>::getInstance mogao da kreira
objekat pozivajuci privatni konstruktor od klase Test */
class Test {
private:
    int vrednost;
    Test() { vrednost = brojac++; }
    Test(const Test& t) {  }
    Test& operator=(const Test& t) {  }
    ~Test() {}
public:
    static int brojac;
    friend class Singleton<Test>;
    void koristi() { cout << "koristim Test objekat, vrednost = " << vrednost << endl ; }
};
int Test::brojac = 0;

int main() {
    Test &singleton = Singleton<Test>::getInstance();
    singleton.koristi();
    Test &singleton2 = Singleton<Test>::getInstance();
    singleton2.koristi();

    return 0;
}
