#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

/* ispravno napisan Singleton obrazac koji radi ispravno i prilikom paralelnog koriscenja
  u funkciji getInstance pre nego sto uradimo proveru da li je objekat vec kreiran i pozovemo konstruktor
  zakljucamo mutex kako bismo bili sigurni da taj deo koda moze da izvrsi maksimalno jedan thread u svakom
  trenutku */
class Singleton {
public:
    static Singleton* getInstance() {
        pthread_mutex_lock(&lock);
        if (s_singleton == NULL) {
                for (int i = 0; i < 100000000;i++) { int j = i * i; }
            s_singleton = new Singleton();
            atexit(deleteInstance);
        }
        pthread_mutex_unlock(&lock);
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
    Singleton() { vrednost = brojac++ ; cout << "B " << vrednost << endl; }
    Singleton(const Singleton& s) { }
    Singleton& operator=(const Singleton& s) {}
    static void deleteInstance() {
        delete s_singleton;
    }

    static pthread_mutex_t lock;
};
Singleton* Singleton::s_singleton;
int Singleton::brojac = 0;
pthread_mutex_t Singleton::lock = PTHREAD_MUTEX_INITIALIZER;

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
