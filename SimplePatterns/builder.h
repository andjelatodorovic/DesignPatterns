#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Racunar, kaci mu se deo po deo */
class Racunar {
public:
	void setKomponenta(const string& deo);
	void start();
protected:
	vector<string> komponente;
};

/* Interfejs graditelja racunara */
class GraditeljRacunara {
public:
	virtual void zapocniGradnju() = 0;
	virtual void napraviProcesor() = 0;
	virtual void napraviMaticnu() = 0;
	virtual void napraviMonitor() = 0;
	virtual Racunar* vratiRezultat() = 0;
};

/* Primer kako treba da izgleda direktor gradnje */

class Direktor {
public:
	Direktor() : ptr(0) {}
	~Direktor();
	void setGraditeljRacunara(GraditeljRacunara* ptr);
	Racunar* getRacunar();
private:
	GraditeljRacunara* ptr;
};

/* Jedan konkretni graditelj koji implementira interfejs */
class DesktopGraditelj : public GraditeljRacunara {
public:
	DesktopGraditelj() : ptr(0) {}
	virtual void zapocniGradnju();
	virtual void napraviProcesor();
	virtual void napraviMaticnu();
	virtual void napraviMonitor();
	virtual Racunar* vratiRezultat();
protected:
	Racunar* ptr;
};

/* Mrzi me da pravim drugog graditelja, you get the idea */

void builder_test();