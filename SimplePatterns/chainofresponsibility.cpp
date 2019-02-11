#include "chainofresponsibility.h"

template<ENivoOdgovornosti nivo>
void RadnikL<nivo>::ObradiUpit(Upit upit) {
	if (upit.NivoUpita() <= nivo) {
		/* Trenutni objekat u lancu JESTE sposoban da da odgovor */
		cout << "Odgovor na pitanje: " << upit.StaJeUpit().c_str()
			<< " je dao " << Ime().c_str() << endl;
		return;
	}
	/* Trenutni objekat u lancu NIJE sposoban da da odgovor */
	cout << "Osoba " << Ime().c_str()
		<< " ne moze da obradi trenutni upit. Upit se salje na dalju obradu: "
		<< (PtrToSef()->Ime()).c_str() << endl;
	/* Zahtev se salje na dalju obradu sledecem objektu u lancu odgovornosti */
	PtrToSef()->ObradiUpit(upit);
}


void chainofresponsibility_test() {
	RadnikL<NIZAK> rad("Petar Djuric");
	RadnikL<SREDNJI> sup("Vojislav Mitrovic");
	RadnikL<VISOK> sef("Miroslav Stevanovic");
	rad.PostaviSefa(&sup);
	sup.PostaviSefa(&sef);
	sef.PostaviSefa(0);

	Upit q1("Mozes li da zavrsis ovaj zadatak?", NIZAK);
	Upit q2("Da li tim moze da zavrsi zadatak na vreme?", SREDNJI);
	Upit q3("Da li odeljenje proizvodnje moze da zavrsi zadatak?", VISOK);

	rad.ObradiUpit(q1);
	rad.ObradiUpit(q2);
	rad.ObradiUpit(q3);
}