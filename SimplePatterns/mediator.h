#pragma once

#include <string>
#include <algorithm>
using namespace std;

/* Interfejs posrednika */
class IPosrednik {
public:
	virtual void PosaljiPoruku(size_t IDSaradnika, const string& message) = 0;
	virtual ~IPosrednik() {}
};

/* Klasa objekata koji ce komunicirati preko posrednika */
class Saradnik {
	IPosrednik* m_ptrPosrednik;
	size_t m_ID;
	string m_ime;
public:
	Saradnik(size_t ID, string ime) : m_ptrPosrednik(0),
		m_ID(ID), m_ime(ime) {}
	size_t getID() const { return m_ID; }
	/* Funkcija kojom se objekat vezuje za posrednika */
	void RegistrujPosrednika(IPosrednik &p) { m_ptrPosrednik = &p; }
	/* Akcije koje mogu da se izvrsavaju nad objektima klase Saradnik */
	void PrimiPoruku(const string &poruka);
	void PosaljiPoruku(size_t ID, const string &poruka);
};

/* Konkretna klasa posrednika */
class Posrednik : public IPosrednik {
	Saradnik **ptrSaradnik;
public:
	Posrednik(size_t num);
	/* Funkcija kojom se posrednik vezuje za saradnika */
	void RegistrujSaradnika(Saradnik& s);
	/* Funkcija kojom se implementira komunikacija sa objektima izmedju kojih posredje */
	void PosaljiPoruku(size_t IDSaradnika, const string& poruka);
	virtual ~Posrednik() { delete[] ptrSaradnik; }
};

void mediator_test();