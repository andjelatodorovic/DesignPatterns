#pragma once

#include <string>
#include <map>
using namespace std;

class INalivPero {
public:
	virtual string Pisi() = 0;
};

class NalivPeroZlatno : public INalivPero {
public:
	string Pisi();
};

class NalivPeroCelicno : public INalivPero{
public:
	string Pisi();
};

template <typename T>
class Fabrika {
public:
	/* Funkcija koja sluzi za registrovanje fabrickih metoda za
	razlicite tipove Tizveden koji moraju da nasledjuju tip T */
	template <typename Izveden>
	void registrujTip(int IDTipa);

	/* Javna funkcija koja je zaduzena za pravljenje objekta na osnovu
	identifikatora njegovog tipa IDTipa. Preko ove funkcije Klijent trazi
	od fabrike da pozove odgovarajucu fabricki metod za tip koji je on
	identifikovao kljucem, tj. Identifikatorom IDTipa */
	T* napravi(int IDTipa);

private:
	typedef T* (*funkcija)();

	map<int, funkcija> fabrickiMetod;

	/* Staticki sablon Fabrickog Metoda, koji nije deo interfejsa vec
	predstavlja detalj implementacije sablona Fabrike. Instancira se
	prilikom registrovanja za razlicite tipove objekata, koji moraju
	da budu izvedeni iz T */
	template <typename Izveden>
	static T* FabrickiMetod();
};

void factorymethod_test();
