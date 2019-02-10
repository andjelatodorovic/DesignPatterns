/* primer adaptiran modifikacijom originalne verzije autora Zaid Gadialija */

#include<iostream>
#include<string>
#include<vector>

using namespace std;

/* komponenta - apstraktna komponenta, u ovom slucaju smo u nju stavili
   metode za dodavanje/uklanjanje potkomponenti
   morace da budu na neki nacin implementirani u prostim komponentama/listovima klasi Leaf */
class ElementZaCrtanje {
public:
    ElementZaCrtanje(string ime) : m_ime(ime) {};
    virtual void dodaj(ElementZaCrtanje* d) = 0;
    virtual void izbrisi(ElementZaCrtanje* d) = 0;
    virtual void prikazi(int razmak) = 0;
    virtual ~ElementZaCrtanje() {};
protected:
    string m_ime;
private:
    ElementZaCrtanje();
};

/* listovi - moramo dati implementaciju za metode dodavanja/uklanjanja potkomponenti */
class OsnovniElementZaCrtanje : public ElementZaCrtanje {
public:
    OsnovniElementZaCrtanje(string ime) : ElementZaCrtanje(ime){};
    void dodaj(ElementZaCrtanje* d) {
        cout << "Ne mogu da dodam element u List" << endl;
    }
    void izbrisi(ElementZaCrtanje* d) {
        cout << "Ne mogu da izbrisem List" << endl;
    }
    void prikazi(int razmak) {
        cout << string(razmak, '~') << " " << m_ime << endl;
    }
    virtual ~OsnovniElementZaCrtanje(){};
private:
    OsnovniElementZaCrtanje();
};

/* kompozicija */
class KompozicijaElemenataZaCrtanje : public ElementZaCrtanje {
public:
    typedef vector<ElementZaCrtanje*>::iterator ElementiIter;
    KompozicijaElemenataZaCrtanje(string ime) : ElementZaCrtanje(ime) {};
    void dodaj(ElementZaCrtanje* d) {
        m_elementi.push_back(d);
    }
    void izbrisi(ElementZaCrtanje* d) {
        for (ElementiIter it = m_elementi.begin(); it != m_elementi.end(); ++ it) {
            if (*it == d) {
                delete d;
                m_elementi.erase(it);
                break;
            }
        }
    }
    void prikazi(int razmak) {
        cout << string(razmak, '~') << "+ " << m_ime <<endl;
        for (ElementiIter it = m_elementi.begin(); it != m_elementi.end(); ++ it) {
            (*it)->prikazi(razmak + 2);
        }
    }
    /* rekurzivno cemo da pozivamo destruktora */
    virtual ~KompozicijaElemenataZaCrtanje() {
        for (ElementiIter it = m_elementi.begin(); it != m_elementi.end(); ++ it) {
            delete *it;
        }
        m_elementi.clear();
    }
private:
    KompozicijaElemenataZaCrtanje();
    vector<ElementZaCrtanje*> m_elementi;
};


int main() {
  KompozicijaElemenataZaCrtanje* slika = new KompozicijaElemenataZaCrtanje("Slika");
  slika->dodaj(new OsnovniElementZaCrtanje("Zuti krug"));
  slika->dodaj(new OsnovniElementZaCrtanje("Plavi pravougaonik"));
  slika->dodaj(new OsnovniElementZaCrtanje("Zeleni pravougaonik"));

  KompozicijaElemenataZaCrtanje* stabloDrveta = new KompozicijaElemenataZaCrtanje("Drvo");
  stabloDrveta->dodaj(new OsnovniElementZaCrtanje("Zeleni krug"));
  stabloDrveta->dodaj(new OsnovniElementZaCrtanje("Braon pravougaonik"));
  slika->dodaj(stabloDrveta);

  OsnovniElementZaCrtanje* ulica = new OsnovniElementZaCrtanje("Bela linija");
  slika->dodaj(ulica);
  OsnovniElementZaCrtanje* staza = new OsnovniElementZaCrtanje("Crna linija");
  slika->dodaj(staza);
  slika->izbrisi(ulica);

  slika->prikazi(0);

  delete slika;

  return 0;
}
