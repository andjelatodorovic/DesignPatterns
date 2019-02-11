#include "observer.h"

#include <algorithm>
#include <iostream>
using namespace std;

//Dodaje ptrPosmatrac u listu posmatraca
bool Posmatrani::DodajPosmatraca(IPosmatrac* ptrPosmatrac) {
	auto temp = find(m_listaPosmatraca.begin(), m_listaPosmatraca.end(), ptrPosmatrac);

	if (temp != m_listaPosmatraca.end()) return false;

	m_listaPosmatraca.push_back(ptrPosmatrac);
	return true;
}

//Uklanja ptrPosmatrac iz liste posmatraca
bool Posmatrani::UkloniPosmatraca(IPosmatrac* ptrPosmatrac) {
	auto temp = find(m_listaPosmatraca.begin(), m_listaPosmatraca.end(), ptrPosmatrac);

	if (temp == m_listaPosmatraca.end()) return false;

	m_listaPosmatraca.erase(temp);
	return true;
}

/* Ova funkcija implementira kljucno ponasanje uzorka */
bool Posmatrani::ObavestiPosmatrace() {
	for (auto obs : m_listaPosmatraca) {
		obs->Obavesti(this);
	}
	return !m_listaPosmatraca.empty();
}

void SigurnosnaVrata::Print() const {
	cout << "Vrata: " << m_status << endl;
}

void SigurnosnaVrata::Obavesti(Posmatrani* ptrPosmatrani) {
	if (ptrPosmatrani->GetStatus() == "OK")
		m_status = "OTVORENA";
	else
		m_status = "ZATVORENA";
	Print();
}

void Cuvar::Print() const {
	cout << "Cuvar: " << m_ime.c_str() << ' ' << m_status.c_str() << endl;
}

void Cuvar::Obavesti(Posmatrani* ptrPosmatrani) {
	if (ptrPosmatrani->GetStatus() == "OK")
		m_status = "CUVA OBJEKAT";
	else
		m_status = "JURI ULJEZA";
	Print();
}

void observer_test() {
	Cuvar* ptrCuvar1 = new Cuvar("Petar Mrkonjic");
	Cuvar* ptrCuvar2 = new Cuvar("Filip Jaksic");
	SigurnosnaVrata* ptrVrata = new SigurnosnaVrata();
	Nakit* ptrNakit = new Nakit();

	ptrNakit->DodajPosmatraca(ptrCuvar1);
	ptrNakit->DodajPosmatraca(ptrCuvar2);
	ptrNakit->DodajPosmatraca(ptrVrata);
	ptrNakit->ObavestiPosmatrace();
	ptrNakit->Kradja();
	ptrNakit->ObavestiPosmatrace();
}
