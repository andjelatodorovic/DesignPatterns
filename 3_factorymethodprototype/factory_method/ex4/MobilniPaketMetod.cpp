#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

/* apstraktan proizvod */
class MobilniPaket {
protected:
    int m_cena;
    int m_protok;
    string m_ime;
    vector<string> m_korisnici;
    vector<string> m_usluga;
public:
    MobilniPaket(): m_cena(0), m_protok(0), m_ime("") {}
    virtual void dodajUslugu(string usluga) = 0;
    virtual void izlistajUsluge() = 0;
};

/* konkretan proizvod */
class ZlatniPaket: public MobilniPaket {
public:
    ZlatniPaket() {
        m_cena = 1000;
        m_protok = 2000;
        m_ime = "Zlatni paket";
    }
    void dodajUslugu(string usluga) {
        cout << "dodajem zlatnu uslugu <" << usluga << ">." << endl;
        m_usluga.push_back(usluga);
    }
    void izlistajUsluge() {
        cout << "izlistajem zlatne usluge: " << endl;
        for (int i = 0; i < m_usluga.size(); i ++) {
            cout << "\t<" << m_usluga [i] << ">" << endl;
        }
    }
};

/* konkretan proizvod */
class NormalanPaket: public MobilniPaket {
public:
    NormalanPaket() {
        m_cena = 600;
        m_protok = 800;
        m_ime = "Normalan paket";
    }
    void dodajUslugu(string usluga) {
        cout << "dodajem normalnu uslugu <" << usluga << ">." << endl;
        m_usluga.push_back(usluga);
    }
    void izlistajUsluge() {
        cout << "izlistajem normalne usluge: " << endl;
        for (int i = 0; i < m_usluga.size(); i ++) {
            cout << "\t<" << m_usluga [i] << ">" << endl;
        }
    }
};

/* klijent + apstraktan fabricki metod */
class FabrikaMobilnihPaketa {
public:
    MobilniPaket *dajMobilniPaket() {
        MobilniPaket *mobilniPaket = napraviMobilniPaket();
        mobilniPaket->dodajUslugu("telefon");
        mobilniPaket->dodajUslugu("internet");
        return mobilniPaket;
    }
    virtual MobilniPaket* napraviMobilniPaket() = 0;
};

/* konkretan fabricki metod */
class FabrikaZlatnihMobilnihPaketa: public FabrikaMobilnihPaketa {
public:
    MobilniPaket* napraviMobilniPaket() {
        MobilniPaket *mobilniPaket = new ZlatniPaket();
        mobilniPaket->dodajUslugu("zlatni TV kanali");
        return mobilniPaket;
    }
};

/* konkretan fabricki metod */
class FabrikaNormalnihMobilnihPaketa: public FabrikaMobilnihPaketa {
public:
    MobilniPaket* napraviMobilniPaket() {
        MobilniPaket *mobilniPaket = new NormalanPaket();
        mobilniPaket->dodajUslugu("normalni TV kanali");
        return mobilniPaket;
    }
};

int main() {
    cout << "Koji hocete da budete korisnik (Z-zlatni, N-normalan)? ";
    char ch;
    cin >> ch;
    FabrikaMobilnihPaketa *fabrikaMobilnihPaketa;
    if (ch == 'z' || ch == 'Z') {
        fabrikaMobilnihPaketa = new FabrikaZlatnihMobilnihPaketa();
    } else {
        fabrikaMobilnihPaketa = new FabrikaNormalnihMobilnihPaketa();
    }
    MobilniPaket *mobilniPaket = fabrikaMobilnihPaketa->dajMobilniPaket();
    mobilniPaket->izlistajUsluge();

    delete fabrikaMobilnihPaketa;
    delete mobilniPaket;
    return 0;
}
