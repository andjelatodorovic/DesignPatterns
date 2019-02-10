#pragma once
#include "CommandMemento.h"

class CentralniServer;

class Ucenik {
private:
	string ime, prezime;
	float br_bod_iz_srednje;
	int godina_rodjenja, sifra;
	static int usifra[MAXSIFRA];
	static int count;
	bool odlozenoOcenjivanje;
	Rad *rad;
	InterfejsZaRad *interfejs;
	static CentralniServer *server;
public:
	Ucenik(string _ime, string _prezime, int _godrodj, float _brbod) : ime(_ime), prezime(_prezime), godina_rodjenja(_godrodj), br_bod_iz_srednje(_brbod), odlozenoOcenjivanje(0) {
		this->rad = new Rad();
		this->interfejs = NULL;
		int tempSifra = generisiSifru();
		for (int i = 0; i < count; ++i)
			while (usifra[i] == tempSifra)
				tempSifra = generisiSifru();
		this->sifra = tempSifra;
	}
	inline string getIme()const { return this->ime; }
	inline string getPrezime()const { return this->prezime; }
	inline float getBrBodIzSrednje()const { return this->br_bod_iz_srednje; }
	inline int getGodinaRodjenja()const { return this->godina_rodjenja; }
	inline int getSifra()const { return this->sifra; }
	inline bool getOdlozeno()const { return this->odlozenoOcenjivanje; }
	inline void setOdlozeno(bool value) { this->odlozenoOcenjivanje = value; }
	inline Rad* getRad()const { return this->rad; }
	inline void setRad(string value) { this->rad->setRad(value); }
	inline void setInterfejs(InterfejsZaRad *value) { this->interfejs = value; }
	inline void connectToServer(CentralniServer *_server) { server = _server; }
	// Command
	void komandaNadRadom(Command *command, string rec = "") {
		if (interfejs != NULL) {
			command->setReceiver(this->rad);
			command->setRec(rec);
			(this->interfejs)->setCommand(command);
			(this->interfejs)->invoke();
		}
		else cout << "Postavi interface za rad!" << endl;
	}
	// Memento
	void snimi(Command *command) { // CareTaker se nalazi u klasi Rad
		if (interfejs != NULL) {
			command->setReceiver(this->rad);
			(this->interfejs)->setCommand(command);
			(this->interfejs)->invoke();
		}
		else cout << "Postavi interface za rad!" << endl;
	}
	void ucitaj(Command *command, int index) {
		if (interfejs != NULL) {
			command->setIndex(index);
			command->setReceiver(this->rad);
			(this->interfejs)->setCommand(command);
			(this->interfejs)->invoke();
		}
		else cout << "Postavi interface za rad!" << endl;
	}
	// Mediator
	virtual void send(const string& message) { server->sendMessage(message, this); }
	virtual void receive(const string& message) { cout << "Ucenik.receive(" << message << ")" << endl; }
	inline float getBrPoena()const { return this->rad->getBrPoena(); }
	int generisiSifru() {
		int temp = rand() % 9, r, i = 8;
		while (--i) {
			temp *= 10;
			r = rand() % 9;
			temp += r;
		}
		return temp;
	}
};
int Ucenik::usifra[MAXSIFRA] = { 0 };
int Ucenik::count = 0;
CentralniServer* Ucenik::server = NULL;