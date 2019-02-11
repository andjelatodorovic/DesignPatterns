#pragma once

#include <memory>
#include <list>
#include <iostream>
#include <string>
using namespace std;

template<typename>
class ISubjekat;

/* Sablon podsetnika */
template <class Subjekat>
class Podsetnik {
public:
	virtual ~Podsetnik() {}
private:
	Subjekat stanje;
	Podsetnik(const Subjekat& stanje) : stanje(stanje) {}
	friend ISubjekat<Subjekat>;
};

/* Sablon klase cuvara podsetnika */
template<class Podsetnik>
class CuvarPodsetnika {
private:
	list<shared_ptr<Podsetnik>> lista;
public:
	void push(shared_ptr<Podsetnik> m) { lista.push_back(m); }
	shared_ptr<Podsetnik> pop();
};

template<class Izvedena>
class ISubjekat {
public:
	typedef Podsetnik<Izvedena> Podsetnik_t;
	typedef CuvarPodsetnika<Podsetnik_t> CuvarPodsetnika_t;

	shared_ptr<Podsetnik_t> kreirajPodsetnik();
	void vratiNaPodsetnik(shared_ptr<Podsetnik_t> mem);
};

class Subjekat : public ISubjekat<Subjekat> {
private:
	string s;
public:
	Subjekat(const string& s) : s(s) {}
	void set(const string& s) { this->s = s; }
	void show() const { cout << s << endl; }
};

template<class T>
class ArrayM : public ISubjekat<ArrayM<T>> {
	size_t size, capacity;
	T* p;
public:
	ArrayM(size_t init_size = 2) : size(init_size), capacity(init_size), p(new T[size]) {}
	ArrayM(const ArrayM& other);
	ArrayM& operator= (const ArrayM& other);
	T operator [] (size_t x) const { return p[x]; }
	T& operator [] (size_t x) { return p[x]; }
};

void memento_test();
