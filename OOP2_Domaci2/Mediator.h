#pragma once
#include "Profesori.h"

class CentralniServer {
private:
	vector<Ucenik*> ucenik; // sadrzi radove samim tim i ocene kao i podatke o ucenicima
protected:
	Ucenik *student;
	Profesor *profesor;
public:
	typedef vector<Ucenik*>::iterator uit;
	void addUcenik(Ucenik *u) {
		for (uit it = ucenik.begin(); it != ucenik.end(); ++it)
			if ((*it) == u) {
				cout << "Ucenik se vec nalazi na serveru!" << endl;
				return;
			}
		ucenik.push_back(u);
	}
	virtual void setUcenik(Ucenik *_ucenik) { this->student = _ucenik; }
	virtual void setProfesor(Profesor *_profesor) { this->profesor = _profesor;	}
	virtual void sendMessage(const string& message, Osoba *colleague) {
		if (colleague == student) {
			if (profesor == NULL) cout << "ConcreteColleague2 not set up" << endl;
			else profesor->receive(message);
		}
		else if (colleague == profesor) {
			if (student == NULL) cout << "ConcreteColleague1 not set up" << endl;
			else student->receive(message);
		}
	}
	void obavesti(int sifra, float ocena) {
		for (uit it = ucenik.begin(); it != ucenik.end(); ++it)
			if ((*it)->getSifra() == sifra) {
				string ret = "Osvojili ste ukupno " + to_string(ocena) + " poena na prijemnom!";
				sendMessage(ret, (*it));
			}
	}
};