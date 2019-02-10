#include <iostream>
#include <vector>

using namespace std;
/* realni subjekt / RealSubject koji je u ovom slucaju i zajednicki interfejs / Subject sto bas i nije najbolja praksa */
class Slika {
public:
    Slika(const string& imeSlike, const string& lokacijaSlike): m_imeSlike(imeSlike), m_lokacijaSlike(lokacijaSlike) {
        cout << "Ucitajem sliku sa " << m_lokacijaSlike << endl;
    }
    ~Slika() { cout << "Brisem sliku " << m_imeSlike << endl; }
    virtual void Nacrtaj() {
        cout << "Crtam sliku " << m_imeSlike << endl;
    }
protected:
    Slika() {}
    string  m_lokacijaSlike;
    string  m_imeSlike;
};
/* zastupnik / proxy realnog subjekta, u ovom slucaju Slika */
class SlikaZastupnik: public Slika {
public:
    SlikaZastupnik(const string& imeSlike, const string& lokacijaSlike) {
        m_lokacijaSlike = lokacijaSlike;
        m_imeSlike = imeSlike;
        m_slika = NULL;
    }
    virtual ~SlikaZastupnik() {
        if (m_slika != NULL) {
            delete m_slika;
        }
    }
    virtual void Nacrtaj() {
        if (m_slika == NULL) {
            m_slika = new Slika(m_imeSlike, m_lokacijaSlike);
        }
        m_slika->Nacrtaj();
    }
protected:
    Slika*  m_slika;
};

int main() {
    vector<Slika*> slike;
    slike.push_back(new SlikaZastupnik("Drvo", "./img/Drvo.png"));
    slike.push_back(new SlikaZastupnik("Auto", "./img/Auto.png"));
    slike.push_back(new SlikaZastupnik("Kuca", "./img/Kuca.png"));
    slike.push_back(new SlikaZastupnik("More", "./img/More.png"));

    int odgovor;

    do {
        cout << "Koju sliku hoces da nacrtas [od 1 do 4], 0 za izlaz: ";
        cin >> odgovor;
        if (odgovor != 0) {
            slike[odgovor - 1]->Nacrtaj();
        }
    } while (odgovor != 0);

    for (vector<Slika*>::iterator it = slike.begin(); it != slike.end(); ++it) {
        delete *it;
    }

    return 0;
}
