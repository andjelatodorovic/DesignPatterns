#pragma once

#include <iostream>
#include <string>
#include <list>
using namespace std;

/* Komponenta (interfejs) */
class Komponenta {
public:
	Komponenta(string ime, double plata) : m_Ime(ime), m_plata(plata) {}
	virtual void getPlata(int level) const = 0;
protected:
	string m_Ime;
	double m_plata;
};

/* List hijerarhije - obican radnik */
class Radnik : public Komponenta {
public:
	Radnik(string ime, double plata) : Komponenta(ime, plata) {}
	void getPlata(int level) const;
};

/* Kompozit */
class Menadzer : public Komponenta {
public:
	Menadzer(string ime, double plata) : Komponenta(ime, plata) {}
	void add(Komponenta *cmp);
	void getPlata(int nivo) const;
private:
	list<Komponenta*> m_tim;
};

void composite_test();