
#include <map>
#include <string>
#include <iostream>

using namespace std;

class IUcesnik;
/* subjekt / subject
   moze da promeni interno stanje, promeni se trenutna vrednost aukcije */
class IAukcija {
public:
    IAukcija() {}
    virtual ~IAukcija() {}
    virtual void DodajUcesnika(IUcesnik& ucesnik) = 0;
    virtual void IzbaciUcesnika(IUcesnik& ucesnik) = 0;
    virtual int DajVrednost() const = 0;
    virtual void PostaviVrednost(int vrednost) = 0;
protected:
    virtual void ObavestiUcesnike() = 0;
};
/* posmatrac / observer
   metod Update je Obavesti */
class IUcesnik {
public:
    virtual void Obavesti(const IAukcija& aukcija) = 0;
};
/* konkretan subject / concrete subject
   implementira metode za registrovanje/odregistrovanje posmatraca
   kao i obavestavanje registrovanih posmatraca o dogadjajima od interesa, u ovom slucaju kada se
   pozove metod PostaviVrednost koji menja vrednost aukcije, interno se poziva zasticeni metod ObavestiUcesnik
   koji prodje kroz listu registrovanih posmatraca/observers/ucesnika i na njima pozove metod Obavesti  */
class CAukcija: public IAukcija {
public:
    typedef map<IUcesnik* const, IUcesnik* const> UcesniciMap;
    CAukcija(int pocetnaVrednost): m_vrednost(pocetnaVrednost) {}
    virtual ~CAukcija() {}
    virtual void DodajUcesnika(IUcesnik& ucesnik) {
        m_ucesnici.insert(UcesniciMap::value_type(&ucesnik, &ucesnik));
    }
    virtual void IzbaciUcesnika(IUcesnik& ucesnik) {
        m_ucesnici.erase(&ucesnik);
    }
    virtual int DajVrednost() const { return m_vrednost; }
    virtual void PostaviVrednost(int vrednost) {
        cout << "Aukcija.PostaviVrednost(" << vrednost << "): stara vrednost aukcije <" << m_vrednost << "> nova vrednost <" << vrednost << ">" << endl;
        m_vrednost = vrednost;
        ObavestiUcesnike();
    }
protected:
    int             m_vrednost;
    UcesniciMap     m_ucesnici;
    virtual void ObavestiUcesnike() {
        for (UcesniciMap::iterator it = m_ucesnici.begin(); it != m_ucesnici.end(); ++it) {
            (*it).first->Obavesti(*this);
        }
    }
};
/* konkretan posmatrac / concrete observer */
class CUcesnik: public IUcesnik {
public:
    CUcesnik() {}
    virtual ~CUcesnik() {}
    virtual void Obavesti(const IAukcija& aukcija) {
        cout << "CUcesnik.Obavesti(" << aukcija.DajVrednost() << ")" << endl;
        m_stanjeAukcije = aukcija.DajVrednost();
    }
protected:
    int     m_stanjeAukcije;
};
/* kreiramo aukciju nekoliko konkretnih ucesnika i izvrsimo promenu vrednosti aukcije i pratimo
   kako su obavestavani posmatraci/ucesnici */
int main() {
    IAukcija* aukcija = new CAukcija(100);
    IUcesnik* ucesnik1 = new CUcesnik();
    IUcesnik* ucesnik2 = new CUcesnik();
    IUcesnik* ucesnik3 = new CUcesnik();

    aukcija->DodajUcesnika(*ucesnik1);
    aukcija->DodajUcesnika(*ucesnik2);
    aukcija->DodajUcesnika(*ucesnik3);
    aukcija->PostaviVrednost(200);

    aukcija->IzbaciUcesnika(*ucesnik2);
    aukcija->PostaviVrednost(300);

    aukcija->IzbaciUcesnika(*ucesnik1);
    aukcija->PostaviVrednost(400);

    aukcija->IzbaciUcesnika(*ucesnik3);
    aukcija->PostaviVrednost(500);

    delete aukcija;
    delete ucesnik1;
    delete ucesnik2;
    delete ucesnik3;

    return 0;
}
