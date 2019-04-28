
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

class Adapter: public NoviOblik{
private:
	StariOblik *stari;
public:
	Adapter(StariOblik* s): stari(s){};
	void nacrajNovi(){
		stari->nacrtaj();
	}
};

void crtanje(NoviOblik* n){
	n->nacrajNovi();
};

int main(){
	StariOblik* s = new StariOblik();
	NoviOblik* o = new Adapter(s);
	NoviOblik* k = new Oblik;
	crtanje(o);
	crtanje(k);
}
