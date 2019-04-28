#include <iostream>

using namespace std;

class Crtac {
public:
	virtual void crtajPortret() = 0;
	virtual void crtajPejzaz() = 0;
};

class Pikaso : public Crtac {
	void crtajPortret() { cout << "Portret by Pikaso" << endl; }
	void crtajPejzaz() { cout << "Pejzaz by Pikaso" << endl; }
};

class Rembrandt : public Crtac {
	void crtajPortret() { cout << "Portret by Rembrandt" << endl; }
	void crtajPejzaz() { cout << "Pejzaz by Rembrandt" << endl; }
};

class Platno {
protected:
	Crtac* crtac;
public:
	Platno(Crtac* c): crtac(c){}
	virtual void crtaj() = 0;
	void postaviCrtaca(Crtac* c) {
		crtac = c;
	}
};

class Portret : public Platno {
public:
	Portret(Crtac* c): Platno(c){}
	void crtaj() {
		crtac->crtajPortret();
	}
};

class Pejzaz : public Platno {
public:
	Pejzaz(Crtac* c): Platno(c){}
	void crtaj() {
		crtac->crtajPejzaz();
	}
};

int main(){
	
	Crtac* pikaso = new Pikaso();
	Portret* portret = new Portret(pikaso); // Portret koji ce pikaso da crta
	Pejzaz* pejzaz = new Pejzaz(pikaso);

	portret->crtaj();
	pejzaz->crtaj();

	// Sad ce neki novi umetnik da nacrta isti portret
	portret->postaviCrtaca(new Rembrandt()); // Postavi rembrandt-a da crta portret
	portret->crtaj();

	return 0;
}