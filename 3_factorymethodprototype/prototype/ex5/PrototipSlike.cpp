/* primer je adaptiran iz knjige Design Patterns Explained Simply */

#include <iostream>
#include <vector>

using namespace std;

enum TipSlike { JPEG, PNG };

/* apstraktan prototip koji ima apstraktan metod za kloniranje konkretnih prototipova kloniraj(),
   poseduje i metod za dodavanje prototipa u kolekciju prototipova, i onda koristeci staticki
   metod nadjiIKloniraj(tipSlike) mozemo kreirati kopiju odgovarajuceg prototipa iz te kolekcije */
class Slika {
public:
    virtual void nacrtaj() = 0;
    /* metod koji nam vraca kopiju/klona prototipa iz kolekcije koji odgovara tipu slike */
    static Slika *nadjiIKloniraj(TipSlike);
protected:
    virtual TipSlike vratiTipSlike() = 0;
    /* metod za kloniranje konkretnih prototipova */
    virtual Slika *kloniraj() = 0;
    /* za svaku potklasu Slika registrujemo njen prototip dodajuci je u
       niz/kolekciju prototipova koja je vector m_prototipovi */
    static void dodajPrototip(Slika *prototipSlike) {
        m_prototipovi.push_back(prototipSlike);
    }
private:
    /* vector /niz u kojem cuvamo konkretne prototipove */
    static vector<Slika*> m_prototipovi;
};

vector<Slika*> Slika::m_prototipovi;

/* pomocu ovog statickog metoda moguce je dobiti kopije konkretnih
   prototipova koji se cuvaju u kolekciji prototipova m_prototipovi */
Slika *Slika::nadjiIKloniraj(TipSlike tipSlike) {
  for (int i = 0; i < m_prototipovi.size(); i++) {
    if (m_prototipovi[i]->vratiTipSlike() == tipSlike) {
      return m_prototipovi[i]->kloniraj();
    }
  }
}
/* konkretan prototip, implementira metod za kloniranje kloniraj() */
class JPEGSlika: public Slika {
public:
    TipSlike vratiTipSlike() {
        return JPEG;
    }
    void nacrtaj() {
        cout << "JPEGSlika::nacrtaj() id#" << m_id << endl;
    }
    /* metod za kloniranje koji poziva konstruktor JPEGSlika(int) ako hocemo da dodeljujemo
       brojac za svaku kreiranju sliku */
    Slika *kloniraj() {
        return new JPEGSlika(0);
    }
protected:
    /* ovaj konstruktor zovemo samo iz metoda kloniraj */
    JPEGSlika(int x) {
        m_id = m_brojac++;
    }
private:
    /* prilikom inicijaliziranja pozvace se konstruktor JPEGSlika() i dodace se ovaj prototip
       u kolekciju prototipova */
    static JPEGSlika m_JPEGSlika;
    /* ovaj konstruktor je pozvan samo prilikom inicijaliziranja statickog polja m_JPEGSlika */
    JPEGSlika() {
        dodajPrototip(this);
    }
    /* identifikator i brojac */
    int m_id;
    static int m_brojac;
};
JPEGSlika JPEGSlika::m_JPEGSlika;
int JPEGSlika::m_brojac = 1;

/* konkretan prototip, implementira metod za kloniranje kloniraj() */
class PNGSlika: public Slika {
public:
    TipSlike vratiTipSlike() {
        return PNG;
    }
    void nacrtaj() {
        cout << "PNGSlika::nacrtaj id#" << m_id << endl;
    }
    /* metod za kloniranje koji poziva konstruktor PNGSlika(int) ako hocemo da dodeljujemo
       brojac za svaku kreiranju sliku */
    Slika *kloniraj() {
        return new PNGSlika(0);
    }
protected:
    /* ovaj konstruktor zovemo samo iz metoda kloniraj */
    PNGSlika(int x) {
        m_id = m_brojac++;
    }
private:
    /* prilikom inicijaliziranja pozvace se konstruktor PNGSlika() i dodace se ovaj prototip
       u kolekciju prototipova */
    static PNGSlika m_PNGSlika;
    /* ovaj konstruktor je pozvan samo prilikom inicijaliziranja statickog polja m_PNGSlika */
    PNGSlika() {
        dodajPrototip(this);
    }
    /* identifikator i brojac */
    int m_id;
    static int m_brojac;
};

PNGSlika PNGSlika::m_PNGSlika;
int PNGSlika::m_brojac = 1;

/* kreiracemo nekoliko slika po tipu */
const int BROJ_SLIKA = 9;
TipSlike tipSlike[BROJ_SLIKA] = {
  JPEG, JPEG, JPEG, PNG, JPEG, PNG, PNG, JPEG, PNG
};

/* koriscenje sablona prototip, pomocu statickog metoda nadjiIKloniraj kreiramo kopije
   prototipova iz kolekcije, i zatim ih koristimo pozivajuci metod nacrtaj() */
int main() {
    vector<Slika*> slike;
    for (int i = 0; i < BROJ_SLIKA; i++) {
        slike.push_back(Slika::nadjiIKloniraj(tipSlike[i]));
    }
    for (int i = 0; i < slike.size(); i++) {
        slike [i]->nacrtaj();
    }

    for (int i = 0; i < slike.size(); i++) {
        delete slike[i];
    }
}
