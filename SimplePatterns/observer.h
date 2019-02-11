#pragma once

#include <string>
#include <list>
using namespace std;

class Posmatrani;

class IPosmatrac {
public:
	virtual ~IPosmatrac() {}
	virtual void Obavesti(Posmatrani* ptrPosmatrani) = 0;
protected:
	IPosmatrac() {}
private:
	IPosmatrac(const IPosmatrac&);
	IPosmatrac& operator=(const IPosmatrac&) = default;
};

class Posmatrani {
public:
	virtual ~Posmatrani() {}
	bool DodajPosmatraca(IPosmatrac* ptrPosmatrac);
	bool UkloniPosmatraca(IPosmatrac* ptrPosmatrac);
	bool ObavestiPosmatrace();
	virtual string GetStatus() const = 0;
protected:
	//Ova klasa sluzi samo kao koren hijerarhije
	Posmatrani() : m_listaPosmatraca() {}
private:
	list<IPosmatrac*> m_listaPosmatraca;
	Posmatrani(const Posmatrani&);
	Posmatrani& operator=(const Posmatrani&) = default;
};

/* KONKRETNA KLASA POSMATRANOG OBJETKA */
class Nakit : public Posmatrani {
public:
	Nakit() : m_status("OK") {}
	virtual ~Nakit() {}
	void Kradja() { m_status = "KRADJA"; }
	string GetStatus() const { return m_status; }
private:
	string m_status;
	Nakit(const Nakit& yRef);
	Nakit& operator=(const Nakit& yRef) = default;
};

class SigurnosnaVrata : public IPosmatrac {
public:
	SigurnosnaVrata() : m_status("OTVORENA") {}
	virtual ~SigurnosnaVrata() {}
	void Print() const;
	virtual void Obavesti(Posmatrani* ptrPosmatrani);
private:
	string m_status;
	SigurnosnaVrata(const SigurnosnaVrata&);
	SigurnosnaVrata& operator=(const SigurnosnaVrata&) = default;
};

class Cuvar : public IPosmatrac {
public:
	Cuvar(string ime) :m_ime(ime), m_status("CUVA OBJEKAT") {}
	virtual ~Cuvar() {}
	void Print() const;
	virtual void Obavesti(Posmatrani* ptrPosmatrani);
private:
	string m_ime, m_status;
	Cuvar(const Cuvar&);
	Cuvar& operator=(const Cuvar&) = default;
};

void observer_test();