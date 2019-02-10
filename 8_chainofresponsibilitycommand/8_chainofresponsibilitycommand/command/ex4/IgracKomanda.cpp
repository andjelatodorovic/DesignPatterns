#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

class CIgrac;
/* konkretna komanda, ime metod Execute putem kojeg se prosledjuju i parametri za izvrsenje operacije
   primaoc akcije su igraci, instance CIgrac, nad kojim komanda poziva metod m_akcija sa parametrima podaci,
   metod clan klase koji ce poziva na igracu je prosledjen komandi putem konstruktora */
class CKomandaIgraca {
public:
    CKomandaIgraca(CIgrac* igrac = NULL, void (CIgrac:: *akcija) (const string&) = NULL): m_igrac(igrac), m_akcija(akcija) {}
    virtual ~CKomandaIgraca() { cout << "brisem komandu" << endl; }
    void Izvrsi(string podaci = "") {
        if (m_igrac != NULL && m_akcija != NULL) {
            (m_igrac->*m_akcija)(podaci);
        }
    }
protected:
    CIgrac*                     m_igrac;
    void (CIgrac:: *m_akcija)(const string&);
};
/* primaoc akcije / receiver koji ima razlicite metode clanice koje realicuju neke akcije/operacije nad
   primaocem/receiver-om
   pokretac akcije je integrisan unutar primaoca, metod Invoke je u stvari IzvrsiAkciju
   na ovaj nacin mozemo da imamo razlicite instance konkretnih igraca koji ce razlicito da reaguju na
   metod IzvrsiAkciju (koji sada igra ulogu Invoke) koji koristi komandu da se izvrsi akcija na samom primaocu
   ovde imamo nestandardan nacin primene obrasca Komanda */
class CIgrac {
public:
    CIgrac(const string& ime = "", CKomandaIgraca* komanda = NULL): m_ime(ime), m_komanda(komanda) {}
    virtual ~CIgrac() {
        cout << "brisem igraca " << m_ime << endl;
        if (m_komanda != NULL) delete m_komanda;
    }
    virtual void Trci(const string& podaci = "") {
        cout << "Igrac " << m_ime << " trci [" << podaci << "]" << endl;
    }
    virtual void Cucni(const string& podaci = "") {
        cout << "Igrac " << m_ime << " cuci [" << podaci << "]" << endl;
    }
    virtual void Kazi(const string& podaci = "") {
        cout << "Igrac " << m_ime << " govori [" << podaci << "]" << endl;
    }
    virtual void Skace(const string& podaci = "") {
        cout << "Igrac " << m_ime << " skace [" << podaci << "]" << endl;
    }
    virtual void RegistrujKomandu(CKomandaIgraca* komanda) {
        if (m_komanda != NULL) delete m_komanda;
        m_komanda = komanda;
    }
    virtual void IzvrsiAkciju(const string& podaci = "") {
        if (m_komanda != NULL) {
            m_komanda->Izvrsi(podaci);
        }
    }
protected:
    string              m_ime;
    CKomandaIgraca*     m_komanda;
};
/* nemamo izdvojenog pokretaca akcije/Invoker-a to je simuliranu unutar glavnog programa,
   kreiramo nekoliko igraca i njima dodelimo razlicite konkretne komande prosledjujuci razlicite
   metode clanice klase CIgrac,
   sada ce razliciti igraci da imaju razlicite manifestacije prilikom poziva istog metoda IzvrsiAkciju
   u kojem se koristi komanda da se ostvari neka operacija
   tokom izvrsenja programa igracima je moguce promeniti konkretnu komandu pa samim tim i nacin reagovanja
   prilikom poziva metoda IzvrsiAkciju */
int main() {
    vector<CIgrac*> igraci;
    CIgrac* igrac;
    igrac = new CIgrac("Aca");
    igrac->RegistrujKomandu(new CKomandaIgraca(igrac, &CIgrac::Trci));
    igraci.push_back(igrac);
    igrac = new CIgrac("Braca");
    igrac->RegistrujKomandu(new CKomandaIgraca(igrac, &CIgrac::Cucni));
    igraci.push_back(igrac);
    igrac = new CIgrac("Caca");
    igrac->RegistrujKomandu(new CKomandaIgraca(igrac, &CIgrac::Kazi));
    igraci.push_back(igrac);
    igrac = new CIgrac("Daca");
    igrac->RegistrujKomandu(new CKomandaIgraca(igrac, &CIgrac::Skace));
    igraci.push_back(igrac);
    igrac = new CIgrac("Gaca");
    igrac->RegistrujKomandu(new CKomandaIgraca(igrac, &CIgrac::Trci));
    igraci.push_back(igrac);

    srand(time(NULL));
    for (vector<CIgrac*>::iterator it = igraci.begin(); it != igraci.end(); ++it) {
        ostringstream out;
        out << "(" << rand() % 256 << ", " << rand() % 256 << ")";
        (*it)->IzvrsiAkciju(out.str());
    }
    igraci[2]->RegistrujKomandu(new CKomandaIgraca(igraci[2], &CIgrac::Trci));
    igraci[2]->IzvrsiAkciju("Nova akcija");

    for (vector<CIgrac*>::iterator it = igraci.begin(); it != igraci.end(); ++it) {
        delete *it;
    }

    return 0;
}
