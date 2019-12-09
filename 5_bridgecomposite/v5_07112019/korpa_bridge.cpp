#include <memory>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class IServisPlacanja {
public:
    virtual ~IServisPlacanja() {}
    virtual void plati(int cena) = 0;
};

class Korpa {
public:
    Korpa(): m_ukupnaCena(0), m_servisPlacanja(nullptr) {}
    virtual ~Korpa() {}

    virtual void postaviServisPlacanja(shared_ptr<IServisPlacanja> servis) {
        m_servisPlacanja = servis;
    }
    virtual void dodajArtikl(int cena) {
        m_ukupnaCena += cena;
    }
    virtual void izbaciArtikl(int cena) {
        m_ukupnaCena -= cena;
    }
    virtual void plati() {
        if (m_servisPlacanja == nullptr) {
            throw "nije postavljen servis za placanje";
        }
        m_servisPlacanja->plati(m_ukupnaCena);

        m_ukupnaCena = 0;
    }
protected:
    int                             m_ukupnaCena;
    shared_ptr<IServisPlacanja>     m_servisPlacanja;
};

class CServisPlacanjeKarticom: public IServisPlacanja {
public:
    virtual void plati(int cena) {
        cout << "Placam karticom " << cena << " RSD." << endl;
    }
};

class CServisPlacanjePouzecem: public IServisPlacanja {
public:
    virtual void plati(int cena) {
        cout << "Placam pouzecem " << cena << " RSD." << endl;
    }
};

class CServisPlacanjePaypalom: public IServisPlacanja {
public:
    virtual void plati(int cena) {
        cout << "Placam paypalom " << cena << " RSD." << endl;
    }
};

int main() {
    srand(time(NULL));
    unique_ptr<Korpa> korpa = make_unique<Korpa>();

    korpa->dodajArtikl(10);
    korpa->dodajArtikl(20);
    korpa->dodajArtikl(30);

    while (true) {
        try {
            korpa->plati();
            break;
        }
        catch (const char* ch) {
            cout << "Greska " << ch << endl;
        }
        switch (rand()%3) {
        case 0:
            korpa->postaviServisPlacanja(make_shared<CServisPlacanjeKarticom>());
            break;
        case 1:
            korpa->postaviServisPlacanja(make_shared<CServisPlacanjePouzecem>());
            break;
        case 2:
            korpa->postaviServisPlacanja(make_shared<CServisPlacanjePaypalom>());
            break;
        }
    }

    return 0;
}
