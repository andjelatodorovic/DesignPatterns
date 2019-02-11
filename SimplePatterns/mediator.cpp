#include "mediator.h"

#include <iostream>
using namespace std;

/* Akcije koje mogu da se izvrsavaju nad objektima klase Saradnik */

void Saradnik::PrimiPoruku(const string& poruka) {
	cout << "Poruku primio " << m_ime << ": "
		<< poruka.c_str() << endl;
}

void Saradnik::PosaljiPoruku(size_t ID, const string & poruka) {
	cout << m_ime << " salje poruku objektu " << ID
		<< ": " << poruka.c_str() << endl;
	m_ptrPosrednik->PosaljiPoruku(ID, poruka);
}

Posrednik::Posrednik(size_t num) : ptrSaradnik(new Saradnik*[num]) {
	fill(ptrSaradnik, ptrSaradnik + num, nullptr);
}

/* Funkcija kojom se posrednik vezuje za saradnika */

void Posrednik::RegistrujSaradnika(Saradnik & s) {
	if (!ptrSaradnik[s.getID()]) {
		s.RegistrujPosrednika(*this);
		ptrSaradnik[s.getID()] = &s;
	}
}

/* Funkcija kojom se implementira komunikacija sa objektima izmedju kojih posredje */

void Posrednik::PosaljiPoruku(size_t IDSaradnika, const string & poruka) {
	if (ptrSaradnik[IDSaradnika])
		ptrSaradnik[IDSaradnika]->PrimiPoruku(poruka);
}

void mediator_test() {
	Saradnik mitar(0, "Mitar");
	Saradnik joksim(1, "Joksim");
	Saradnik svetlana(2, "Svetlana");

	Posrednik posrednik(3);

	posrednik.RegistrujSaradnika(mitar);
	posrednik.RegistrujSaradnika(joksim);
	posrednik.RegistrujSaradnika(svetlana);

	mitar.PosaljiPoruku(1, "Zdravo, Joksime");
	joksim.PosaljiPoruku(2, "Ceco, znas li sta oce od mene ovaj Mitar?");
	svetlana.PosaljiPoruku(0, "Ej Mitre, sta ima?");
	joksim.PosaljiPoruku(0, "Cao, Mitre!");
}
