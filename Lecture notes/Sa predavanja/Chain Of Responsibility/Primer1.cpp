//
// Created by Maverick on 4/21/2017.
//

#include <iostream>

using namespace std;

enum Prioritet { NIZAK, SREDNJI, VISOK };

class Upit {
public:
    Upit(string _zahtev, Prioritet _prio) : zahtev(_zahtev), prioritet(_prio){}
    Prioritet getNivoOdgovornosti() { return prioritet; }
    string getZahtev() { return zahtev; }
private:
    string zahtev;
    Prioritet prioritet;
};


class IOsoba{
public:
    IOsoba(string _ime) : ime(_ime){};
    virtual void postaviSledeceg(IOsoba* osoba) { next = osoba; }
    virtual string getIme() { return ime; }
    virtual IOsoba* getNext() { return  next; }
    virtual ~ IOsoba(){}
    virtual void obradi(Upit) = 0;
private:
    string ime;
    IOsoba* next;
};

template <enum Prioritet nivo>

class Osoba : public IOsoba {
public:
    Osoba(string ime) : IOsoba(ime){}
    void obradi(Upit upit) {
        if(upit.getNivoOdgovornosti() == nivo) {
            cout << "Zahtev: " << upit.getZahtev() << " je resio " << getIme() << endl;
            return ;
        }
        cout << "Radnik: " << getIme() << " nije mogao da obradi zahtev. Proseledjeno: " << getNext()->getIme() << endl;
        getNext()->obradi(upit);
    }

};


int main() {
    Osoba<NIZAK>* radnik = new Osoba<NIZAK>("Petar Petkovic");
    Osoba<SREDNJI>* supervizor = new Osoba<SREDNJI>("Miodrag Mikic");
    Osoba<VISOK>* sef = new Osoba<VISOK>("Lazar Stamenkovic");

    radnik->postaviSledeceg(supervizor);
    supervizor->postaviSledeceg(sef);
    sef->postaviSledeceg(NULL);

    Upit zahtev1("Kako da restartujem komp?", NIZAK);
    Upit zahtev2("Kako da instaliram Windows?", SREDNJI);
    Upit zahtev3("Kako da ugradim cooler?", VISOK);

    radnik->obradi(zahtev1);
    radnik->obradi(zahtev2);
    radnik->obradi(zahtev3);

    return 0;

}