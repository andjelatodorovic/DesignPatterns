#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/* napravicemo sablon klasu koja ce kao parametar Komponenta imati komponente
   od kojih ce da kreira slozene/kompozicione komponente
   sablon klasa ima metode za dodavanje/uklanjanje potkomponenti
   klasa Komponente treba da ima samo operacije koje mogu da se izvrsavaju
   nad komponentom */
template<typename Komponenta>
class Sastav: public Komponenta {
protected:
	vector<Komponenta*> deca;
public:
	typedef	typename vector<Komponenta*>::iterator IteratorDece;
	Sastav() {}
	/* metodi za dodavanje i uklanjanje potkomponenti */
	void dodajDete(Komponenta *dete) {
	    IteratorDece it = find(deca.begin(), deca.end(), dete);
		if (it == deca.end()) {
            deca.push_back(dete);
		}
	}
	void izbrisiDete(Komponenta *dete) {
		IteratorDece it = find(deca.begin(), deca.end(), dete);
		if (it != deca.end()) {
            deca.erase(it);
		}
	}
	void izbrisiSve() {
		deca.clear();
	}
	/* u ovom slucaju necemo da pozivamo rekurzivno destruktor */
	virtual ~Sastav() {	}
};

/* apstraktna komponenta od koje cemo da pravimo kompoziciju
   dovoljno je da samo implementira neke operacije koje je moguce izvrsavati na komponenti
   a posao sablon klase Sastav je da vodi racuna o mogucnosti dodavanja/uklanjanja potkomponenti */
class Cvor {
protected:
    int m_tezina;
public:
    Cvor() : m_tezina(0) {}
    Cvor(int tezina) : m_tezina(tezina) {};
	virtual void stampaj() = 0;
	virtual int operacija() = 0;
};
/* konkretna komponenta - u ovom slucaju prosta komponenta/list */
class List: public Cvor {
public:
    List(int tezina): Cvor(tezina) {}
    virtual void stampaj() {
        cout << "<LIST> tezina = " << m_tezina << endl;
    }
    virtual int operacija() {
        cout << "<LIST>.operacija() tezina = " << m_tezina << endl;
        return m_tezina;
    }
};
/* konkretna slozena komponenta / composite koja je izvedena od klase Sastav<Cvor>
   pa tako nasledjuje i metode za dodavanje/uklanjanje potkomponenti */
class UnutrasnjiCvor: public Sastav<Cvor> {
protected:
    int m_tezina;
public:
    UnutrasnjiCvor(int tezina) : m_tezina(tezina) {}
    virtual void stampaj() {
        cout << "<UNUTRASNJI CVOR> tezina = " << m_tezina << endl;
        for (int i = 0; i < deca.size(); i ++) {
            deca[i]->stampaj();
        }
    }
    virtual int operacija() {
        int tezina = m_tezina;
        for (int i = 0; i < deca.size(); i ++) {
            tezina += deca[i]->operacija();
        }
        cout << "<UNUTRASNJI CVOR>.operacija() tezina = " << tezina << endl;
        return tezina;
    }
};

int main() {
    UnutrasnjiCvor *koren = new UnutrasnjiCvor(1);
    UnutrasnjiCvor *lk = new UnutrasnjiCvor(2);
    Cvor *rk = new List(3);
    koren->dodajDete(lk);
    koren->dodajDete(rk);
    koren->stampaj();
    koren->operacija();
    cout << "dodajem decu cvoru lk" << endl;
    Cvor *llk = new List(4);
    Cvor *lrk = new List(5);
    lk->dodajDete(llk);
    lk->dodajDete(lrk);
    koren->stampaj();
    koren->operacija();

    delete koren;
    delete lk;
    delete rk;
    delete llk;
    delete lrk;

    return 0;
}
