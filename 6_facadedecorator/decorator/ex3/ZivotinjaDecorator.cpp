#include <iostream>
#include <memory>

using namespace std;

/* ovaj primer prikazuje eksponencijalnost u broju izvedenih klasa ako zelimo da imamo
   razlicit podskup svojstava na nasim izvedenim potklasama,
   i prikaz resenja pomocu dopuna/dekoratera */

/* apstraktna komponenta */
class IZivotinja {
public:
    virtual string dajOpis() = 0;
};
/* konkretna komponenta */
class CZivotinja: public IZivotinja {
public:
    virtual string dajOpis() { return "CZivotinja: Zivotinja"; }
};
/* konkretna komponenta sa jednim svojstvom - ima krila */
class CZivotinjaSaKrilima: public CZivotinja {
public:
    virtual string dajOpis() { return CZivotinja::dajOpis() + " krilima"; }
};
/* konkretna komponenta - sa cetiri noge */
class CZivotinjaSaCetiriNoge: public CZivotinja {
public:
    virtual string dajOpis() { return CZivotinja::dajOpis() + " sa cetiri noge"; }
};
/* konkretna komponenta - sisar */
class CZivotinjaSisar: public CZivotinja {
public:
    virtual string dajOpis() { return CZivotinja::dajOpis() + " sisar"; }
};
/* konkretna komponenta - sa cetiri noge i sisar */
class CZivotinjaSaCetiriNogeSisar: public CZivotinjaSisar {
public:
    virtual string dajOpis() { return CZivotinjaSisar::dajOpis() + " sa cetiri noge"; }
};
/* konkretna komponenta - sa cetiri noge, sisar i sa krilima */
class CZivotinjaSaCetiriNogeSisarSaKrilima: public CZivotinjaSaCetiriNogeSisar {
public:
    virtual string dajOpis() { return CZivotinjaSaCetiriNogeSisar::dajOpis() + " sa krilima"; }
};
/* konkretna komponenta - sa cetiri noge, i sa krilima */
class CZivotinjaSaCetiriNogeSaKrilima: public CZivotinjaSaCetiriNoge {
public:
    virtual string dajOpis() { return CZivotinjaSaCetiriNoge::dajOpis() + " sa krilima"; }
};

/* apstraktna klasa dopuna / dekoratera - nasledjuje klasu komponenta */
class IDopunaZivotinja: public IZivotinja {
public:
    IDopunaZivotinja(IZivotinja *zivotinja): m_zivotinja(zivotinja) {}
    virtual ~IDopunaZivotinja() { if (m_zivotinja != NULL) delete m_zivotinja; }
    virtual string dajOpis() { return m_zivotinja->dajOpis(); }
protected:
    IZivotinja *m_zivotinja;
};
/* konkretna dopuna/dekorater - dodaje svojstvo cetiri noge */
class CCetiriNogeDopunaZivotinja: public IDopunaZivotinja {
public:
    CCetiriNogeDopunaZivotinja(IZivotinja *zivotinja): IDopunaZivotinja(zivotinja) {}
    virtual ~CCetiriNogeDopunaZivotinja() {}
    virtual string dajOpis() { return m_zivotinja->dajOpis() + " sa cetiri noge"; }
};
/* konkretna dopuna/dekorater - dodaje svojstvo krila */
class CSaKrilimaDopunaZivotinja: public IDopunaZivotinja {
public:
    CSaKrilimaDopunaZivotinja(IZivotinja *zivotinja): IDopunaZivotinja(zivotinja) {}
    virtual ~CSaKrilimaDopunaZivotinja() {}
    virtual string dajOpis() { return m_zivotinja->dajOpis() + " sa krilima"; }
};
/* konkretna dopuna/dekorater - dodaje svojstvo sisar */
class CSisarDopunaZivotinja: public IDopunaZivotinja {
public:
    CSisarDopunaZivotinja(IZivotinja *zivotinja): IDopunaZivotinja(zivotinja) {}
    virtual ~CSisarDopunaZivotinja() {}
    virtual string dajOpis() { return m_zivotinja->dajOpis() + " sisar"; }
};
/* u testiranju kreiracemo razlicite objekte tipa IZivotinja sa razlicitim svojstvima,
   prikazujemo primer kreiranja objekata sa razlicitim svojstvima kao instance potklasa
   koje implementiraju ceo podskup tih svojstava,
   i posle drugi nacin putem dopuna/dekoratera kako mozemo da dodajemo svojstva
   i tokom izvrsavanja/runtime mozemo da dodamo nova svojstva bez da pravimo
   instance objekata potklase sa tim novim podskupom svojstava */
int main() {
   unique_ptr<IZivotinja> sisarSaKrilimaICetiriNoge(
                new CZivotinjaSaCetiriNogeSisarSaKrilima());
    cout << "prikazujem instancu klase CZivotinjaSaCetiriNogeSisarSaKrilima:" << endl;
    cout << "'" << sisarSaKrilimaICetiriNoge->dajOpis() << "'" << endl << endl;

    unique_ptr<IZivotinja> zivotinja(
                new CSisarDopunaZivotinja
                (new CCetiriNogeDopunaZivotinja
                (new CSaKrilimaDopunaZivotinja
                 (new CZivotinja()))));
    cout << "prikazujem instancu zivotinje sa dodatkom/dekoracijom/decorator:" << endl;
    cout << "'" << zivotinja->dajOpis() << "'" << endl << endl;

    cout << "samo zivotinja sisar" << endl;
    cout << (unique_ptr<IZivotinja>(
                new CSisarDopunaZivotinja
                 (new CZivotinja())))->dajOpis() << endl;

    return 0;
}
