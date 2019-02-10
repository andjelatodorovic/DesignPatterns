#include <string>
#include <map>
#include <iostream>

using namespace std;

/* naredni primer ne prati direktno sablon apstraktna fabrika (abstract factory pattern) jer
   se unutar apstraktne fabrike cuvaju i konkretne fabrike putem mape ime_konkretnog_objekta -> funkcija za
   kreiranje tog konkretnog objekta koja ima i ulogu konkretne fabrike
   probajte da transformisete ovaj primer da potpuno sledi teorijski model apstraktne fabrike
   i uocite koje su prednosti i mane jednog i drugog pristupa */

/* apstraktni proizvod */
class Zivotinja {
public:
	virtual int brojNoga() const = 0;
	virtual void kazi() = 0;
	virtual void izbrisi() = 0;
};
/* konkretna fabrika: pokazivac na funkciju koja pravi zivotinju, pokazivac na konkretnu fabriku */
typedef Zivotinja* (*NapraviZivotinjuFun)(void);
/* kolekcija konkretnih fabrika cuvana u mapi koja slika ime zivotinje u konkretnu fabriku za tu zivotinju,
   a to je u ovom slucaju funkcija tipa NaraviZivotinjuFun */
typedef map<string, NapraviZivotinjuFun> MapaImeUFabriku;

/* apstraktna fabrika, u sebi ima mapu koja slika ime zivotinje u konkretnu fabriku,
   ta konkretna fabrika ne nasledjuje ovu apstraktnu fabriku vec je samo funkcija koja
   ima ulogu konkretne fabrike */
class FabrikaZivotinja {
private:
	FabrikaZivotinja();
	FabrikaZivotinja(const FabrikaZivotinja &) { }
	FabrikaZivotinja &operator=(const FabrikaZivotinja &) { return *this; }

    MapaImeUFabriku m_skupFabrika;
public:
	~FabrikaZivotinja() {
	    m_skupFabrika.clear();
	}
	static FabrikaZivotinja *uzmiFabriku() {
		static FabrikaZivotinja fabrika;
		return &fabrika;
	}
	void registrujFabriku(const string &imeZivotinje, NapraviZivotinjuFun napraviZivotinjuFun);
	Zivotinja *napraviZivotinju(const string &imeZivotinje);
};

/* konkretan proizvod, koja unutar sebe ima i konkretnu fabriku za Macka */
class Macka : public Zivotinja {
public:
	int brojNoga() const { return 4; }
	void kazi() { cout << "Mjau!" << endl; }
	void izbrisi() { delete this; }

	static Zivotinja *napraviZivotinjuFun() { return new Macka(); }
};
/* konkretan proizvod, koja unutar sebe ima i konkretnu fabriku za Pas */
class Pas : public Zivotinja {
public:
	int brojNoga() const { return 4; }
	void kazi() { cout << "Vau!Vau!" << endl; }
	void izbrisi() { delete this; }

	static Zivotinja *napraviZivotinjuFun() { return new Pas(); }
};
/* konkretan proizvod, koja unutar sebe ima i konkretnu fabriku za Pauk */
class Pauk : public Zivotinja {
public:
	int brojNoga() const { return 8; }
	void kazi() { cout << "......" << endl; }
	void izbrisi() { delete this; }

	static Zivotinja *napraviZivotinjuFun() { return new Pauk(); }
};
/* konkretan proizvod, koja unutar sebe ima i konkretnu fabriku za Konj */
class Konj : public Zivotinja {
public:
	int brojNoga() const { return 4; }
	void kazi() { cout << "Iiiihaa!Iiiihaa!" << endl; }
	void izbrisi() { delete this; }

	static Zivotinja *napraviZivotinjuFun() { return new Konj(); }
};

/* vracanje konkretne fabrike za konkretan proizvod iz mape ime zivotinje -> konkretna fabrika */
FabrikaZivotinja::FabrikaZivotinja() {
	registrujFabriku("Macka", &Macka::napraviZivotinjuFun);
	registrujFabriku("Pas", &Pas::napraviZivotinjuFun);
	registrujFabriku("Pauk", &Pauk::napraviZivotinjuFun);
	registrujFabriku("Konj", &Konj::napraviZivotinjuFun);
}
/* dodavanje nove konkretne fabrike za novi konkretan proizvod */
void FabrikaZivotinja::registrujFabriku(const string &imeZivotinje, NapraviZivotinjuFun napraviZivotinjuFun) {
	m_skupFabrika[imeZivotinje] = napraviZivotinjuFun;
}
/* poziv konkretne fabrike za pravljenje konkretnog proizvoda a poziv je uradjen unutar apstraktne fabrike */
Zivotinja *FabrikaZivotinja::napraviZivotinju(const string &imeZivotinje) {
	MapaImeUFabriku::iterator it = m_skupFabrika.find(imeZivotinje);
	if (it != m_skupFabrika.end()) {
		return it->second();
	}
	return NULL;
}

int main() {
	Zivotinja *zivotinja = NULL;
	string imeZivotinje;

	while (zivotinja == NULL ) {
		cout << "Upisi ime zivotinje (Macka, Pas, Konj, Pauk) ili 'q' za izlaz: ";
		cin >> imeZivotinje;

		if (imeZivotinje == "q" || imeZivotinje == "Q") {
			break;
		}
		zivotinja = FabrikaZivotinja::uzmiFabriku()->napraviZivotinju(imeZivotinje);
		if (zivotinja != NULL) {
			cout << "Tvoja zivotinja ima broj noga: " << zivotinja->brojNoga() << "." << endl;
			cout << imeZivotinje << " kaze ";
			zivotinja->kazi();
			zivotinja->izbrisi();
		} else {
			cout << imeZivotinje << " ne postoji na farmi. Odaberi drugu zivotinju." << endl;
		}
		zivotinja = NULL;
	}
	return 0;
}
