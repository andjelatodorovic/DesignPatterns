#include <iostream>

using namespace std;


// Kompleksan pod sistem
class Kocka {
	int x, y, a;
public:
	Kocka(int _x=1, int _y=1, int _a=2): x(_x), y(_y), a(_a) {}
	void crtaj() {
		cout << "Crtam kocku" << endl;
	}
	void racunajKraj() {
		cout << "Kraj kocke je u (" << x+a << ", " << y+a << ")" << endl;
	}

	void povrsina() {
		cout << "Sa povrsinom: " << a*a << endl;
	}
};

// Jos jedan kompleksan pod sistem
class Pravougaonik {
	int x, y,a, b;
public:
	Pravougaonik(int _x=1, int _y=1, int _a=3, int _b=5): x(_x), y(_y), a(_a), b(_b) {}
	void crtaj() { cout << "Crtam pravougaonik" << endl; }

	void orijentacija() {
		if(a>b) cout << "Pravougaonik je uspravan" << endl;
		else cout << "Pravougaonik je polozen" << endl;
	}

	void racunajKraj() { cout << "Kraj pravougaonik je u (" << x+a << ", " << y+b << ")" << endl; }

	void povrsina() { cout << "Sa povrsinom: " << a*b << endl; }
};

class Fasada {
private:
	Pravougaonik* ptr_prav;
	Kocka* ptr_kocka;
public:
	Fasada() {
		ptr_prav = new Pravougaonik();
		ptr_kocka = new Kocka();
	}
	void crtajKocku() {
		ptr_kocka->crtaj();
		ptr_kocka->racunajKraj();
		ptr_kocka->povrsina();
	}
	void crtajPravougaonik() {
		ptr_prav->crtaj();
		ptr_prav->orijentacija();
		ptr_prav->racunajKraj();
		ptr_prav->povrsina();
	}
};

int main() {
	Fasada* oblici = new Fasada();
	oblici->crtajKocku();
}
