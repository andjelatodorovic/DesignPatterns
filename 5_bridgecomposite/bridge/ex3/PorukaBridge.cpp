#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class ServisSlanjaPoruka;

/* apstrakcija, ne mora da bude i apstraktna klasa, u ovom slucaju to je vec
   konkretna klasa sa definisanim svim metodima */
class Poruka {
protected:
    string  m_naslov;
    string  m_sadrzaj;
    int     m_vaznost;
    /* sadrzi objekat tipa implementor ciju implementaciju koristi da realizuje sopstvene metode */
    ServisSlanjaPoruka *m_servisSlanjaPoruka;
public:
    Poruka() {}
    Poruka(ServisSlanjaPoruka *servisSlanjaPoruka) : m_servisSlanjaPoruka(servisSlanjaPoruka) { }
    Poruka(string naslov, string sadrzaj, int vaznost, ServisSlanjaPoruka *servisSlanjaPoruka) :
        m_naslov(naslov),
        m_sadrzaj(sadrzaj),
        m_vaznost(vaznost),
        m_servisSlanjaPoruka(servisSlanjaPoruka) { }
    virtual ~Poruka() {}
    virtual void posalji();
    virtual void postaviServisSlanjaPoruka(ServisSlanjaPoruka *servisSlanjaPoruka);
    virtual void postaviSadrzaj(string sadrzaj) { m_sadrzaj = sadrzaj; }
    virtual void postaviNaslov(string naslov) { m_naslov = naslov; }
    virtual void postaviVaznost(int vaznost) { m_vaznost = vaznost; }
};

/* implementor */
class ServisSlanjaPoruka {
public:
    virtual ~ServisSlanjaPoruka() {}
    virtual void posaljiPoruku(string naslov, string sadrzaj, int vaznost) = 0;
};

void Poruka::posalji() {
    if (m_servisSlanjaPoruka == NULL) {
        cout << "Nije postavljen servis slanja poruka." << endl;
    } else {
        cout << "<PORUKA>: saljem poruku(" << m_naslov << ", " << m_sadrzaj << ", " << m_vaznost << ")" << endl;
        m_servisSlanjaPoruka->posaljiPoruku(m_naslov, m_sadrzaj, m_vaznost);
    }
}

void Poruka::postaviServisSlanjaPoruka(ServisSlanjaPoruka *servisSlanjaPoruka) {
    m_servisSlanjaPoruka = servisSlanjaPoruka;
}

/* konkretan implementor */
class EmailServisSlanjaPoruka : public ServisSlanjaPoruka {
public:
    virtual ~EmailServisSlanjaPoruka() {}
    virtual void posaljiPoruku(string naslov, string sadrzaj, int vaznost) {
        cout << "<EMAIL SERVIS PORUKA> Saljem poruku (" << naslov << ", " << sadrzaj << ", " << vaznost << ") putem e-mail-a..." << endl;
    }
};
/* konkretan implementor */
class SMSServisSlanjaPoruka: public ServisSlanjaPoruka {
public:
    virtual ~SMSServisSlanjaPoruka() {}
    virtual void posaljiPoruku(string naslov, string sadrzaj, int vaznost) {
        cout << "<SMS SERVIS PORUKA> Saljem poruku (" << naslov << ", " << sadrzaj << ", " << vaznost << ") putem SMS-a..." << endl;
    }
};
/* konkretan implementor */
class WebServisSlanjaPoruka: public ServisSlanjaPoruka {
public:
    virtual ~WebServisSlanjaPoruka() {}
    virtual void posaljiPoruku(string naslov, string sadrzaj, int vaznost) {
        cout << "<WEB SERVIS PORUKA> Saljem poruku (" << naslov << ", " << sadrzaj << ", " << vaznost << ") putem Web-a..." << endl;
    }
};
/* finija apstrakcija / refined abstraction */
class PorukaSaFajlom: public Poruka {
protected:
    string m_fajl;
public:
    PorukaSaFajlom(string naslov, string sadrzaj, int vaznost, string fajl, ServisSlanjaPoruka *servisSlanjaPoruka)
        : Poruka(naslov, sadrzaj, vaznost, servisSlanjaPoruka), m_fajl(fajl) {}
    virtual ~PorukaSaFajlom() {}
    virtual void postaviFajl(string fajl) { m_fajl = fajl; }
    virtual void posalji() {
        if (m_servisSlanjaPoruka == NULL) {
            cout << "Nije postavljen servis slanja poruka." << endl;
        } else {
            cout << "<PORUKA SA FAJLOM>: saljem poruku(" << m_naslov << ", " << m_sadrzaj << ", " << m_vaznost << ", " << m_fajl << ")" << endl;
            m_servisSlanjaPoruka->posaljiPoruku(m_naslov, m_sadrzaj + " FAJL: " + m_fajl, m_vaznost);
        }
    }
};

int main() {
    /* kreiramo tri razlicita konkretna implementora koji predstavljaju tri razlicita servisa,
    tj. nude tri razlicite implementacije metoda za slanje poruke */
    ServisSlanjaPoruka *emailServisSlanjaPoruka = new EmailServisSlanjaPoruka();
    ServisSlanjaPoruka *webServisSlanjaPoruka = new WebServisSlanjaPoruka();
    ServisSlanjaPoruka *smsServisSlanjaPoruka = new SMSServisSlanjaPoruka();
    /* napravicemo skup objekata razlicitog tipa apstrakcija, u ovom slucaju Poruka i PorukaSaFajlom,
    prilikom kreiranja objekata prosledjivacemo im i implementora, u zavisnosti koji servis
    zelimo da koristimo da bi realizovali metod za slanje poruke */
    vector<Poruka*> poruke;
    poruke.push_back(new Poruka("Vezbe iz OOP2", "Danas u 17", 5, emailServisSlanjaPoruka));
    poruke.push_back(new PorukaSaFajlom("Projekat iz OOP2", "Do 12/12/2015", 3, "projekat.zip", webServisSlanjaPoruka));
    poruke.push_back(new Poruka("Sastanak zgrade", "Pokvaren lift", 10, smsServisSlanjaPoruka));
    /* sve cemo poruke da posaljemo pozivajuci isti metod posalji(), ali ce implementacije da budu razlicite,
    i za objekte iste klase, jer ce da imaju razlicitog implementora pomocu koga ce da realizuju metod
    posalji() */
    for (int i = 0; i < poruke.size(); i ++) {
        poruke[i]->posalji();
    }
    for (int i = 0; i < poruke.size(); i ++) {
        delete poruke[i];
    }
    delete emailServisSlanjaPoruka;
    delete webServisSlanjaPoruka;
    delete smsServisSlanjaPoruka;

    return 0;
}
