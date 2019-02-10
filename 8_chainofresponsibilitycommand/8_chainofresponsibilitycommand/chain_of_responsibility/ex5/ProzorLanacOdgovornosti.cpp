#include <iostream>
#include <vector>

using namespace std;

/* request / zahtev, u ovom slucaju simulacija nekog GUI dogadjaja */
class CDogadjaj {
public:
    CDogadjaj(const string& ime, const string& podaci): m_ime(ime), m_podaci(podaci) {}
    virtual ~CDogadjaj() {}
    friend ostream& operator<<(ostream& out, const CDogadjaj& dogadjaj) {
        out << "[" << dogadjaj.m_ime << "] <" << dogadjaj.m_podaci << ">";
        return out;
    }
private:
    string  m_ime;
    string  m_podaci;
};

class IProzor;
/* razresavac koji ima samo implementaciju metoda koji koristimo prilikom razresavanja zahteva,
   lanac nije kreiran unutar ovog razresavaca vec unutar klijenata koji su medjusobno
   povezani */
class CUpravljacDogadjajem {
public:
    CUpravljacDogadjajem() {}
    virtual void Izvrsi(const IProzor& metaDogadjaja, const CDogadjaj& dogadjaj);
};
/* handler/razresavac ujedno i klijent, interno kreira razresavac dogadjajem pa na taj nacin enkapsulira i razresavac,
   lista je kreirana medjusobno povezujuci IProzor objekte koji treba da simuliraju hijerarhiju grafickih elemenata / GUI elemenata,
   ovde imamo i kompoziciju, svaki prozor moze da ima dodeljen konkretan razresavac dogadjajem (npr. neki graficki elementi ce
   ce da reaguju na klik misem, neki ne) u slucaju da se desio neki dogadjaj na nekom prozoru objektu tipa IProzor, ako je
   njemu dodeljen razresavac tim dogadjajem onda ce da ga razresi, u suprotnom ce da ga prosledi prozoru koji je otac te komponente
   (npr. imamo aplikaciju koja ima svoj panel, unutar panela su neki frejmovi, jedan frejm ima unutar sebe opet neki panel koji
    sadrzi dugme) kada se klikne na dugme ono moze da ima vec implementiran razresavac za dogadjaj klik misem, u suprotnom
    taj dogadjaj prosledjuje panelu unutar koga se nalazi, a ovaj ako ne reaguje na klik prosledjuje frejmu u koji je smesten itd)*/
class IProzor {
public:
    typedef vector<IProzor*>::iterator DecaIter;
    IProzor(const string& tip, const string& ime, IProzor* otac = NULL, CUpravljacDogadjajem *upravljacDogadjajem = NULL)
        : m_ime(ime), m_tip(tip), m_otac(otac), m_upravljacDogadjajem(upravljacDogadjajem) {
        if (otac != NULL) {
            otac->DodajDete(this);
        }
    }
    virtual ~IProzor() {
        cout << "brisem " << m_tip << "," << m_ime << endl;
        for (DecaIter it = m_deca.begin(); it != m_deca.end(); ++it) {
            delete *it;
        }
    }
    /* metod Handle Request */
    virtual bool Klikni(const CDogadjaj& dogadjaj) {
        if (m_upravljacDogadjajem != NULL) {
            m_upravljacDogadjajem->Izvrsi(*this, dogadjaj);
            return true;
        } else {
            if (m_otac != NULL) {
                return m_otac->Klikni(dogadjaj);
            }
            return false;
            /*
            for (DecaIter it = m_deca.begin(); it != m_deca.end(); ++it) {
                if (*it != NULL) {
                    if ((*it)->Klikni(dogadjaj)) return true;
                }
            }
            return false;
            */
        }
    }
    virtual void DodajUpravljac(CUpravljacDogadjajem* upravljac) {
        m_upravljacDogadjajem = upravljac;
    }
    friend ostream& operator<<(ostream& out, const IProzor& prozor) {
        out << "TIP [" << prozor.m_tip << "] IME <" << prozor.m_ime << ">";
        return out;
    }
protected:
    IProzor*                m_otac;
    string                  m_ime;
    string                  m_tip;
    vector<IProzor*>        m_deca;
    CUpravljacDogadjajem*   m_upravljacDogadjajem;
    virtual void DodajDete(IProzor *prozor) {
        m_deca.push_back(prozor);
    }
};

void CUpravljacDogadjajem::Izvrsi(const IProzor& metaDogadjaja, const CDogadjaj& dogadjaj) {
    cout << "[DOGADJAJ IZVRSEN]\n\t" << metaDogadjaja << "\n\t" << dogadjaj << endl;
}
/* kreiramo neku simulaciju GUI aplikacije gde elementi cine drvo, ciji je koren komponenta aplikacija
   kada se prosledi neki dogadjaj nekoj komponenti taj dogadjaj biva prosledjen setajuci se ka korenu kreiranog
   stabla sve dok ne naidjem na komponentu koja ima dodeljen razresavac tim dogadjajem */
int main() {
    CUpravljacDogadjajem* upravljac = new CUpravljacDogadjajem();
    IProzor* aplikacija = new IProzor("PROZOR", "Aplikacija v0.1");
    aplikacija->DodajUpravljac(upravljac);
    IProzor* panel = new IProzor("PANEL", "Glavni panel", aplikacija, upravljac);
    IProzor* meni = new IProzor("MENI", "Glavni meni", aplikacija);
    IProzor* meniElementOtvoriFajl = new IProzor("MENI ELEMENT", "Meni Element Otvori Fajl", meni, upravljac);
    IProzor* meniElementSacuvajFajl = new IProzor("MENI ELEMENT", "Meni Element Sacuvaj Fajl", meni);
    IProzor* meniElementIzadji = new IProzor("MENI ELEMENT", "Meni Element Izadji", meni, upravljac);
    IProzor* dugme1 = new IProzor("DUGME", "OK", panel, upravljac);
    IProzor* dugme2 = new IProzor("DUGME", "CANCEL", panel);
    dugme2->Klikni(CDogadjaj("Klik Levim Dugmetom", "(100, 200)"));
    dugme1->Klikni(CDogadjaj("Klik Desnim Dugmetom", "(150, 220)"));
    meniElementIzadji->Klikni(CDogadjaj("Klik Levim Dugmetom", "(50, 20)"));
    meniElementSacuvajFajl->Klikni(CDogadjaj("Klik Levim Dugmetom", "(40, 40)"));

    delete aplikacija;
    delete upravljac;

    return 0;
}
