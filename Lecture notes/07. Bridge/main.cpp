#include <iostream>

using namespace std;

class Crtac{
public:
	virtual void crtajLiniju()=0;
	virtual void crtajKrug()=0;
};

class Crtac1 : public Crtac{
	void crtajKrug(){ cout << "Ja sam Crtac1 i crtam Krug" << endl; }
	void crtajLiniju(){ cout << "Ja sam Crtac1 i crtam Liniju" << endl; }
};

class Crtac2 : public Crtac{
	void crtajKrug(){ cout << "Ja sam Crtac2 i crtam Krug" << endl; }
	void crtajLiniju(){ cout << "Ja sam Crtac2 i crtam Liniju" << endl; }
};

class Oblik{
protected:
	Crtac *crtac;
public:
	Oblik(): crtac(NULL) {}
	Oblik(Crtac* c):crtac(c) {}
	virtual void crtaj()=0;
	void postavi(Crtac* c){
		if(crtac == NULL){
			delete crtac;
		}
		crtac = c;
	
	}

};

class Kvadrat : public Oblik{
private:
	int a,b;
public:
	Kvadrat(int m_a, int m_b): a(m_a), b(m_b) {}
	Kvadrat(int m_a, int m_b, Crtac* c): a(m_a), b(m_b), Oblik(c){}
	void crtaj(){
		cout << "Pozvan metod crtanje kvadrata" <<endl;
		if(crtac != NULL){
			crtac->crtajLiniju();
		} else { cout << "Nema crtaca" << endl;}
	}
};

class Krug : public Oblik{
private:
	int a,b,r;
public:
	Krug(int m_a, int m_b, int m_r): a(m_a), b(m_b), r(m_r) {}
	Krug(int m_a, int m_b, int m_r, Crtac* c): a(m_a), b(m_b), r(m_r), Oblik(c){}
	void crtaj(){
		cout << "Pozvan metod crtanje kruga" <<endl;
		if(crtac != NULL){
			crtac->crtajKrug();
		} else { cout << "Nema crtaca" << endl;}
	}
};


int main(){

	
	Kvadrat *k1 = new Kvadrat(1,2);
	Krug *k2 = new Krug(3,3,2, new Crtac1());

	Crtac *c2 = new Crtac2();

	k1->crtaj();
	k2->crtaj();

	k1->postavi(c2);

	k1->crtaj();

	return 0;
}