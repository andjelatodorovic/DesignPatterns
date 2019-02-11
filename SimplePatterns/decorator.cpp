#pragma once

#include "decorator.h"

void decorator_test() {
	Knjiga knjiga("Radoje Domanovic", "Vodja", 237);
	knjiga.info();

	/*Transforacija knjige u bubliotecki element koji moze da se izdaje */
	ZaIzdavanje knjigaZaIzd(&knjiga);
	knjigaZaIzd.pozajmi("Svetozar Stancic");
	knjigaZaIzd.info();

	/* Kreiranje biblioteckog elementa koji predstavlja video sadrzaj*/
	Video video("Slobodan Sijan", "Ko to tamo peva", 86, 24);
	video.info();

	/* Transformacija videa u bubliotecki element koji moze da se izdaje */
	ZaIzdavanje videoZaIzd(&video);
	videoZaIzd.pozajmi("Petar Petrovic");
	videoZaIzd.pozajmi("Nikola Nikolic");
	videoZaIzd.info();
	videoZaIzd.vrati("Nikola Nikolic");
	videoZaIzd.info();
}

void BiblElem::setBrKopija(size_t v) {
	kopija = v;
}

size_t BiblElem::getBrKopija() {
	return kopija;
}

void Knjiga::info() {
	cout << "\nKnjiga ------ \n";
	cout << " Autor : " << autor << "\n";
	cout << " Naslov : " << naslov << "\n";
	cout << " Broj kopija : " << getBrKopija() << endl;
}

void Video::info() {
	cout << "\nVideo ------ \n";
	cout << " Reziser : " << reziser << "\n";
	cout << " Naslov : " << naslov << "\n";
	cout << " Trajanje : " << trajanje << "\n";
	cout << " Broj kopija : " << getBrKopija() << endl;
}

void Dekorater::info() {
	ptr->info();
}

size_t Dekorater::getBrKopija() const {
	return ptr->getBrKopija();
}

void Dekorater::setBrKopija(size_t b) {
	ptr->setBrKopija(b);
}

void ZaIzdavanje::pozajmi(string ime) {
	size_t b = ptr->getBrKopija();
	if (b == 0) {
		cout << "Nemoguce pozajmiti ovu jedinicu!\n";
	} else {
		zajmici.push_back(ime);
		ptr->setBrKopija(b - 1);
	}
}

void ZaIzdavanje::vrati(string ime) {
	auto it = find(zajmici.begin(), zajmici.end(), ime);
	if (it == zajmici.end()) {
		cout << "Vi niste ni pozajmili ovu jedinicu!\n";
	} else {
		zajmici.erase(it);
		ptr->setBrKopija(ptr->getBrKopija() + 1);
	}
}

void ZaIzdavanje::info() {
	Dekorater::info();
	cout << "Broj pozajmljenih kopija : " << zajmici.size() << "\n";
	for (auto it : zajmici) {
		cout << "Korisnik : " << it << "\n";
	}
}
