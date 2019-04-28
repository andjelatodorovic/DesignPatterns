#include <iostream>

using namespace std;

// Abstraktan proizovd
class IModel{
public:
	virtual void crtaj() = 0;
};

// Konkretan proizvod 1
class Kocka : public IModel{
public:
	void crtaj(){cout << "Ja sam Kocka" <<endl;}
};

// Konkretan proizvod 2
class Trougao : public IModel{
public:
	void crtaj(){cout << "Ja sam Trougao" <<endl;}
};

// Abstraktna fabrika
class IFabrika {
public:
	virtual IModel* napraviKocku() =0;
	virtual IModel* napraviTrouga() =0;

};
// Konkretna fabrika
class Pravougli : public IFabrika {

// Fabrika bi trebala da bude singletone ali to jos nije obradjeno

public:
	IModel* napraviKocku(){ return new Kocka(); }
	IModel* napraviTrouga(){ return new Trougao(); }
};



int main(){
	// Pravimo abstraktnu fabriku
	IFabrika *pravougaonici;

	// Abstraktnoj fabrici dodeljujemo konkretnu fabriku
	pravougaonici = new Pravougli();

	// Pravimo abstrakni proizvod kome ce da dodelimo konkretan proizvod kao za fabriku
	IModel* kocka = pravougaonici->napraviKocku();

	// Iz proizvoda pozivamo konkretan metod (koji je predefinisan u svakom proizvodu);
	kocka->crtaj();

return 0;
}
