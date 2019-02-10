#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;
/* ovde koristimo kod slican kao u IspravanSingletonParalelan.cpp samo sto koristimo tzv duplo proveravanje,
 prvo proveravanje if (s_singleton == NULL) nije pod mutex_lock i moze da se izvrsava paralelno ali nakon toga
 stavljamo zakljucavanje da bi samo jedan thread mogao da izvrsava kod i onda opet radimo istu proveru
 if (s_singleton == NULL) i tek onda pozivamo konstruktor
    na ovaj nacin smanjujemo opterecenje za threadove koje je prouzrokovano ako ceo kod u getInstance
    stavimo pod mutex */
class Singleton {
public:
    static Singleton* getInstance() {
        if (s_singleton == NULL) {
            pthread_mutex_lock(&lock);
            if (s_singleton == NULL) {
                s_singleton = new Singleton();
                atexit(deleteInstance);
            }
            pthread_mutex_unlock(&lock);
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
