#include <iostream>
#include <vector>
#include <map>

using namespace std;

class CSlika;

/* pomocna klasa */
class CSlikaBiblioteka {
public:
    static void PromeniVelicinu(CSlika& pSlika, int velicina);
    static CSlika* UcitajSliku(const string& lokacijaSlike, const string& naziv);
};
/* pomocna klasa */
class CSlika {
public:
    friend class CSlikaBiblioteka;
    CSlika(const string& naziv): m_naziv(naziv), m_velicina(10) {}
    ~CSlika() {}
    void Prikazi() {
        cout << "Crtam sliku " << m_naziv << ", velicina = " << m_velicina << endl;
    }
protected:
    string  m_naziv;
    int     m_velicina;
};

void CSlikaBiblioteka::PromeniVelicinu(CSlika& pSlika, int velicina) {
    pSlika.m_velicina = velicina;
}

CSlika* CSlikaBiblioteka::UcitajSliku(const string& lokacijaSlike, const string& naziv) {
    cout << "Ucitavam sliku sa lokacije '" << lokacijaSlike << "'" << naziv << endl;
    return new CSlika(naziv);
    cout << "Slika ucitana " << endl;
}
/* flyweight / muva apstraktna klasa */
class IZastavaDrzave {
public:
    virtual void Prikazi() {
        cout << "Prikazujem zastavu " << endl;
        m_zastava->Prikazi();
    }
    virtual ~IZastavaDrzave() {
        delete m_zastava;
    }
protected:
    IZastavaDrzave(const string& naziv, const string& lokacijaSlike) {
        m_zastava = CSlikaBiblioteka::UcitajSliku(lokacijaSlike, naziv);
    }
    string      m_lokacijaSlike;
    CSlika*     m_zastava;
};
/* konkretna muva / concrete flyweight */
class CZastavaSrbije: public IZastavaDrzave {
public:
    CZastavaSrbije(): IZastavaDrzave(string("Srbija"), string("./img/Srbija.png")) {}
    virtual ~CZastavaSrbije() {}
};
/* konkretna muva / concrete flyweight */
class CZastavaRusije: public IZastavaDrzave {
public:
    CZastavaRusije(): IZastavaDrzave(string("Rusija"), string("./img/Rusija.png")) {}
    virtual ~CZastavaRusije() {}
};
/* konkretna muva / concrete flyweight */
class CZastavaKine: public IZastavaDrzave {
public:
    CZastavaKine(): IZastavaDrzave(string("Kina"), string("./img/Kina.png")) {}
    virtual ~CZastavaKine() {}
};
/* konkretna muva / concrete flyweight */
class CZastavaNepoznateDrzave: public IZastavaDrzave {
public:
    CZastavaNepoznateDrzave(const string& imeDrzave): IZastavaDrzave(string(imeDrzave), string("./img/Nepoznato.png")) {}
    virtual ~CZastavaNepoznateDrzave() {}
};
/* fabrika muva / flyweight factory */
class CFabrikaZastavaDrzava {
public:
    CFabrikaZastavaDrzava() {}
    virtual ~CFabrikaZastavaDrzava() {
        while (m_kolekcijaZastava.begin() != m_kolekcijaZastava.end()) {
            delete m_kolekcijaZastava.begin()->second;
            m_kolekcijaZastava.erase(m_kolekcijaZastava.begin());
        }
    }
    IZastavaDrzave* dajZastavuDrzave(const string& imeDrzave) {
        if (m_kolekcijaZastava.find(imeDrzave) == m_kolekcijaZastava.end()) {
            if (imeDrzave == "SRBIJA") {
                m_kolekcijaZastava[imeDrzave] = new CZastavaSrbije();
            } else if (imeDrzave == "RUSIJA") {
                m_kolekcijaZastava[imeDrzave] = new CZastavaRusije();
            } else if (imeDrzave == "KINA") {
                m_kolekcijaZastava[imeDrzave] = new CZastavaKine();
            } else {
                m_kolekcijaZastava[imeDrzave] = new CZastavaNepoznateDrzave(imeDrzave);
            }
        }
        return m_kolekcijaZastava[imeDrzave];
    }
protected:
    map<string, IZastavaDrzave*> m_kolekcijaZastava;
};

int main() {
    CFabrikaZastavaDrzava fabrikaZastava;

    vector<string> listaDrzava;
    listaDrzava.push_back("RUSIJA");
    listaDrzava.push_back("NORVESKA");
    listaDrzava.push_back("SRBIJA");
    listaDrzava.push_back("FINSKA");
    listaDrzava.push_back("KINA");

    cout << "Prikazujem ikone drzava: " << endl;
    for (vector<string>::iterator it = listaDrzava.begin(); it != listaDrzava.end(); ++it) {
        IZastavaDrzave* zastava = fabrikaZastava.dajZastavuDrzave(*it);
        zastava->Prikazi();
    }
    cout << "Zavrsen prikaz" << endl;

    cout << "Prikazujem ikone drzava drugi put: " << endl;
    for (vector<string>::iterator it = listaDrzava.begin(); it != listaDrzava.end(); ++it) {
        IZastavaDrzave* zastava = fabrikaZastava.dajZastavuDrzave(*it);
        zastava->Prikazi();
    }
    cout << "Zavrsen prikaz" << endl;

    return 0;
}
