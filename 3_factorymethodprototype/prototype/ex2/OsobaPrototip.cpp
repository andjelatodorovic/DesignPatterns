#include <cstring>
#include <iostream>

using namespace std;

/* apstraktan prototip, ima apstraktan metod za kloniranje, kloniraj() */
class Osoba {
protected:
    string m_ime;
    string m_prezime;
public:
    virtual Osoba* kloniraj() = 0;
    void setIme(string ime) { m_ime = ime; }
    void setPrezime(string prezime) { m_prezime = prezime; }
    virtual void kaziKoSi() = 0;
};

/* konkretan protitip, implementira metod za kloniranje */
class Naucnik: public Osoba {
public:
    Osoba* kloniraj() {
        Osoba *osoba = new Naucnik();
        osoba->setIme(Osoba::m_ime);
        osoba->setPrezime(Osoba::m_prezime);
        return osoba;
    }
    void kaziKoSi() {
        cout << "Ja sam naucnik " << Osoba::m_ime << " " << Osoba::m_prezime << "." << endl;
    }
};
/* konkretan protitip, implementira metod za kloniranje */
class Inzenjer: public Osoba {
public:
    Osoba* kloniraj() {
        Osoba *osoba = new Inzenjer();
        osoba->setIme(Osoba::m_ime);
        osoba->setPrezime(Osoba::m_prezime);
        return osoba;
    }
    void kaziKoSi() {
        cout << "Ja sam inzenjer " << Osoba::m_ime << " " << Osoba::m_prezime << "." << endl;
    }
};
/* primer koriscenja sablona protitip, kreiramo dva prototipa pozivajuci direktno njihove konstruktore,
   a zatim kreiramo njihove kopije sa metodom za kloniranje, kloniraj, izmenimo kopije (menjajuci im polje ime)
   i prikazemo im stanja */
int main() {
    Osoba *naucnik = new Naucnik();
    naucnik->setIme("Marko");
    naucnik->setPrezime("Markovic");

    Osoba *inzenjer = new Inzenjer();
    inzenjer->setIme("Petar");
    inzenjer->setPrezime("Petrovic");
    cout << "originalne osobe: " << endl;
    naucnik->kaziKoSi();
    inzenjer->kaziKoSi();

    Osoba *klonNaucnika = naucnik->kloniraj();
    klonNaucnika->setIme("Nikola");
    Osoba *klonInzenjera = inzenjer->kloniraj();
    klonInzenjera->setIme("Jovana");
    cout << "klonirane osobe: " << endl;
    klonNaucnika->kaziKoSi();
    klonInzenjera->kaziKoSi();
}
