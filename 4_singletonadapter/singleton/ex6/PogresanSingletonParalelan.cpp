#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

/* primer koji pokazuje kako moze doci do greske prilikom paralelnog koriscenja singletona koji
   nije 'thread safe' (siguran za paralelno izvrsavanje)
   dve niti/threada paralelno se izvrsavaju i oba pokusavaju da dobiju primerak objekta pozivom
   funkcije getInstance, oba uspevaju da prodju proveru if (s_singleton == NULL) pa samim tim
   oba pozivaju konstruktor da kreira DVE RAZLICITE instance objekta,
   to vidimo posto na ekranu ispisemo polje vrednost i imamo dve razlicite vrednosti 0 i 1 */
class Singleton {
public:
    static Singleton* getInstance() {
        if (s_singleton == NULL) {
                /* dodajemo kod koji ce da uspori izvrsavanje niti pre nego sto se pozove konstruktor
                kako bi i drugi thread mogao da udje u ovaj deo koda */

            for (int i = 0; i < 100000000;i++) { int j = i * i; }
            s_singleton = new Singleton();
        }
        return s_singleton;
    }
    void setvrednost(int vrednost) {
        this->vrednost = vrednost;
    }
    int getvrednost() {
        return this->vrednost;
    }
    void koristi() {
        cout << "Koristim singleton, vrednost = " << vrednost << endl;
    }
private:
    static Singleton* s_singleton;
    int vrednost;
    static int brojac;
    Singleton() {
        vrednost = brojac++ ;
    }
    Singleton(const Singleton& s) { }
    Singleton& operator=(const Singleton& s) {}
};
Singleton* Singleton::s_singleton;
int Singleton::brojac = 0;

void *fnA(void*) {
    Singleton* singleton = Singleton::getInstance();
    singleton->koristi();

}
void *fnB(void* x) {
    Singleton* singleton = Singleton::getInstance();
    singleton->koristi();
}
/* naredni kod kreira dva procesa / threada koji ce paralelno da se izvrsavaju jedan izvrsava kod u funkciji fnA,
drugi u fnB, oba uzimaju primerak objekta Singleton pozivom funkcije getInstance */
int main() {
    srand(time(NULL));
    pthread_t t1;

    pthread_create(&t1, NULL, &fnA, NULL);
    pthread_t t2;
    int x = 2;
    pthread_create(&t2, NULL, &fnB, (void *) &x);
    cout << "main() cekam tredove..." << endl;
    void* result1;
    pthread_join(t1, &result1);
    void* result2;
    pthread_join(t2, &result2);

    cout << "kraj" << endl;

    return 0;
}
