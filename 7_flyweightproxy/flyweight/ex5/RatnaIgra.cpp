#include <iostream>
#include <map>
#include <vector>

using namespace std;

/* pomocna klasa - nebitna za flyweight pattern */
class CSlika {
public:
    CSlika(const string& lokacijaSlike): m_lokacijaSlike(lokacijaSlike) {}
    friend ostream& operator<<(const ostream& out, const CSlika& slika) {
        cout << "crtam sliku " << slika.m_lokacijaSlike << endl;
    }
protected:
    string  m_lokacijaSlike;
};

/* flyweight / muva apstraktna klasa */
class IRatnik {
public:
    enum {VOJNIK};
    virtual void pomeriRatnika(int staroX, int staroY, int novoX, int novoY) = 0;
};
/* concrete flyweight / konkretna muva */
class CVojnik: public IRatnik {
public:
    CVojnik() { m_slika = new CSlika("./img/Vojnik.bmp"); }
    virtual ~CVojnik() { if (m_slika != NULL) delete m_slika; }
    void pomeriRatnika(int staroX, int staroY, int novoX, int novoY) {
        cout << "pomeram ratnika sa (" << staroX << ", " << staroY << ") na (" << novoX << ", " << novoY
            << ") " << *m_slika << endl;
    }
protected:
    CSlika* m_slika;
};
/* flyweight factory / fabrika muva */
class FabrikaRatnika {
public:
    static FabrikaRatnika& DajFabriku() {
        static FabrikaRatnika fabrikaRatnika;
        return fabrikaRatnika;
    }
    IRatnik* dajRatnika(int tipRatnika) {
        if (m_kolekcijaRatnika.find(tipRatnika) == m_kolekcijaRatnika.end()) {
            switch (tipRatnika) {
                case IRatnik::VOJNIK:
                    m_kolekcijaRatnika[tipRatnika] = new CVojnik();
                    break;
                default:
                    throw(string("Nepostojeci tip ratnika"));
            }
        }
        return m_kolekcijaRatnika[tipRatnika];
    }
protected:
    map<int, IRatnik*>  m_kolekcijaRatnika;
};

/* klijenti / objekti koji medjusobno dele iste muva objekte
   klijenti poseduju svoja stanja koja su u stvari kontekst/okruzenje
   u kojem se muva objekti koriste, pa su stanja klijenata u stvari spoljasnja/extrinsic
   stanja za muvu koja ima svoje interno stanje koje je deljeno izmedju razlicitih klijenata */
class CRatnikUIgri {
public:
    CRatnikUIgri(int tipRatnika): m_trenutnoX(0), m_trenutnoY(0) {
        try {
            m_ratnik = FabrikaRatnika::DajFabriku().dajRatnika(tipRatnika);
        } catch (string ex) {
            cout << ex << endl;
        }
    }
    virtual ~CRatnikUIgri() {
        if (m_ratnik != NULL) delete m_ratnik;
    }
    void pomeriRatnika(int novoX, int novoY) {
        if (m_ratnik != NULL) {
            m_ratnik->pomeriRatnika(m_trenutnoX, m_trenutnoY, novoX, novoY);
            m_trenutnoX = novoX;
            m_trenutnoY = novoY;
        }
    }
protected:
    int         m_trenutnoX;
    int         m_trenutnoY;
    IRatnik*    m_ratnik;
};

/* kreiramo nekoliko igraca i svi ce da dele isti flyweight/muva objekat */
int main() {
    vector<CRatnikUIgri*> ratniciUIgri;
    ratniciUIgri.push_back(new CRatnikUIgri(IRatnik::VOJNIK));
    ratniciUIgri.push_back(new CRatnikUIgri(IRatnik::VOJNIK));
    ratniciUIgri.push_back(new CRatnikUIgri(IRatnik::VOJNIK));
    ratniciUIgri.push_back(new CRatnikUIgri(IRatnik::VOJNIK));
    ratniciUIgri[0]->pomeriRatnika(10, 10);
    ratniciUIgri[1]->pomeriRatnika(30, 30);
    ratniciUIgri[0]->pomeriRatnika(-50, 20);

    while (ratniciUIgri.begin() != ratniciUIgri.end()) {
        delete ratniciUIgri[0];
        ratniciUIgri.erase(ratniciUIgri.begin());
    }
    return 0;
}
