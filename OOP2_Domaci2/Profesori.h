#pragma once
#include "Interpreter.h"

class CentralniServer;

class Profesor {
private:
	Profesor *naredniProf;
	static Profesor *siguranProf;
	static vector<Ucenik*> kasnije;
	static vector<Ucenik*>::iterator itk;
protected:
	string ime;
	static Interpreter *sablon;
	static CentralniServer *server;
public:
	Profesor(string _ime) : ime(_ime), naredniProf(NULL) {}
	virtual void oceni(Ucenik *ucenik) {
		if (naredniProf != NULL) {
			naredniProf->oceni(ucenik);
		}
		else {
			if (siguranProf != NULL)
				siguranProf->oceni(ucenik);
			else
				cout << "Greska! Ni jedan profesor ne moze da pregleda ovaj rad a siguran progesor nije postavljen!" << endl;
		}
	}
	inline void connectToServer(CentralniServer *_server) { server = _server; }
	inline void setNaredniProf(Profesor *prof) { this->naredniProf = prof; }
	inline static void setSiguranProf(Profesor *prof) { siguranProf = prof; }
	inline static Profesor* getSiguranProf() { return siguranProf; }
	inline void setSablon(Interpreter *value) { this->sablon = value; }
	inline bool uzmiILIostavi() { return rand() % 2; }
	virtual void send(const string& message) { server->sendMessage(message, this); }
	virtual void receive(const string& message) { cout << "Profesor.receive(" << message << ")" << endl; }
	void addUKasnije(Ucenik *u) {
		if (kasnije.empty()) {
			kasnije.push_back(u);
			u->setOdlozeno(1);
			return;
		}
		for (itk = kasnije.begin(); itk != kasnije.end(); ++itk)
			if (*itk == u) {
				cout << "Vec je u vektoru" << endl;
				return;
			}
		u->setOdlozeno(1);
		kasnije.push_back(u);
	}
	void oceniSve() {
		itk = kasnije.begin();
		while (itk != kasnije.end())
			oceni(*itk++);
		kasnije.clear();
	}
	virtual ~Profesor() {}
};
vector<Ucenik*> Profesor::kasnije;
vector<Ucenik*>::iterator Profesor::itk;
Profesor* Profesor::siguranProf = NULL;
Interpreter* Profesor::sablon = NULL;
CentralniServer* Profesor::server = NULL;

class ProfesorNovcic : public Profesor {
public:
	ProfesorNovcic(string _ime) : Profesor(_ime) {}
	virtual void oceni(Ucenik *ucenik) {
		int r = rand() % 2 + 1;
		if (r == 1) {
			if (uzmiILIostavi()) {
				cout << this->ime << " : *baca novcic* Pismo!!! Ja cu da pregledam ovaj rad! " << endl;
				cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
				float ocena = sablon->interptet(ucenik->getRad());
				server->obavesti(ucenik->getSifra(), ocena);
			}
			else {
				if (!ucenik->getOdlozeno()) {
					cout << this->ime << " : Kasnije cu da pregledam ovaj rad. " << endl;
					addUKasnije(ucenik);
				}
				else {
					cout << this->ime << " : Ovaj rad je vec odlozen, ja cu da ga pregledam! " << endl;
					cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
					float ocena = sablon->interptet(ucenik->getRad());
					server->obavesti(ucenik->getSifra(), ocena);
				}
			}
		}
		else {
			cout << this->ime << " : *baca novcic* Glava.. Ne mogu ja ovo da pregledam... " << endl;
			Profesor::oceni(ucenik);
		}
	}
};
class ProfesorParan : public Profesor {
public:
	ProfesorParan(string _ime) : Profesor(_ime) {}
	virtual void oceni(Ucenik *ucenik) {
		int temp = ucenik->getSifra();
		int suma = 0;
		while (temp) {
			suma += temp % 10;
			temp /= 10;
		}
		if (suma % 2 == 0) {
			if (uzmiILIostavi()) {
				cout << this->ime << " : Parna sifra! Ja cu da pregledam ovaj rad! " << endl;
				cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
				float ocena = sablon->interptet(ucenik->getRad());
				server->obavesti(ucenik->getSifra(), ocena);
			}
			else {
				if (!ucenik->getOdlozeno()) {
					cout << this->ime << " : Kasnije cu da pregledam ovaj rad. " << endl;
					addUKasnije(ucenik);
				}
				else {
					cout << this->ime << " : Ovaj rad je vec odlozen, ja cu da ga pregledam! " << endl;
					cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
					float ocena = sablon->interptet(ucenik->getRad());
					server->obavesti(ucenik->getSifra(), ocena);
				}
			}
		}
		else {
			cout << this->ime << " : Ne mogu ja ovo da pregledam... " << endl;
			Profesor::oceni(ucenik);
		}
	}
};
class ProfesorDeset : public Profesor {
public:
	ProfesorDeset(string _ime) : Profesor(_ime) {}
	virtual void oceni(Ucenik *ucenik) {
		int temp = ucenik->getSifra();
		int suma = 0; 
		while (temp) {
			suma += temp % 10;
			temp /= 10;
		}
		if (suma % 10 == 0) {
			if (uzmiILIostavi()) {
				cout << this->ime << " : Sifra deljiva sa 10! Ja cu da pregledam ovaj rad! " << endl;
				cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
				float ocena = sablon->interptet(ucenik->getRad());
				server->obavesti(ucenik->getSifra(), ocena);
			}
			else {
				if (!ucenik->getOdlozeno()) {
					cout << this->ime << " : Kasnije cu da pregledam ovaj rad. " << endl;
					addUKasnije(ucenik);
				}
				else {
					cout << this->ime << " : Ovaj rad je vec odlozen, ja cu da ga pregledam! " << endl;
					cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
					float ocena = sablon->interptet(ucenik->getRad());
					server->obavesti(ucenik->getSifra(), ocena);
				}
			}
		}
		else {
			cout << this->ime << " : Ne mogu ja ovo da pregledam... " << endl;
			Profesor::oceni(ucenik);
		}
	}
};
class ProfesorSve : public Profesor {
public:
	ProfesorSve(string _ime) : Profesor(_ime) {}
	virtual void oceni(Ucenik *ucenik) {
		cout << this->ime << " : Nema problema ja gledam sve radove! " << endl;
		cout << this->ime << " trenutno gleda rad koji je radio " << ucenik->getIme() << ' ' << ucenik->getPrezime() << endl;
		float ocena = sablon->interptet(ucenik->getRad());
		server->obavesti(ucenik->getSifra(), ocena);
	}
};