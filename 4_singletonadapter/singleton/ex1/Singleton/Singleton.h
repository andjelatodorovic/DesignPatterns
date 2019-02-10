#ifndef __SINGLETON_H
#define __SINGLETON_H

#include <iostream>

using namespace std;

/* unikat sablon / singleton pattern,
   implementacija teorijskog modela */
class Singleton {
private:
    static Singleton *s_instance;
    /* konstruktori su privatni */
    Singleton() {}
    /* obratiti paznju na implicitni copy konstruktor */
    Singleton(const Singleton& s);
    Singleton& operator=(const Singleton &s);
    /* za destruktor postoji vise varijanti, moguce je
    staviti ga javnog/public ali tada bi svako mogao da
    ga unisti, ili ga postaviti privatnog i registrovati
    destruktora da bude izvrsen prilikom zavrsetka
    aplikacije ukoliko se vraca pointer na objekat,
    ovog problema nema ukoliko se objekat kreira staticki
    unutar funkcije getInstance i vraca referenca na
    objekat,
    sve ove pristupe moguce je videti u ostalim primerima */
public:
    /* imamo staticni javni metod preko koga generisemo
       objekat */
    static Singleton* getInstance() {
        if (s_instance == NULL) {
            s_instance = new Singleton();
        }
        return s_instance;
    }
    void use() {
        cout << "Koristim Singleton objekat" << endl;
    }
};

Singleton* Singleton::s_instance = NULL;
#endif // __SINGLETON_H
