#pragma once
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#include "Profesor.h"

class ICentralniServer;
class IUsers {
public:
	virtual void SetServer(ICentralniServer* server) {m_server = server; }
	virtual void Send(const int receiver, const string message) = 0;
	virtual void Receive(const string message) = 0;
	virtual int getSifra() = 0;
protected:
	ICentralniServer *m_server;
};

class ICentralniServer {
public:
	typedef vector<Ucenik*>::iterator Iter;
	typedef vector<Rad*>::iterator IterRad;

	ICentralniServer() {}
	virtual ~ICentralniServer() {}
	virtual void EnterRoom(Ucenik* user) = 0;
	virtual void ExitRoom(Ucenik* user) = 0;
	virtual void SendMessage(const int receiver, const string message) = 0;
	void addRad(Rad* rad) {
		radovi.push_back(rad);
	}
	void predajRad() {
		string r;
		cout << "Predaj rad: " << endl;
		cin >> r;
		for (Iter it = ucenici.begin(); it != ucenici.end(); ++it) {
			addRad((*it)->dajOdgovor(r));
		}
	}
	void oceniRadove() {
		for (IterRad it = radovi.begin(); it != radovi.end(); ++it) {
			profesor->oceniRad((*it));
		}
	}
protected:
	vector<Ucenik*> ucenici;
	IProfesor* profesor;
	vector<Rad*> radovi;
	vector<IObserver*> posmatraci;
};

class SMSServer : public ICentralniServer {
public:
	SMSServer() {}
	virtual ~SMSServer() { }
	virtual void EnterRoom(Ucenik* user) {
		if (user == NULL) throw("Invalid user");
		user->SetServer(this);
		ucenici.push_back(user);
		cout << "Server > " + to_string(user->getSifra()) + " entered the SMS server." << endl;
	}
	virtual void ExitRoom(Ucenik* user) {
		if (user == NULL) throw("Invalid user");
		user->SetServer(this);
		cout << "Server > " + to_string(user->getSifra()) + " left the SMS server." << endl;
	}
};