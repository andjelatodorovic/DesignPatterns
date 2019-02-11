#include "memento.h"

#include <memory>
using namespace std;

template<class Podsetnik>
inline shared_ptr<Podsetnik> CuvarPodsetnika<Podsetnik>::pop() {
	if (lista.empty()) throw runtime_error("Prazna lista podsetnika");
	shared_ptr<Podsetnik> res = lista.front();
	lista.pop_front();
	return res;
}

template<class Izvedena>
shared_ptr<typename ISubjekat<Izvedena>::Podsetnik_t> ISubjekat<Izvedena>::kreirajPodsetnik() {
	return shared_ptr<Podsetnik_t>(new Podsetnik_t(static_cast<const Izvedena&>(*this)));
}

template<class Izvedena>
inline void ISubjekat<Izvedena>::vratiNaPodsetnik(shared_ptr<Podsetnik_t> mem) {
	static_cast<Izvedena&>(*this) = mem->stanje;
}

template<class T>
ArrayM<T>::ArrayM(const ArrayM & other) :
	size(other.size), capacity(other.capacity), p(new T[capacity])
{
	for (size_t i = 0; i < size; i++) p[i] = other.p[i];
}

template<class T>
ArrayM<T>& ArrayM<T>::operator= (const ArrayM<T>& other) {
	if (this != &other) {
		delete[] p;
		capacity = other.capacity;
		size = other.size;
		p = new T[capacity];
		for (size_t i = 0; i < size; i++) p[i] = other.p[i];
	}
	return *this;
}

void memento_test() {
	ArrayM<double> niz(3);
	niz[0] = 1;
	niz[1] = 2.5;
	niz[2] = 6.25;

	CuvarPodsetnika<ArrayM<double>::Podsetnik_t> cuvar;
	cuvar.push(niz.kreirajPodsetnik());
	niz[1] = 4;

	niz.vratiNaPodsetnik(cuvar.pop());
	cout << niz[0] << ' ' << niz[1] << ' ' << niz[2] << endl;
}