#pragma once
#include "Rad.h" // razlog u Client.cpp

class Ucenik;

class Strategy {
public:
	virtual bool polozio(Ucenik *ucenik) = 0;
	virtual ~Strategy() { }
};

class BrojPoenaNaTestuStrategija : public Strategy {
public:
	virtual bool polozio(Ucenik *ucenik) {
		if (((ucenik->getRad())->getPoeni()) > 25) return 1;
		return 0;
	}
};
class BrojPoenaNaTestuIIzSkole : public Strategy {
public:
	virtual bool polozio(Ucenik *ucenik) {
		if (((ucenik->getRad())->getPoeni()+ucenik->getBrPoena()) > 25) return 1;
		return 0;
	}
};

class DvadesetPostoStrategija : public Strategy {
public:
	virtual bool polozio(Ucenik *ucenik) {
		vector<Ucenik*> u = ucenik->getServer()->getUcenici();
		for (vector<Ucenik*>::iterator uit = u.begin(); uit != u.end(); ++uit)
			if ((*uit)->getPoeni() > racunajdvadesetposto())
				return true;
		return false;
	}
};

class Context {
protected:
	Strategy *strategy;
	Ucenik *ucenik;
public:
	Context(Strategy *strategy,Ucenik *_u) : strategy(strategy), ucenik(_u) {}
	virtual ~Context() { 
		if (strategy != NULL) 
			delete strategy; 
	}
	virtual void ContextInterface(ucenik) {
		if (strategy == NULL) 
			cout << "Strategija nije postavljena" << endl;
		else strategy->polozio();
	}
	virtual void SetStrategy(Strategy *_strategy) {
		if (strategy != NULL) 
			delete strategy;
		strategy = _strategy;
	}
};