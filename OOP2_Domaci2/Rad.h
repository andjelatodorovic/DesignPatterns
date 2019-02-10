#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <map>
#define MAXSIFRA 100
using namespace std;

class CareTaker;
class Memento;

class Rad {
private:
	string rad;
	float poeni;
	CareTaker *ct;
public:
	Rad(); // definicija u CommandMemento.h
	inline string getRad()const { return this->rad; }
	inline void setRad(string value) { this->rad = value; }
	inline float getBrPoena()const { return this->poeni; }
	inline void dodajPoen(float value) { this->poeni += value; }
	inline void oduzmiPoen(float value) { this->poeni -= value; }
	inline CareTaker* getCT()const { return this->ct; }
	inline Memento* createMemento();
	vector<float> istorijaBodovanja;
	virtual ~Rad() {
		delete ct;
	}
};