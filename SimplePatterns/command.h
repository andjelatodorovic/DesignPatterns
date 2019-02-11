#pragma once

#include <stack>
#include <string>
#include <iostream>
using namespace std;

class IKomanda {
public:
	virtual void Izvrsi() = 0;
	virtual void OtkaziIzvrseno() = 0;
	virtual void PonovoIzvrsi() = 0;
	virtual ~IKomanda() {}
};

class TV {
	bool m_ukljucen;
	int m_kanal;
public:
	TV() {}
	void Ukljuci() { m_ukljucen = true; }
	void Iskljuci() { m_ukljucen = false; }
	void PromeniKanal(int kanal) { m_kanal = kanal; }
	bool JeUkljucen() const { return m_ukljucen; }
	int Kanal() const { return m_kanal; }
};

class KomandaUkljuciTV : public IKomanda {
	TV *m_ptrTV;
public:
	KomandaUkljuciTV(TV& tv) : m_ptrTV(&tv) {}
	void Izvrsi() { m_ptrTV->Ukljuci(); }
	void OtkaziIzvrseno() { m_ptrTV->Iskljuci(); }
	void PonovoIzvrsi() { m_ptrTV->Ukljuci(); }
};

class KomandaIskljuciTV : public IKomanda {
	/* Agregira objekat klase KomandaUkljuciTV i radi suprotno */
	/* ovo smo zaista mogli i lepo da otkucamo ali ajde */
	KomandaUkljuciTV m_KomandaUkljuciTV;
public:
	KomandaIskljuciTV(TV &tv) : m_KomandaUkljuciTV(tv) {}
	void Izvrsi() { m_KomandaUkljuciTV.OtkaziIzvrseno(); }
	void OtkaziIzvrseno() { m_KomandaUkljuciTV.Izvrsi(); }
	void PonovoIzvrsi() { m_KomandaUkljuciTV.OtkaziIzvrseno(); }
};

class KomandaPromeniKanal : public IKomanda {
	TV *m_ptrTV;
	int m_stariKanal, m_noviKanal;
public:
	KomandaPromeniKanal(TV *ptv, int kanal) : m_ptrTV(ptv), m_noviKanal(kanal) {}
	void Izvrsi();
	void OtkaziIzvrseno() { m_ptrTV->PromeniKanal(m_stariKanal); }
	void PonovoIzvrsi() { m_ptrTV->PromeniKanal(m_noviKanal); }
};

/* Menadzer komandi je odgovoran za odrzavanje steka otkaza i ponovnog izvrsavanja */
class MenadzerKomandi { /* INVOKER */
	stack< IKomanda* > m_StekOtkaza;
	stack< IKomanda* > m_StekPonavljanja;
	bool m_bOtkaziPokrenut;
	void IsprazniStekove();
public:
	MenadzerKomandi() :m_bOtkaziPokrenut(false) {}
	void IzvrsiKomandu(IKomanda* komanda);
	void OtkaziIzvrseno();
	void PonovoIzvrsi();
};

void command_test();