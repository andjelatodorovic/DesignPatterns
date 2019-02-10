#pragma once
#include "Rad.h" // razlog u Client.cpp

class State {
public:
	virtual void Handle(CentralniServer *server, const string& s) = 0;
};

class UIzradi: public State {
public:
	UIzradi() {}
	virtual void Handle(CentralniServer *server, const string& s) {
		if (s == "uizradi" || s == "UIZRADI")
			cout << "Trenutno u izradi" << endl;
		else if (s == "upregledanju" || s == "UPREGLEDANJU")
			server->setState(new UPregledanju());
		else if (s == "kraj" || s == "KRAJ")
			server->setState(new Kraj());
	}
};

class UPregledanju : public State {
public:
	Pregledanje() {}
	virtual void Handle(CentralniServer *server, const string& s) {
		if (s == "uizradi" || s == "UIZRADI")
			server->setState(new UIzradai());
		else if (s == "upregledanju" || s == "UPREGLEDANJU")
			cout << "Trenutno je u fazi pregledanja" << endl;
		else if (s == "kraj" || s == "KRAJ")
			server->setState(new Kraj());
	}
};

class Kraj : public State {
public:
	Kraj() {}
	virtual void Handle(CentralniServer *server, const string& s) {
		if (s == "uizradi" || s == "UIZRADI")
			server->setState(new UIzradi());
		else if (s == "upregledanju" || s == "UPREGLEDANJU")
			server->setState(new UPregledanju());
		else if (s == "kraj")
			cout << "Trenutno je u fazi KRAJ" << endl;
	}
};