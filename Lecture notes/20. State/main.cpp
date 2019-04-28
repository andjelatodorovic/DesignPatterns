/*
	Odlican uzorak kad u toku izvrsavanja hocemo da promenimo ponasanje objekta.

	@Context		Sadrzi referencu na konkretna stanja, u njemu se definise stanje.
	Takodje funkcije iz stanja se redefinisu u konteksu!!!
	@State			Interfejs za sva stanja.
	@ConcreteState	Impementira konkretno ponasanje objekta u nekom stanju
*/

// Recimo uzmemo primer motora koji ima tri stanja: ugasen, paljenje i upaljen.

#include <iostream>
#include <typeinfo> // typeid()
#include "windows.h"

using namespace std;


// State
class iStanjeMotora {
public:
	// Obe ove funkcije treba da redefinisemo u svim stanjima
	virtual void UpaliMotor() = 0;
	virtual void UgasiMotor() = 0;
};

// ConcreteState
class UgasenMotor : public iStanjeMotora {
public:
	void UpaliMotor() { cout << "Pokrecemo paljenje motora" << endl; }
	void UgasiMotor() { cout << "Motor je vec ugasen" << endl; }
};

class PaljenjeMotora : public iStanjeMotora {
public:
	void UpaliMotor() { cout << "Motor se trenutno pali, sacekajte 3 sekunde" << endl; }
	void UgasiMotor() { cout << "Motor se trenutno pali, sacekajte 3 sekunde" << endl; }
};

class UpaljenMotor : public iStanjeMotora {
public:
	void UpaliMotor() { cout << "Moto je vec upaljen" << endl; }
	void UgasiMotor() { cout << "Motor se gasi" << endl; }
};

// Context
class Motor : public iStanjeMotora {
public:
	Motor() : stanje(new UgasenMotor()) {} // Inicijalizujemo motor sa pocetnim stanje (ugasen)
	virtual ~Motor() {}

	iStanjeMotora* TrenutnoStanje() { return stanje; }
	void PromeniStanje(iStanjeMotora* s) { stanje = s; }

	// Sada redefinisemo sve funkcije i kad se pozovu koje je sledece stanje
	void UpaliMotor() {

		stanje->UpaliMotor();
		// Moramo da proverimo da li je trenutno stanje ono koje ustvari treba,
		// kako bi znali gde treba da ga prebacimo
		if (typeid(*stanje) == typeid(UgasenMotor)) {
			PromeniStanje(new PaljenjeMotora());
		}

		if (typeid(*stanje) == typeid(PaljenjeMotora) && (i++) == 1)
			PromeniStanje(new UpaljenMotor());
	}

	void UgasiMotor() {
		stanje->UgasiMotor();
		if (typeid(*stanje) == typeid(UpaljenMotor)) {
			PromeniStanje(new UgasenMotor());
		}
	}
private:
	iStanjeMotora* stanje;
	int i = 0; // Ovo je dummy parametar radi stanja PaljenjeUToku
};

int main() {
	Motor* motor = new Motor();

	motor->UgasiMotor();
	motor->UpaliMotor();
	motor->UpaliMotor();
	motor->UpaliMotor();
	motor->UgasiMotor();
}
/*
	OUTPUT:
	Motor je vec ugasen
	Pokrecemo paljenje motora
	Motor se trenutno pali, sacekajte 3 sekunde
	Moto je vec upaljen
	Motor se gasi
*/
