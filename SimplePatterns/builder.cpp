#include "builder.h"

void builder_test() {
	Direktor k0cc4;
	k0cc4.setGraditeljRacunara(new DesktopGraditelj());
	auto racunar = k0cc4.getRacunar();

	racunar->start();

	delete racunar;
}

void Racunar::setKomponenta(const string & deo) {
	komponente.push_back(deo);
}

void Racunar::start() {
	for (auto deo : komponente) {
		cout << "Pokrecem " << deo << endl;
	}
	cout << "Racunar upaljen!" << endl;
}

Direktor::~Direktor() {
	delete ptr;
}

void Direktor::setGraditeljRacunara(GraditeljRacunara * ptr) {
	delete this->ptr;
	this->ptr = ptr;
}

Racunar* Direktor::getRacunar() {
	ptr->zapocniGradnju();
	ptr->napraviMaticnu();
	ptr->napraviMonitor();
	ptr->napraviProcesor();
	return ptr->vratiRezultat();
}

void DesktopGraditelj::zapocniGradnju() {
	delete ptr;
	ptr = new Racunar();
}

void DesktopGraditelj::napraviProcesor() {
	ptr->setKomponenta("AMD FX-8320 8-core CPU");
}

void DesktopGraditelj::napraviMaticnu() {
	ptr->setKomponenta("Gigabyte 990");
}

void DesktopGraditelj::napraviMonitor() {
	ptr->setKomponenta("LG 22\" (primary)");
	ptr->setKomponenta("Acer 22\" (secondary)");
}

Racunar* DesktopGraditelj::vratiRezultat() {
	return ptr;
	ptr = 0;
}
