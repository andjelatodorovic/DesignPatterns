#include "composite.h"

void composite_test() {
	//Direktor
	Menadzer direktor("Joksim Mitrovic", 120000.0);

	//Sefovi departmana
	Menadzer sefProizvodnje("Petar Mitic", 90000.0);
	Menadzer glavniInzenjer("Miroslava Stevanovic", 90000.0);
	Menadzer sefKontroleKvaliteta("Danica Pekic", 80000.0);
	Menadzer sefProdaje("Maksimilijan Topalovic", 75000.0);

	//Vodje timova odeljenja inzenjera
	Menadzer vodjaTimaRD("Jovana Stankovic", 70000.0);
	Menadzer vodjaTimaQA("Aleksandar Veljovic", 70000.0);

	//Inzenjeri u odeljenju razvoja
	Radnik programer1("Andrija Djordjevic", 200000.0);
	Radnik programer2("Malica Tosic", 240000.0);
	Radnik tester("Tomislav Stanimirovic", 130000.0);

	// Dodajemo neposredne saradnike direktoru
	direktor.add(&sefProizvodnje);
	direktor.add(&glavniInzenjer);
	direktor.add(&sefKontroleKvaliteta);
	direktor.add(&sefProdaje);

	// Dodajemo neposrednje saradnike glavnom inzenjeru
	glavniInzenjer.add(&vodjaTimaRD);
	glavniInzenjer.add(&vodjaTimaQA);

	// Dodajemo neposredne saradnike vodji tima za istrazivanje i razvoj
	vodjaTimaRD.add(&programer1);
	vodjaTimaRD.add(&programer2);

	// Dodajemo neposredne saradnike vodji tima za osiguravanje kvaliteta
	vodjaTimaQA.add(&tester);

	cout << "Hijerarhija kompanije\n direktor i njegovi saradnici :\n\n";
	direktor.getPlata(0);
	cout << '\n';
}

inline void Radnik::getPlata(int level) const {
	for (int j = 0; j < level; ++j) cout << "\t";
	cout << "Radnik : " << m_Ime.c_str() << ", plata: $" << m_plata << "\n";
}

void Menadzer::add(Komponenta * cmp) {
	m_tim.push_back(cmp);
}

inline void Menadzer::getPlata(int nivo) const {
	for (int j = 0; j < nivo; ++j) cout << "\t";
	cout << "Menadzer : " << m_Ime.c_str() << ", plata: $" << m_plata << "\n";

	if (!m_tim.empty()) {
		for (int x = 0; x < nivo; ++x) cout << "\t";
		cout << "Tim saradnika " << m_Ime.c_str() << ":\n";
		++nivo;
		for (auto mate : m_tim) {
			mate->getPlata(nivo);
		}
	}
}
