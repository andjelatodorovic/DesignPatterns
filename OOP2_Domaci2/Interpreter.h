#pragma once
#include "Ucenik.h"

class Expression {
public:
	virtual float Interpret(Rad *_rad) = 0;
};

class IMAExpression : public Expression {
protected:
	string rec;
	float dodaj;
	float oduzmi;
public:
	IMAExpression(string _rec, float _dodaj, float _oduzmi) : rec(_rec), dodaj(_dodaj), oduzmi(_oduzmi) {}
	virtual float Interpret(Rad *_rad) {
		istringstream in(_rad->getRad());
		string token;
		bool isThere = false;
		while (!in.eof()) {
			in >> token;
			if (token == rec) {
				_rad->istorijaOcenjivanja.push_back(dodaj);
				_rad->dodajPoen(dodaj);
				return dodaj;
			}
		}
		_rad->istorijaOcenjivanja.push_back(-oduzmi);
		_rad->oduzmiPoen(oduzmi);
		return -oduzmi;
	}
};

class NEMAExpression : public Expression {
protected:
	string rec;
	float dodaj;
	float oduzmi;
public:
	NEMAExpression(string _rec, float _dodaj, float _oduzmi) : rec(_rec), dodaj(_dodaj), oduzmi(_oduzmi) {}
	virtual float Interpret(Rad *_rad) {
		istringstream in(_rad->getRad());
		string token;
		bool isThere = false;
		while (!in.eof()) {
			in >> token;
			if (token == rec) {
				_rad->istorijaOcenjivanja.push_back(-oduzmi);
				_rad->oduzmiPoen(oduzmi);
				return -oduzmi;
			}
		}
		_rad->istorijaOcenjivanja.push_back(dodaj);
		_rad->dodajPoen(dodaj);
		return dodaj;
	}
};

class SADRZIExpression : public Expression { // Naravno treba pametnije resenje za detekciju
protected:									 // niza reci mozda vector ili nesto slicno...
	string reci;
	float dodaj;
	float oduzmi;
public:
	SADRZIExpression(string _reci, float _dodaj, float _oduzmi) : reci(_reci), dodaj(_dodaj), oduzmi(_oduzmi) {}
	virtual float Interpret(Rad *_rad) {
		istringstream in(_rad->getRad());
		string token;
		bool isThere = false;
		while (!in.eof()) {
			in >> token;
			if (token == reci) {
				_rad->istorijaOcenjivanja.push_back(dodaj);
				_rad->dodajPoen(dodaj);
				return dodaj;
			}
		}
		_rad->istorijaOcenjivanja.push_back(-oduzmi);
		_rad->oduzmiPoen(oduzmi);
		return -oduzmi;
	}
};

class Interpreter {
protected:
	vector<Expression*> lista;
public:
	typedef vector<Expression*>::iterator lit;
	inline void add(Expression *e) { lista.push_back(e); }
	float interptet(Rad *_rad) {
		float poeni;
		for (lit it = lista.begin(); it != lista.end(); ++it)
			poeni += (*it)->Interpret(_rad);
		return poeni;
	}
	virtual ~Interpreter() {
		for (lit it = lista.begin(); it != lista.end(); ++it)
			delete (*it);
	}
};

class ExspresionParser {
public:
	static Interpreter* Parse(string patern) {
		istringstream in(patern);
		string token;
		Interpreter *ipt = new Interpreter();
		while (!in.eof()) {
			in >> token;
			if (token == "IMA") {
				string r;
				int d, g;
				in >> r;
				in >> d;
				in >> g;
				ipt->add(new IMAExpression(r, d, g));
			}
			else if (token == "NEMA") {
				string r;
				int d, g;
				in >> r;
				in >> d;
				in >> g;
				ipt->add(new NEMAExpression(r, d, g));
			}
			else if (token == "SADRZI") {
				string r;
				int d, g;
				in >> r;
				in >> d;
				in >> g;
				ipt->add(new SADRZIExpression(r, d, g));
			}
		}
		return ipt;
	}
};