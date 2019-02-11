#include "state.h"

void state_test() {
	Covek kiki, bubi;

	cout << "\nTestiramo Kikija:" << endl;

	kiki.dajLek();
	kiki.cekaj();
	kiki.dajEbolu();
	kiki.dajLek();
	kiki.cekaj();

	cout << "\nTestiramo Bubija:" << endl;

	bubi.cekaj();
	bubi.dajEbolu();
	bubi.cekaj();
	bubi.dajLek();
}

void ZdravCovek::dajEbolu() {
	cout << "Zarazio sam se ebolom." << endl;
}

void ZdravCovek::cekaj() {
	cout << "Zdrav sam!" << endl;
}

void ZdravCovek::dajLek() {
	cout << "Od ovog leka me malo boli glava, ali sam OK" << endl;
}

void CovekSaEbolom::dajEbolu() {
	cout << "Vec imam ebolu... Pomozite mi!" << endl;
}

void CovekSaEbolom::cekaj() {
	cout << "Umirem..." << endl;
}

void CovekSaEbolom::dajLek() {
	cout << "Polako se osecam sve bolje i bolje!" << endl;
}

void MrtavCovek::dajEbolu() {
	cout << "..." << endl;
}

void MrtavCovek::cekaj() {
	cout << "..." << endl;
}

void MrtavCovek::dajLek() {
	cout << "..." << endl;
}

void Covek::dajEbolu() {
	stanje->dajEbolu();
	if (typeid(*stanje) != typeid(MrtavCovek)) {
		stanje = unique_ptr<ICovek>(new CovekSaEbolom);
	}
}

void Covek::cekaj() {
	stanje->cekaj();
	if (typeid(*stanje) != typeid(ZdravCovek)) {
		stanje = unique_ptr<ICovek>(new MrtavCovek);
	}
}

void Covek::dajLek() {
	stanje->dajLek();
	if (typeid(*stanje) != typeid(MrtavCovek)) {
		stanje = unique_ptr<ICovek>(new ZdravCovek);
	}
}
