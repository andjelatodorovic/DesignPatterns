#include <iostream>
#include <string>

using namespace std;

//Jedan primer gde hocemo da prilagodimo uticnice.
//Hocemo evropski prikljucak da ukljucimo u ameriku


// Ovo je ono sto znamo
class EuropeProd {
public:
	void ukljuci220() { cout << "Ukljucen uredjaj 220v" << endl; }
};


// Novi interface sa kojim treba da radi
class USAProd {
public:
	virtual void ukljuci() = 0;
};


// Adapter, nasledjuje novi interface
class Adapter :public USAProd {
private:
	EuropeProd *evropa;
public:
	Adapter(EuropeProd* e) : evropa(e){}
	void ukljuci() {
		evropa->ukljuci220();
	}
};

class Uticnica : public USAProd {
public:
	void ukljuci() { cout << "Ukljucen uredjaj 110v" << endl; }
};

int main() {
	USAProd* u = new Uticnica(); // Normalna uticnica
	USAProd* e = new Adapter(new EuropeProd());


	u->ukljuci();
	e->ukljuci();
}