#include <cstring>
#include <iostream>
#include <map>
#include <memory>

/* koristi standard c++11 pa je neophodno kompajlirati sa opcijom -std=c++11 */

using namespace std;

/* apstraktan prototip, ima metod za kloniranje kloniraj */
class Objekat {
public:
    virtual void prikazi() = 0;
    virtual Objekat* kloniraj() = 0;
};
/* konkretan prototip */
class Film: public Objekat {
private:
    string m_ime;
public:
    Objekat* kloniraj() {
        cout << "Kloniram film.." << endl;
        Film *film = new Film();
        film->m_ime = m_ime;
        return film;
    }
    string dajIme() { return m_ime; }
    void postaviIme(string ime) { m_ime = ime; }
    void prikazi() {
        cout << "Ovo je film " << m_ime << "." << endl;
    }
};
/* konkretan prototip */
class MuzickiCD: public Objekat {
private:
    string m_naslov;
public:
    Objekat* kloniraj() {
        cout << "Kloniram muzicki CD.." << endl;
        MuzickiCD *muzickiCD = new MuzickiCD();
        muzickiCD->m_naslov = m_naslov;
        return muzickiCD;
    }
    string dajNaslov() { return m_naslov; }
    void postaviNaslov(string naslov) { m_naslov = naslov; }
    void prikazi() {
        cout << "Ovo je muzicki CD " << m_naslov << "." << endl;
    }
};
/* konkretan prototip */
class Predstava: public Objekat {
private:
    string m_naslov;
public:
    Objekat* kloniraj() {
        cout << "Kloniram predstavu.." << endl;
        Predstava *predstava = new Predstava();
        predstava->m_naslov = m_naslov;
        return predstava;
    }
    string dajNaslov() { return m_naslov; }
    void postaviNaslov(string naslov) { m_naslov = naslov; }
    void prikazi() {
        cout << "Ovo je predstava " << m_naslov << "." << endl;
    }
};
/* ovde cuvamo kolekciju prototipova za svaki konkretan prototip,
   kolekcija se cuva u mapi prototipovi koja mapira tip konkretnog prototipa (TipObjekta)
   u jedinstven primerak objekta tog konkretnog prototipa,
   ima i metod dajObjekat koji vraca konkretan objekat klonirajuci odgovarajuci prototip */
class FabrikaPrototipova {
public:
    enum TipObjekta {FILM, CD, PREDSTAVA};
    static map<TipObjekta, unique_ptr<Objekat> > prototipovi;
    static void init() {
        prototipovi[FILM] = (unique_ptr<Objekat>) new Film();
        prototipovi[CD] = (unique_ptr<Objekat>) new MuzickiCD();
        prototipovi[PREDSTAVA] = (unique_ptr<Objekat>)new Predstava();
    }
    static Objekat* dajObjekat(TipObjekta tipObjekta) {
        return prototipovi[tipObjekta]->kloniraj();
    }
};

map<FabrikaPrototipova::TipObjekta, unique_ptr<Objekat> > FabrikaPrototipova::prototipovi;

/* primer koriscenja sablona prototip gde u klasi cuvamo kolekciju prototipa koje
   kloniramo kako bismo pravili instance objekata */
int main() {
    FabrikaPrototipova::init();
    Objekat *film = FabrikaPrototipova::dajObjekat(
                        FabrikaPrototipova::FILM);
    Objekat *cd = FabrikaPrototipova::dajObjekat(
                        FabrikaPrototipova::CD);
    Objekat *predstava = FabrikaPrototipova::dajObjekat(
                        FabrikaPrototipova::PREDSTAVA);
    ((Film*) film)->postaviIme("Tesna koza");
    film->prikazi();
    ((MuzickiCD*) cd)->postaviNaslov("Mala nocna muzika");
    cd->prikazi();
    ((Predstava*) predstava)->postaviNaslov("Gospodja ministarka");
    predstava->prikazi();

    return 0;
}
