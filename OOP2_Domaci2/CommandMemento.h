#pragma once
#include "Rad.h"

class Memento {
protected:
	string state;
public:
	Memento(string _state) { state = _state; }
	inline string getState() { return this->state; }
};
Memento* Rad::createMemento() {
	return new Memento(this->rad);
}

class CareTaker {
protected:
	vector<Memento*> memento;
public:
	typedef vector<Memento*>::iterator mit;
	Memento* undo() {
		if (memento.size() == 0) cout << "Nema vise prethodnih koraka!" << endl;
		Memento *_memento = memento.back();
		memento.pop_back();
		return _memento;
	}
	Memento* getMemento(int index) {
		if (index < memento.size())
			return memento[memento.size() - index - 1];
		else
			cout << "Index ne postoji!" << endl;
	}
	inline void addMemento(Memento *_memento) { memento.push_back(_memento); }
	~CareTaker() {
		for (mit it = memento.begin(); it != memento.end(); ++it)
			delete *it;
	}
};

// Commands
class Command {
protected:
	Rad *rad;
public:
	virtual void execute() = 0;
	virtual void setReceiver(Rad *rad) = 0;
	virtual void setRec(string rec) = 0;
	virtual void setIndex(int _index) = 0;
	virtual ~Command() {}
};
class IzbrisiRadCommand : public Command {
public:
	IzbrisiRadCommand() {}
	virtual ~IzbrisiRadCommand() {}
	virtual void execute() { 
		(rad->getCT())->addMemento(rad->createMemento());
		rad->setRad(""); 
	}
	virtual void setReceiver(Rad *_rad) { rad = _rad; }
	virtual void setRec(string _rec) {}
	virtual void setIndex(int _index) {}
};
class DodajRecCommand : public Command {
private:
	string rec;
public:
	DodajRecCommand(string _rec = "") : rec(_rec) {}
	virtual ~DodajRecCommand() {}
	virtual void execute() { 
		(rad->getCT())->addMemento(rad->createMemento());
		string temp = rad->getRad() + " " + rec;
		rad->setRad(temp);
	}
	virtual void setReceiver(Rad *_rad) { rad = _rad; }
	virtual void setRec(string _rec) { this->rec = _rec; }
	virtual void setIndex(int _index) {}
};
class IzbrisiSvaPojavljivanjaCommand : public Command {
private:
	string rec;
public:
	IzbrisiSvaPojavljivanjaCommand(string _rec = "") : rec(_rec) {}
	virtual ~IzbrisiSvaPojavljivanjaCommand() {}
	virtual void execute() {
		(rad->getCT())->addMemento(rad->createMemento());
		string temp = rad->getRad();
		temp.replace(temp.find(rec), rec.length(), "");
		rad->setRad(temp);
	}
	virtual void setReceiver(Rad *_rad) { rad = _rad; }
	virtual void setRec(string _rec) { this->rec = _rec; }
	virtual void setIndex(int _index) {}
};

class SnimiVerzijuCoomand : public Command {
public:
	SnimiVerzijuCoomand() {}
	virtual ~SnimiVerzijuCoomand() {}
	virtual void execute() {
		(rad->getCT())->addMemento(rad->createMemento());
	}
	virtual void setReceiver(Rad *_rad) { rad = _rad; }
	virtual void setRec(string _rec) {}
	virtual void setIndex(int _index) {}
};
class UcitajVerzijuCommand : public Command {
private:
	int index;
public:
	UcitajVerzijuCommand(int _index = 0) : index(_index) {}
	virtual ~UcitajVerzijuCommand() {}
	virtual void execute() {
		// cout << "Rad pre vracanja = '" << rad->getRad() << "'" << endl;
		rad->setRad(((rad->getCT())->getMemento(index))->getState());
		// cout << "Rad vracen na = '" << rad->getRad() << "'" << endl;
	}
	virtual void setReceiver(Rad *_rad) { rad = _rad; }
	virtual void setRec(string _rec) {}
	virtual void setIndex(int _index) { this->index = _index; }
};

// Invokers
class InterfejsZaRad {
protected:
	Command *command;
public:
	virtual void invoke() = 0;
	virtual void setCommand(Command *_command) = 0;
	virtual ~InterfejsZaRad() {}
};
class RadNaPapiru : public InterfejsZaRad {
public:
	RadNaPapiru() {}
	virtual void invoke() { // zahteva od komande da izvrsi neku operaciju
		if (command != NULL)
			command->execute();
		else
			cout << "Greska: Invoker nema postavljenu komandu!" << endl;
	}
	virtual void setCommand(Command *_command) { command = _command; }
	virtual ~RadNaPapiru() {}
};
class RadNaTelefonu : public InterfejsZaRad {
public:
	RadNaTelefonu() {}
	virtual void invoke() { // zahteva od komande da izvrsi neku operaciju
		if (command != NULL)
			command->execute();
		else
			cout << "Greska: Invoker nema postavljenu komandu!" << endl;
	}
	virtual void setCommand(Command *_command) { command = _command; }
	virtual ~RadNaTelefonu() {}
};
class RadPrekoInterneta : public InterfejsZaRad {
public:
	RadPrekoInterneta() {}
	virtual void invoke() { // zahteva od komande da izvrsi neku operaciju
		if (command != NULL)
			command->execute();
		else
			cout << "Greska: Invoker nema postavljenu komandu!" << endl;
	}
	virtual void setCommand(Command *_command) { command = _command; }
	virtual ~RadPrekoInterneta() {}
};

Rad::Rad() {
	rad = "";
	poeni = 0;
	ct = new CareTaker();
}