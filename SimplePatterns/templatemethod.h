#pragma once

/* Jako cheesy primer, ali lepo ilustruje poentu */

#include <iostream>
using namespace std;

class Ispit {
protected:
	virtual void ispuniPredispitneObaveze() = 0;
	virtual void poloziPismeniIspit() = 0;
	virtual void poloziUsmeniIspit() = 0;
public:
	virtual ~Ispit() {}
	void odradiIspit();
};

class IspitIzOOP2 : public Ispit {
protected:
	virtual void ispuniPredispitneObaveze();
	virtual void poloziPismeniIspit();
	virtual void poloziUsmeniIspit();
};

class IspitIzUBP : public Ispit {
protected:
	virtual void ispuniPredispitneObaveze();
	virtual void poloziPismeniIspit();
	virtual void poloziUsmeniIspit();
};

/* Implementirati primer sa sablonskim operatorima poredjenja */

void templatemethod_test();