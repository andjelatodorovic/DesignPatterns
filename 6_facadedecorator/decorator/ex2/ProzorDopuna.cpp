#include <iostream>
#include <memory>

using namespace std;

/* apstraktna komponenta */
class IProzor {
public:
    virtual void prikazi() = 0;
    virtual string dajNaziv() = 0;
    virtual ~IProzor() {}
};
/* konkretna komponenta */
class CObicanProzor: public IProzor {
public:
    virtual void prikazi() {
        cout << "CObicanProzor.prikazi(): prikazujem obican prozor" << endl;
    }
    virtual string dajNaziv() {
        return "CObicanProzor";
    }
    virtual ~CObicanProzor() { }
};
/* apstraktna dopuna/dekorater */
class IProzorDopuna: public IProzor {
public:
    IProzorDopuna() { m_prozor = NULL; }
    IProzorDopuna(IProzor *prozor): m_prozor(prozor) {}
    virtual ~IProzorDopuna() { if (m_prozor != NULL) delete m_prozor; }
    virtual void prikazi() {
        if (m_prozor != NULL) {
            m_prozor->prikazi();
        }
    }
    virtual string dajNaziv() {
        if (m_prozor != NULL) {
            return m_prozor->dajNaziv();
        } else {
            return "";
        }
    }
protected:
    IProzor *m_prozor;
};
/* konkretna dopuna - dodaje svostvo da iscrtaje okvir na prozoru */
class COkvirProzorDopuna: public IProzorDopuna {
public:
    COkvirProzorDopuna(IProzor *prozor): IProzorDopuna(prozor) {}
    ~COkvirProzorDopuna() { }
    virtual void prikazi() {
        if (m_prozor != NULL) {
            cout << "COkvirProzorDopuna.prikazi(): prikazujem prozor sa okvirom" << endl;
            m_prozor->prikazi();
            nacrtajOkvir();
        }
    }
    virtual string dajNaziv() {
        if (m_prozor != NULL) {
            return m_prozor->dajNaziv() + " sa okvirom";
        } else {
            return "";
        }
    }
private:
    virtual void nacrtajOkvir() {
        cout << "crtam okvir" << endl;
    }
};
/* konkretan dopuna/dekorater - dodaje skrolbar na prozoru */
class CSkrolbarProzorDopuna: public IProzorDopuna {
public:
    CSkrolbarProzorDopuna(IProzor *prozor): IProzorDopuna(prozor) {}
    ~CSkrolbarProzorDopuna() { }
    virtual void prikazi() {
        if (m_prozor != NULL) {
            cout << "CSkrolbarProzorDopuna.prikazi(): prikazujem prozor sa skrolbarom" << endl;
            m_prozor->prikazi();
            nacrtajSkrolbar();
        }
    }
    virtual string dajNaziv() {
        if (m_prozor != NULL) {
            return m_prozor->dajNaziv() + " sa skrolbarom";
        } else {
            return "";
        }
    }
private:
    virtual void nacrtajSkrolbar() {
        cout << "crtam skrolbar" << endl;
    }
};
/* kreiramo prozor tako sto obogatimo obican prozor svojstvima okvira i skrolbara
   na ovaj nacin ugnjezdenoscu dekoratera mozemo da kombinujemo razlicita svojstva
   koje nude konkretni dekorateri */
int main() {
    unique_ptr<IProzor> prozor(new CSkrolbarProzorDopuna
                                (new COkvirProzorDopuna
                                (new CObicanProzor())));
    cout << "prikazujem prozor:" << endl;
    prozor->prikazi();
    cout << "Prozor ima ime '" << prozor->dajNaziv() << "'" << endl;

    return 0;
}

