#include <iostream>

using namespace std;

// Apstraktan proizvod
class IAuto{
public:
	virtual void getAuto()=0;
};

// Konkretan proizvod izveden iz apstraktnog
class BMW : public IAuto{
public:
	virtual void getAuto(){
		cout << "Auto je BMW" << endl;
	}
};

// Konkretan proizvod dva izveden iz apstraktnog
class Audi : public IAuto{
public:
	virtual void getAuto(){
		cout << "Auto je Audi" << endl;
	}
};

// Apstraktna fabrika, sadrži metode za kreiranje konkretnih proizvoda
class IFabrika {
public:
	virtual IAuto* napraviBMW() =0;
	virtual IAuto* napraviAudi() =0;

};


// Konkretna fabrika
class Automobil : public IFabrika {
private:
	Automobil(){};
	Automobil(const Automobil&){};
	Automobil operator=(const Automobil &){return *this;}

public:
	static Automobil* get(){
		static Automobil instance;
		return &instance;
	}

	IAuto* napraviBMW(){ return new BMW(); }
	IAuto* napraviAudi(){ return new Audi(); }

};


int main(){

	Automobil* fabrika = Automobil::get(); // Fabrika Automobila

	IAuto* BMW = fabrika->napraviBMW();
	IAuto* Audi = fabrika->napraviAudi();

	BMW->getAuto();
	Audi->getAuto();

	delete BMW;
	delete Audi;

}
