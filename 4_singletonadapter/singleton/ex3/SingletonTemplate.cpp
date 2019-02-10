#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

/* napravimo neki exception koji cemo da vracamo ukoliko dodje
   do greske prilikom instanciranja Singleton objekta */
class SingletonAllocationException: public exception {
    const char* what() const throw() {
        return "Greska pri alokaciji Singletona";
    }
};

/* sablon klasa Singleton koja prati unikat obrazac / singleton pattern,
   kod ovog primera imamo thread safe pristup (siguran kod prilikom izvrsavanja vise paralelnih niti/threadova)
   koriscenjem mutexa i registrujemo pomocu naredbe atexit(..) koja ce komanda da bude izvrsena prilikom kraja
   aplikacije, u ovom slucaju registrujemo funkciju koja ce da izbrise kreirani singleton objekat,
   sa pthread_mutex_lock(&lock) postavljamo uslov da naredni kod moze da izvrsi u svakom trenutku samo jedan thread
   proces, a sa pthread_mutex_unlock(&lock) oslobadjamo taj deo koda da moze naredni proces da udje posle komande
   pthread_mutex_lock(&lock)
   ovo je samo da vidite kao pristup, nece biti trazeno na ispitu
   Singleton<T> klasa kreira unikatni objekat klase T, posto konstruktori od T treba da budu privatni
   neophodno je napraviti prijateljem klasu Singleton */
template<class T>
class Singleton {
public:
    static T* getInstance() {
        try {
            if (s_singleton == NULL) {
                pthread_mutex_lock(&lock);

                if (s_singleton == NULL) {
                    s_singleton = new T();
                    atexit(deleteInstance);
                }
                pthread_mutex_unlock(&lock);
            }
        } catch (...) {
            throw new SingletonAllocationException();
        }
        return s_singleton;
    }
private:
    static T* s_singleton;
    static pthread_mutex_t lock;
    static void deleteInstance() {
        delete s_singleton;
    }
    ~Singleton();
    Singleton() {}
    Singleton(const Singleton& s) {}
    Singleton& operator=(const Singleton& s) {}
};
template<class T> T* Singleton<T>::s_singleton;
template<class T> pthread_mutex_t Singleton<T>::lock = PTHREAD_MUTEX_INITIALIZER;

/* ovo je test klasa koja sluzi da isprobamo Singleton<T> klasu koja treba da kreira jedinstven
primerak objekta klase Test, posto su konstruktori od klase Test privatni neophodno je
napraviti prijateljem klasu Singleton<Test> kako bi Singleton<Test>::getInstance mogao da kreira
objekat pozivajuci privatni konstruktor od klase Test */
class Test {
private:
    int vrednost;
    Test() { vrednost = brojac++; }
    Test(const Test& t) {}
    Test& operator=(const Test& t) {}
    ~Test() {}
public:
    static int brojac;
    friend class Singleton<Test>;
    void koristi() { cout << "koristim Test objekat, vrednost = " << vrednost << endl ; }
};
int Test::brojac = 0;

void *fnA(void*) {
    Test* singleton = Singleton<Test>::getInstance();
    singleton->koristi();

}
void *fnB(void* x) {
    Test* singleton = Singleton<Test>::getInstance();
    singleton->koristi();
}

/* naredni kod kreira dva procesa / threada koji ce paralelno da se izvrsavaju jedan izvrsava kod u funkciji fnA,
drugi u fnB, oba kreiraju objekat tipa Test pomocu Singleton obrasca, prilikom svakog poziva konstruktora
za */
int main() {
    srand(time(NULL));
    pthread_t t1;
    /* sa ovim kreiramo jedan proces/nit /thread koji ce startovati i izvrsavati kod u funkciji fnA,
      neophodno je proslediti pokazivac na funkciju i pokazivac na parametre u ovom slucaju NULL */
    pthread_create(&t1, NULL, &fnA, NULL);
    pthread_t t2;
    int x = 2;
    /* kao i malopre samo sto imamo pokazivac na parametar x koji je cast-ovan u void* */
    pthread_create(&t2, NULL, &fnB, (void *) &x);
    cout << "main() cekam tredove..." << endl;
    void* result1;
    pthread_join(t1, &result1);
    void* result2;
    pthread_join(t2, &result2);

    cout << "kraj" << endl;

    return 0;
}
