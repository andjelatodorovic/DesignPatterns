#include "command.h"

void command_test() {
	TV tv;
	MenadzerKomandi commandManager;

	commandManager.IzvrsiKomandu(new KomandaPromeniKanal(&tv, 43));
	cout << "Prebacen na kanal " << tv.Kanal() << endl;

	commandManager.IzvrsiKomandu(new KomandaPromeniKanal(&tv, 39));
	cout << "Prebacen na kanal " << tv.Kanal() << endl;

	commandManager.IzvrsiKomandu(new KomandaPromeniKanal(&tv, 53));
	cout << "Prebacen na kanal " << tv.Kanal() << endl;


	cout << "vracam na prethodni kanal..." << endl;
	commandManager.OtkaziIzvrseno();
	cout << "Trenutni kanal: " << tv.Kanal() << endl;

	cout << "vracam na prethodni kanal..." << endl;
	commandManager.OtkaziIzvrseno();
	cout << "Trenutni kanal: " << tv.Kanal() << endl;


	cout << "Ponovo prebacujem na kanal..." << endl;
	commandManager.PonovoIzvrsi();
	cout << "Trenutni kanal: " << tv.Kanal() << endl;

	cout << "Ponovo prebacujem na kanal..." << endl;
	commandManager.PonovoIzvrsi();
	cout << "Trenutni kanal: " << tv.Kanal() << endl;

}

void KomandaPromeniKanal::Izvrsi() {
	m_stariKanal = m_ptrTV->Kanal();
	m_ptrTV->PromeniKanal(m_noviKanal);
}

void MenadzerKomandi::IsprazniStekove() {
	m_StekOtkaza = stack<IKomanda*>();
	m_StekPonavljanja = stack<IKomanda*>();
}

void MenadzerKomandi::IzvrsiKomandu(IKomanda* komanda) {
	if (m_bOtkaziPokrenut) {
		/* Isprazni stekove otkaza i ponavljanja */
		IsprazniStekove();
		m_bOtkaziPokrenut = false;
	}
	komanda->Izvrsi();
	m_StekOtkaza.push(komanda);
}

void MenadzerKomandi::OtkaziIzvrseno() {
	if (!m_StekOtkaza.empty()) {
		/* Otkazi poslednju komandu */
		m_StekOtkaza.top()->OtkaziIzvrseno();

		/* Dodaj otkazanu komandu u stek otkaza */
		m_StekPonavljanja.push(m_StekOtkaza.top());

		/* Ukloni element sa vrha steka otkaza */
		m_StekOtkaza.pop();
	}
}

void MenadzerKomandi::PonovoIzvrsi() {
	if (!m_StekPonavljanja.empty()) {
		/* Ponovo izvrsi poslednju komandu */
		m_StekPonavljanja.top()->PonovoIzvrsi();

		/* Dodaj ponovljenu komandu u stek otkaza */
		m_StekOtkaza.push(m_StekPonavljanja.top());

		/* Ukloni element sa vrha steka ponavljanja */
		m_StekPonavljanja.pop();
	}
}
