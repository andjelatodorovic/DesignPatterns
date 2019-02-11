#pragma once

/* Morbidna adaptacija Banetovog primera */

#include <iostream>
#include <typeinfo>
#include <memory>
using namespace std;

class ICovek {
public:
	virtual void dajEbolu() = 0;
	virtual void cekaj() = 0;
	virtual void dajLek() = 0;
	virtual ~ICovek() {}
};

class ZdravCovek : public ICovek {
public:
	virtual void dajEbolu();
	virtual void cekaj();
	virtual void dajLek();
};

class CovekSaEbolom : public ICovek {
public:
	virtual void dajEbolu();
	virtual void cekaj();
	virtual void dajLek();
};

class MrtavCovek : public ICovek {
public:
	virtual void dajEbolu();
	virtual void cekaj();
	virtual void dajLek();
};

class Covek : public ICovek {
	// stanje coveka
	unique_ptr<ICovek> stanje;
public:
	virtual void dajEbolu();
	virtual void cekaj();
	virtual void dajLek();
	Covek() : stanje(unique_ptr<ICovek>(new ZdravCovek)) {}
};

void state_test();