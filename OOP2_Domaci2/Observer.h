#pragma once
#include "Rad.h" // razlog u Client.cpp

class Observer {
public:
	virtual void displayStart(Ucenik*) = 0;
	virtual void displayPregled(Ucenik*) = 0;
	virtual void displayFinish(Ucenik*) = 0;
};

class Sajt : public Observer {
public:
	virtual void displayStart(Ucenik *ucenik) { cout << "U izradi..." << endl; }
	virtual void displayPregled(Ucenik *ucenik) { cout << ucenik->getSifra() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
	virtual void displayFinish(Ucenik* ucenik) { cout << ucenik->getIme() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
};

class Displey : public Observer {
public:
	virtual void displayStart(Ucenik *ucenik) { cout << "U izradi..." << endl; }
	virtual void displayPregled(Ucenik *ucenik) { cout << ucenik->getSifra() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
	virtual void displayFinish(Ucenik* ucenik) { cout << ucenik->getIme() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
};
class Tabla : public Observer {
public:
	virtual void displayStart(Ucenik *ucenik) { cout << "U izradi..." << endl; }
	virtual void displayPregled(Ucenik *ucenik) { cout << ucenik->getSifra() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
	virtual void displayFinish(Ucenik* ucenik) { cout << ucenik->getIme() << ": poeni[" << ucenik->getPoeni() << "]" << endl; }
};