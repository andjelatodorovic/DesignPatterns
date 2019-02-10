#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

/* kompomenta/component
   u ovom slucaju objedinjuje i prostu i slozenu/kompozicionu komponentu
   poseduje metode za dodavanje/uklanjanje potkomponenti
   destruktor je kreiran da se rekurzivno uklanjaju i potkomponente
   tako da je dovoljno samo izbrisati pocetnu slozenu komponentu */
class Oprema {
protected:
    string m_ime;
    int m_cena;
    vector<Oprema*> m_delovi;
public:
    typedef vector<Oprema*>::iterator OpremaIter;

    Oprema() { }
    Oprema(string ime, int cena) : m_ime(ime), m_cena(cena) {}
    virtual ~Oprema() {
        for (OpremaIter it = m_delovi.begin(); it != m_delovi.end(); ++it) {
            delete *it;
        }
    }
    string dajIme() { return m_ime; }
    void postaviIme(string ime) { m_ime = ime; }
    virtual void dodaj(Oprema *oprema);
    virtual void izbrisi(Oprema *oprema);
    virtual int izracunajCenu();
};

void Oprema::dodaj(Oprema *oprema) {
    m_delovi.push_back(oprema);
}

void Oprema::izbrisi(Oprema *oprema) {
    for (OpremaIter it = m_delovi.begin(); it != m_delovi.end(); ++it) {
        if (*it == oprema) {
            m_delovi.erase(it);
            return;
        }
    }
}

/* operacija - implementirana tako sto rekurzivno zove operaciju/metod izracunajCenu
   na potkomponentama */
int Oprema::izracunajCenu() {
    int cena = m_cena;
    for (OpremaIter it = m_delovi.begin(); it != m_delovi.end(); ++it) {
        cena += (*it)->izracunajCenu();
    }
    return cena;
}

/* kreiramo kompjuter koji ce da bude slozena komponenta, dodamo mu potkomponente
   i pozovemo operaciju, u ovom slucaju to je racunanje cene cele komponente
   koja se izvrsi tako sto se pozove rekurzivno racunanje cene za sve potkomponente */
int main() {
    Oprema *kompjuter = new Oprema("Kompjuter", 0);
    kompjuter->dodaj(new Oprema("Tastatura", 50));
    kompjuter->dodaj(new Oprema("Monitor", 150));
    Oprema* mis = new Oprema("Mis", 30);
    kompjuter->dodaj(mis);
    kompjuter->dodaj(new Oprema("Kuciste", 300));
    cout << "Kompjuter kosta: " << kompjuter->izracunajCenu() << endl;
    /* uklonimo potkomponentu i opet izracunamo cenu */
    kompjuter->izbrisi(mis);
    delete mis;
    cout << "Kompjuter bez misa kosta: " << kompjuter->izracunajCenu() << endl;
    /* dodamo novu potkomponentu i izracunamo cenu */
    kompjuter->dodaj(new Oprema("Mis2", 40));
    cout << "Kompjuter sa novim misem kosta: " << kompjuter->izracunajCenu() << endl;

    delete kompjuter;

    return 0;
}
