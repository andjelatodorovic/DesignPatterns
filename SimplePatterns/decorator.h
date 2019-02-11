#pragma once

#include <string>
#include <iostream>
#include <list>
using namespace std;

class BiblElem {
public:
	BiblElem(size_t b) : kopija(b) {}
	void setBrKopija(size_t v);
	size_t getBrKopija();
	virtual void info() = 0;
	virtual ~BiblElem() {}
private:
	size_t kopija;
};

class Knjiga : public BiblElem {
public:
	Knjiga(string autor, string naslov, size_t brKopija) :
		BiblElem(brKopija), autor(autor), naslov(naslov) {}
	void info();
private:
	string autor;
	string naslov;
};

class Video : public BiblElem {
public:
	Video(string reziser, string naslov, int trajanje, size_t brKopija) :
		BiblElem(brKopija), reziser(reziser), naslov(naslov), trajanje(trajanje) {}
	void info();
private:
	string reziser;
	string naslov;
	int trajanje;
};

class Dekorater : public BiblElem {
public:
	Dekorater(BiblElem* ptr) : ptr(ptr), BiblElem(0) {}
	void info();
	size_t getBrKopija() const;
	void setBrKopija(size_t b);
protected:
	BiblElem* ptr;
};

class ZaIzdavanje : public Dekorater {
public:
	ZaIzdavanje(BiblElem* ptr) : Dekorater(ptr) {}
	void pozajmi(string ime);
	void vrati(string ime);
	void info();
protected:
	list<string> zajmici;
};

void decorator_test();