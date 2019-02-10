#include "Mediator.h"

int main() {
	srand(time(NULL));

	// CHAIN OF RESPONSIBILITY

	Profesor *profesor1 = new ProfesorParan("Ivan Stanimirovic");
	Profesor *profesor2 = new ProfesorNovcic("Predrag Krtolica");
	Profesor *profesor3 = new ProfesorDeset("Dejan Ilic");
	Profesor *profesor4 = new ProfesorSve("Branimir Todorovic");

	Profesor::setSiguranProf(profesor4);
	profesor1->setNaredniProf(profesor2);
	profesor2->setNaredniProf(profesor3);
	profesor3->setNaredniProf(Profesor::getSiguranProf());

	Ucenik *ucenik1 = new Ucenik("Zeljko", "Zlatkovic", 1997, 36.35);
	Ucenik *ucenik2 = new Ucenik("Dusan", "Dinic", 1997, 34.11);
	Ucenik *ucenik3 = new Ucenik("Milos", "Sokolovic", 1997, 33.57);
	Ucenik *ucenik4 = new Ucenik("Aleksa", "Mitic", 1997, 38.44);
	Ucenik *ucenik5 = new Ucenik("Vladimir", "Bozic", 1997, 39.12);
	Ucenik *ucenik6 = new Ucenik("Lazar", "Milosevic", 1997, 39.15);
	Ucenik *ucenik7 = new Ucenik("Marko", "Nikolic", 1997, 37.22);
	Ucenik *ucenik8 = new Ucenik("Milena", "Lazarevic", 1997, 38.06);
	Ucenik *ucenik9 = new Ucenik("Aleksa", "Antic", 1997, 36.86);
	Ucenik *ucenik10 = new Ucenik("Jelena", "Vukicevic", 1997, 40.00);

	// INTERPRETER

	string patern = "IMA 1A 5 1 IMA 2B 3 1 NEMA avion 7 2 SADRZI auto,motor,gorivo 10 5";
	Interpreter *ipt = ExspresionParser::Parse(patern);
	profesor1->setSablon(ipt); // moze da se stavi bilo kom prof posto je sablon static u klasi Profesor

	// COMMAND

	InterfejsZaRad *papir = new RadNaPapiru();
	InterfejsZaRad *telefon = new RadNaTelefonu();
	InterfejsZaRad *internet = new RadPrekoInterneta();
	Command *izbrisiRad = new IzbrisiRadCommand();
	Command *dodajRec = new DodajRecCommand();
	Command *izbrisiSvaPonavljanja = new IzbrisiSvaPojavljivanjaCommand();
	Command *snimiVerziju = new SnimiVerzijuCoomand();
	Command *ucitajVerziju = new UcitajVerzijuCommand();

	ucenik1->setInterfejs(internet);
	ucenik1->komandaNadRadom(dodajRec, "1A 2B auto,motor,gorivo");	// index 3
	ucenik1->komandaNadRadom(izbrisiRad);							// index 2
	ucenik1->komandaNadRadom(dodajRec, "avion auto,motor,gorivo");	// index 1
	ucenik1->komandaNadRadom(izbrisiSvaPonavljanja, "avion");		// index 0

	// MEMENTO

	ucenik1->snimi(snimiVerziju);
	ucenik1->ucitaj(ucitajVerziju, 3);

	// MEDIATOR

	CentralniServer *server = new CentralniServer();
	server->addUcenik(ucenik1); server->addUcenik(ucenik2); server->addUcenik(ucenik3); server->addUcenik(ucenik4); server->addUcenik(ucenik5);
	server->addUcenik(ucenik6); server->addUcenik(ucenik7); server->addUcenik(ucenik8); server->addUcenik(ucenik9); server->addUcenik(ucenik10);
	ucenik1->connectToServer(server); // server je static u ucenik tako da moze sa bilo kojom instancom da se poveze
	profesor1->connectToServer(server);

	// Ovde sam izgubio successful build zbog definisanje klasa odnosno njihovoh redosleda kompajliranja
	// Stalno mi javlja gresku "use od undefined type 'BlaBla'" ili "left of '->blabla' must point to class/struct/union/generic type"
	// Tako da nisam testirao, nazalost...
	// Na na kraju mi je i visual studio ubagovao i ne daje mi preporuke
	



	profesor1->oceni(ucenik1);
	profesor1->oceni(ucenik2);
	profesor1->oceni(ucenik3);
	profesor1->oceni(ucenik4);
	profesor1->oceni(ucenik5);
	profesor1->oceni(ucenik6);
	profesor1->oceni(ucenik7);
	profesor1->oceni(ucenik8);
	profesor1->oceni(ucenik9);
	profesor1->oceni(ucenik10);
	profesor1->oceniSve(); // radovi koji su odlozeni se vise ne odlazu 

	// test
	cout << "Ucenik " << ucenik1->getIme() << " osvojio je " << (ucenik1->getRad())->getBrPoena() << " poena na prijemnom!" << endl;

	delete profesor1;	delete profesor2;	delete profesor3;	delete profesor4;
	delete ucenik1;		delete ucenik2;		delete ucenik3;		delete ucenik4;		delete ucenik5;
	delete ucenik6;		delete ucenik7;		delete ucenik8;		delete ucenik9;		delete ucenik10;
	delete papir;		delete telefon;		delete internet;	delete snimiVerziju;
	delete izbrisiRad;	delete dodajRec;	delete izbrisiSvaPonavljanja;			delete ucitajVerziju;

	return 0;
}

/*		Zeljko Zlatkovic
		Indeks 111		       */