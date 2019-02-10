/* primer je adaptiran iz knjige Design Patterns Explained Simply */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/* apstraktni proizvod Dokument */
class Dokument {
private:
    string m_ime;
public:
    Dokument(string ime) {
        m_ime = ime;
    }
    virtual void otvori() = 0;
    virtual void zatvori() = 0;
    string dajIme() {
        return m_ime;
    }
};

/* konkretan proizvod MojDokument */
class MojDokument: public Dokument {
public:
    MojDokument(string ime): Dokument(ime) {}
    void otvori() {
        cout << "\tMojDokument.otvori()" << endl;
    }
    void zatvori() {
        cout << "\tMojDokument.zatvori()" << endl;
    }
};

/* Apstraktni Klijent koji ima Fabricki Metod NapraviDokument */
class Klijent {
  public:
    Klijent() {
        cout << "Klijent.Konstruktor()" << endl;
    }
    ~Klijent() {
        cout << "Klijent.Destruktor()" << endl;
        for (int i = 0; i < m_dokumenti.size(); i ++) {
            m_dokumenti[i]->zatvori();
        }
    }
    void NoviDokument(string ime) {
        cout << "Klijent.NoviDokument()" << endl;
        m_dokumenti.push_back(NapraviDokument(ime));
        m_dokumenti.back()->otvori();
    }
    void otvoriDokument();
    void izvestajODokumentima();
    /* fabricki metod */
    virtual Dokument *NapraviDokument(string ime) = 0;
  private:
    vector<Dokument*> m_dokumenti;
};

void Klijent::izvestajODokumentima() {
  cout << "Klijent.izvestajODokumentima()" << endl;
  for (int i = 0; i < m_dokumenti.size(); i ++) {
    cout << "ime dokumenta #" << i << ": " << m_dokumenti[i]->dajIme() << endl;
  }
}

/* konkretan klijent, implementira konkretan fabricki metod za konkretan proizvod */
class MojKlijent: public Klijent {
  public:
    MojKlijent() {
        cout << "MojKlijent.Konstruktor()" << endl;
    }
    ~MojKlijent() {
        cout << "MojKlijent.Destruktor()" << endl;
    }
    /* konkretan fabricki metod za pravljenje konkretnog proizvoda MojDokument */
    Dokument *NapraviDokument(string ime) {
        cout << "   MojKlijent.NapraviDokument()" << endl;
        return new MojDokument(ime);
    }
};
/* primer koriscenja */
int main() {
  Klijent *mojKlijent = new MojKlijent();
  mojKlijent->NoviDokument("Spisak");
  mojKlijent->NoviDokument("Ugovor");
  mojKlijent->NoviDokument("Faktura");
  mojKlijent->izvestajODokumentima();
  delete mojKlijent;
}
