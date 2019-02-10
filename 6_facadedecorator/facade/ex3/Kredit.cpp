#include<iostream>
#include<string>

using namespace std;

/* klijent banke */
class Klijent {
public:
    Klijent (string ime) : m_ime(ime) {}
    string dajIme(void) { return m_ime; }
private:
    Klijent();
    string  m_ime;
};

/* kompleksan podsistem - banka */
class Banka {
public:
    bool imaDovoljnoUstedjevine(Klijent klijent, int kolicina) {
        cout << "Proveravamo ustedjevinu u banci za klijenta " << klijent.dajIme() << "... " << endl;
        return true;
    }
};
/* kompleksan podsistem - kreditna agencija */
class KreditnaAgencija {
public:
    bool imaDobarKreditniRejting(Klijent klijent, int kolicina) {
        cout << "Proveravamo kreditni rejting za klijenta " << klijent.dajIme() << "... " << endl;
        return true;
    }
};
/* kompleksan podsistem - servis za proveru dugova */
class DuznickiServis {
public:
    bool imaDobarDuznickiRejting(Klijent klijent, int kolicina) {
        cout << "Proveravamo duznicki rejting za klijenta " << klijent.dajIme() << "... " << endl;
        return true;
    }
};

/* fasada - nudi samo jedan metod klijentu jeDozvoljenKredit koji realizuje interakcijom
   sa razlicitim kompleksnim podsistemima */
class ServisKreditiranja {
public:
    ServisKreditiranja() {
        m_banka = new Banka();
        m_duznickiServis = new DuznickiServis();
        m_kreditnaAgencija = new KreditnaAgencija();
    }
    ~ServisKreditiranja() {
        delete m_banka;
        delete m_duznickiServis;
        delete m_kreditnaAgencija;
    }
    bool jeDozvoljenKredit(Klijent klijent, int kolicina) {
        cout << klijent.dajIme() << " se prijavljuje za kredit od " << kolicina << "RSD." << endl;
        bool jeDozvoljen = true;

        jeDozvoljen = m_banka->imaDovoljnoUstedjevine(klijent, kolicina);
        if (jeDozvoljen) {
            jeDozvoljen = m_duznickiServis->imaDobarDuznickiRejting(klijent, kolicina);
        }
        if (jeDozvoljen) {
            jeDozvoljen = m_kreditnaAgencija->imaDobarKreditniRejting(klijent, kolicina);
        }
        return jeDozvoljen;
    }
private:
    Banka*              m_banka;
    DuznickiServis*     m_duznickiServis;
    KreditnaAgencija*   m_kreditnaAgencija;
};

/* klijent sada ima veoma jednostavan nacin koriscenja podsistema putem APIja koji
   nudi fasada */
int main() {
    ServisKreditiranja servisKreditiranja;
    Klijent klijentA("Aca Acic");
    bool jeDozvoljen = servisKreditiranja.jeDozvoljenKredit(klijentA, 100000);

    cout << endl << klijentA.dajIme() << " kredit je " << (jeDozvoljen ? "ODOBREN" : "ODBIJEN") << endl;

    return 0;
}
