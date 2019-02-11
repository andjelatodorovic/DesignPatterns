#include "templatemethod.h"

void Ispit::odradiIspit() {
	ispuniPredispitneObaveze();
	poloziPismeniIspit();
	poloziUsmeniIspit();
}

inline void IspitIzOOP2::ispuniPredispitneObaveze() {
	cout << "Polazem prvi kolokvijum iz OOP2." << endl;
	cout << "Polazem drugi kolokvijum iz OOP2." << endl;
}

inline void IspitIzOOP2::poloziPismeniIspit() {
	cout << "Polozio sam oba kolokvijuma, ne moram da radim pismeni ispit." << endl;
}

inline void IspitIzOOP2::poloziUsmeniIspit() {
	cout << "Polazem usmeni ispit na papiru kod Baneta." << endl;
}

inline void IspitIzUBP::ispuniPredispitneObaveze() {
	cout << "Polazem prvi kolokvijum u Access-u." << endl;
	cout << "Polazem drugi kolokvijum u MySQL-u." << endl;
	cout << "Radim projekat." << endl;
}

inline void IspitIzUBP::poloziPismeniIspit() {
	cout << "Polazem pismeni ispit (Access + MySQL)." << endl;
}

inline void IspitIzUBP::poloziUsmeniIspit() {
	cout << "Profesor me nije oslobodio, radim zavrsni test." << endl;
}

void templatemethod_test() {
	IspitIzOOP2 kodBaneta;
	IspitIzUBP kodTasica;

	kodBaneta.odradiIspit();
	kodTasica.odradiIspit();
}