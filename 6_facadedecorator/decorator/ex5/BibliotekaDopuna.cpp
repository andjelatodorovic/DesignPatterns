#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* apstraktna komponenta */
class IObjekatIzBiblioteke {
public:
    IObjekatIzBiblioteke() : m_kolicina(0) {}
    IObjekatIzBiblioteke(int kolicina): m_kolicina(kolicina) {}
    virtual void prikazi() = 0;
    int dajKolicinu() { return m_kolicina; }
    void postaviKolicinu(int kolicina) { m_kolicina = kolicina; }
protected:
    int m_kolicina;
};
/* konkretna komponenta */
class CKnjigaIzBiblioteke: public IObjekatIzBiblioteke {
public:
    CKnjigaIzBiblioteke(const string& autor, const string& naslov, int kolicina):
        m_autor(autor), m_naslov(naslov), IObjekatIzBiblioteke(kolicina) {}
    virtual void prikazi() {
        cout << "[KNJIGA] autor: " << m_autor << ", naslov: " << m_naslov << ", broj kopija: " << m_kolicina << endl;
    }
private:
    string  m_autor;
    string  m_naslov;
};
/* konkretna komponenta */
class CVideoIzBiblioteke: public IObjekatIzBiblioteke {
public:
    CVideoIzBiblioteke(const string& reziser, const string& naslov, int trajanje, int kolicina):
        m_reziser(reziser), m_naslov(naslov), m_trajanje(trajanje), IObjekatIzBiblioteke(kolicina) {}
    virtual void prikazi() {
        cout << "[VIDEO] reziser: " << m_reziser << ", naslov: " << m_naslov << ", trajanje: " << m_trajanje << ", broj kopija: " << m_kolicina << endl;
    }
private:
    string  m_reziser;
    string  m_naslov;
    int     m_trajanje;
};

/* apstraktna dopuna/dekorater - nasledjuje komponentu */
class IDopunaObjektaIzBiblioteke: public IObjekatIzBiblioteke {
public:
    IDopunaObjektaIzBiblioteke(IObjekatIzBiblioteke *objekatIzBiblioteke): m_objekatIzBiblioteke(objekatIzBiblioteke) {}
    virtual ~IDopunaObjektaIzBiblioteke() { if (m_objekatIzBiblioteke != NULL) delete m_objekatIzBiblioteke; }
    virtual void prikazi() {
        if (m_objekatIzBiblioteke != NULL) {
            m_objekatIzBiblioteke->prikazi();
        }
    }
protected:
    IObjekatIzBiblioteke*   m_objekatIzBiblioteke;
};

/* konkretna dopuna - dodaje svojstvo da objekat moze biti pozajmljiv */
class CPozajmljivDopunaObjektaIzBiblioteke: public IDopunaObjektaIzBiblioteke {
public:
    CPozajmljivDopunaObjektaIzBiblioteke(IObjekatIzBiblioteke *objekatIzBiblioteke)
                            : IDopunaObjektaIzBiblioteke(objekatIzBiblioteke) {}
    virtual void prikazi() {
        if (m_objekatIzBiblioteke != NULL) {
            m_objekatIzBiblioteke->prikazi();
            if (m_korisnici.size() > 0) {
                cout << "Trenutno pozajmili: " << endl;
                for (vector<string>::iterator it = m_korisnici.begin(); it != m_korisnici.end(); ++it) {
                    cout << "\t" << *it << endl;
                }
            }
        }
    }
    virtual void pozajmi(string korisnik) {
        if (m_objekatIzBiblioteke->dajKolicinu() == 0) {
            cout << "Nema tog objekta u biblioteci." << endl;
        } else {
            m_objekatIzBiblioteke->postaviKolicinu(m_objekatIzBiblioteke->dajKolicinu() - 1);
            m_korisnici.push_back(korisnik);
        }
    }
    virtual void vrati(string korisnik) {
        vector<string>::iterator it = find(m_korisnici.begin(), m_korisnici.end(), korisnik);
        if (it != m_korisnici.end()) {
            m_korisnici.erase(it);
            m_objekatIzBiblioteke->postaviKolicinu(m_objekatIzBiblioteke->dajKolicinu() + 1);
        } else {
            cout << "Korisnik " << korisnik << " nije pozajmio taj objekat u biblioteci." << endl;
        }
    }
    virtual ~CPozajmljivDopunaObjektaIzBiblioteke() {}
protected:
    vector<string>  m_korisnici;
};

int main() {
    CVideoIzBiblioteke videoMaratonci("Maratonci trce pocasni krug", "Slobodan Sijan", 92, 2);
    CKnjigaIzBiblioteke knjigaNaCupriji("Ivo Andric", "Na Drini cuprija", 3);

    cout << "Prikazujem film: " << endl;
    videoMaratonci.prikazi();

    cout << "Prikazujem knjigu: " << endl;
    knjigaNaCupriji.prikazi();

    CPozajmljivDopunaObjektaIzBiblioteke pozajmljivaKnjiga(&knjigaNaCupriji);
    CPozajmljivDopunaObjektaIzBiblioteke pozajmljivVideo(&videoMaratonci);

    pozajmljivaKnjiga.pozajmi("Aca");
    pozajmljivaKnjiga.pozajmi("Braca");
    pozajmljivaKnjiga.prikazi();

    pozajmljivVideo.pozajmi("Aca");
    pozajmljivVideo.pozajmi("Maca");
    pozajmljivVideo.pozajmi("Daca");
    pozajmljivVideo.prikazi();
    pozajmljivVideo.vrati("Maca");
    pozajmljivVideo.prikazi();

    return 0;
}
