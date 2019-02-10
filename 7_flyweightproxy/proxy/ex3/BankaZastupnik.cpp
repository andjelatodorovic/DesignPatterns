#include <iostream>

using namespace std;

/* subjekt koji je u ovom slucaju i realni subjekt za koga radimo zastupnika/proxy */
class Banka {
public:
    Banka(int brojRacuna): m_brojRacuna(brojRacuna), m_stanje(800) {}
    virtual ~Banka() { }
    virtual bool UzmiNovac(int kolicina) {
        if (kolicina <= m_stanje) {
            m_stanje -= kolicina;
            cout << "Sa racuna #" << m_brojRacuna << " skinuto " << kolicina << "RSD. Novo stanje " << m_stanje << "RSD." << endl;
            return true;
        }
        cout << "Sa racuna #" << m_brojRacuna << " NIJE skinuto " << kolicina << "RSD. Staro stanje " << m_stanje << "RSD." << endl;
        return true;
    }
protected:
    Banka(): m_stanje(0) {}
    int     m_brojRacuna;
    int     m_stanje;
};
/* proxy/zastupnik za subjekta/Banka, u ovom slucaju proxy ima ulogu da vrsi kontrolu pristupu konkretnom metodu Request (u ovom slucaju
   to je metod UzmiNovac */
class ATM: public Banka {
public:
    ATM(int brojRacuna): Banka(brojRacuna), m_danasUzeto(0), m_banka(NULL) {}
    virtual ~ATM() { if (m_banka != NULL) delete m_banka; }
    virtual bool UzmiNovac(int kolicina) {
        if (m_danasUzeto + kolicina <= DNEVNI_LIMIT) {
            if (m_banka == NULL) {
                m_banka = new Banka(m_brojRacuna);
            }
            if (m_banka->UzmiNovac(kolicina)) {
                m_danasUzeto += kolicina;
                return true;
            }
        }
        cout << "Prekoracen dnevni limit za racun #" << m_brojRacuna << ". Transakcija neuspesna." << endl;
        return false;
    }
protected:
    static int  DNEVNI_LIMIT;
    Banka*      m_banka;
    int         m_danasUzeto;
};
int ATM::DNEVNI_LIMIT = 500;

int main() {
    Banka *atm = new ATM(12345);
    cout << "Pokusavam da skinem 600RSD sa racuna." << endl;
    atm->UzmiNovac(600);
    cout << "Pokusavam da skinem 200RSD sa racuna." << endl;
    atm->UzmiNovac(200);
    cout << "Pokusavam da skinem 400RSD sa racuna." << endl;
    atm->UzmiNovac(400);
    cout << "Pokusavam da skinem 300RSD sa racuna." << endl;
    atm->UzmiNovac(300);

    delete atm;

    return 0;
}
