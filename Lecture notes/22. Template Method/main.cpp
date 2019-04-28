/*
	Definise skeleton algoritma. Samo se definisu koraci a funkcije se redefinisu
	u nasledjenoj klasi.

	@Template		Definise algoritam, i primitivne funkcije
	@ConcreteClass	Redefinise primitivne funkcije iz Template-a
*/

#include <iostream>

using namespace std;

//Template
class EngineStart {
public:
	// Jedina javna funkcija koj implementira algoritam,
	// unutra ove funkcije se pozivaju ostale funkcije.
	virtual void Start() {
		EngineCheck();
		KeyCheck();
		TurnOn();
	}
private:
	// Privatno definisemo funkcije algoritma
	virtual void EngineCheck() = 0;
	virtual void KeyCheck() = 0;
	virtual void TurnOn() = 0;
};

//ConcreteClass
class DieselEngine : public EngineStart {
private:
	// Redefinisane klase su idalje private zato da bi mogli samo da ih
	// pozovemo preko algoritamske funkcije Start()
	void EngineCheck() {
		cout << "Proveravanje ulja" << endl;
		cout << "Proveravanje bosch pumpu" << endl;
	}
	void KeyCheck() { cout << "Proveravamo kljuc za dizel" << endl; }
	void TurnOn() { cout << "Motor se pali" << endl; }
};

class GasolineEngine : public EngineStart {
private:
	void EngineCheck() {
		cout << "Proveravanje ulja" << endl;
		cout << "Proveravanje svecice" << endl;
	}
	void KeyCheck() { cout << "Proveravamo kljuc za benzinca" << endl; }
	void TurnOn() { cout << "Motor se pali" << endl; }
};

int main() {
	// Primenimo tako sto uzimamo samo konkretnu klasu i na nju zovevmo
	// algoritamsku funkciju Start()
	GasolineEngine* benzinac = new GasolineEngine();
	DieselEngine* dizel = new DieselEngine();

	benzinac->Start();
	dizel->Start();
}
