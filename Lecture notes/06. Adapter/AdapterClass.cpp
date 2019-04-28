/*
Imamo neki interfejst NoviOblik gde imamo metod nacrtajNovi()
I imamo neku klasu StariOblik oblik sa metodom nactaj()
1. Treba napraviti adapter koji prilagodjava klasu StariOblik interfejsu NoviOblik
2. Uraditi Preko Nasledjivanje klasa
*/

#include <iostream>

using namespace std;

// Interface novi oblik (Target)
class NoviOblik{
public:
	virtual void nacrajNovi()=0;
};

// Adaptee (ono sto treba da se prebaci u Target)
class StariOblik{
public:
	void nacrtaj(){
		cout << "Crtam StariOblik" << endl;
	}
};


// Konkretan novi oblik
class Oblik : public NoviOblik{
public:
	void nacrajNovi(){
		cout << "Crtam konkretan NoviOblik -> Oblik" << endl;
	}
};

class Adapter: private StariOblik, public NoviOblik{
public:
	void nacrajNovi(){
		this->nacrtaj();
	}
};

void crtanje(NoviOblik* n){
	n->nacrajNovi();
};

int main(){
	NoviOblik* o = new Adapter;
	NoviOblik* k = new Oblik;
	crtanje(o);
	crtanje(k);
}
