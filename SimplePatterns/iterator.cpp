#include "iterator.h"

#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
MatricaIterator<T>& MatricaIterator<T>::operator++ () {
	poz++;
	return *this;
}

template<class T>
MatricaIterator<T> MatricaIterator<T>::operator++ (int) {
	MatricaIterator<T> tmp = *this;
	++*this;
	return tmp;
}

template<class T>
MatricaIterator<T>& MatricaIterator<T>::operator-- () {
	poz--;
	return *this;
}

template<class T>
MatricaIterator<T> MatricaIterator<T>::operator-- (int) {
	MatricaIterator<T> tmp = *this;
	--*this;
	return tmp;
}

template<class T>
MatricaIterator<T> MatricaIterator<T>::operator+ (ptrdiff_t offs) const {
	return MatricaIterator<T>(mat, poz + offs);
}

template<class T>
MatricaIterator<T> MatricaIterator<T>::operator- (ptrdiff_t offs) const {
	return MatricaIterator<T>(mat, poz - offs);
}

template<class T>
MatricaIterator<T>& MatricaIterator<T>::operator+= (ptrdiff_t offs) {
	poz += offs;
	return *this;
}

template<class T>
MatricaIterator<T>& MatricaIterator<T>::operator-= (ptrdiff_t offs) {
	poz -= offs;
	return *this;
}

template<class T>
bool MatricaIterator<T>::operator< (const MatricaIterator& other) const {
	return poz < other.poz;
}

template<class T>
bool MatricaIterator<T>::operator> (const MatricaIterator& other) const {
	return poz > other.poz;
}

template<class T>
bool MatricaIterator<T>::operator== (const MatricaIterator& other) const {
	return poz == other.poz;
}

template<class T>
bool MatricaIterator<T>::operator!= (const MatricaIterator& other) const {
	return poz != other.poz;
}

template<class T>
bool MatricaIterator<T>::operator<= (const MatricaIterator& other) const {
	return poz <= other.poz;
}

template<class T>
bool MatricaIterator<T>::operator>= (const MatricaIterator& other) const {
	return poz >= other.poz;
}

template<class T>
ptrdiff_t MatricaIterator<T>::operator- (const MatricaIterator<T>& other) const {
	return poz - other.poz;
}

template<class T>
T MatricaIterator<T>::operator* () const {
	return mat->data[poz];
}

template<class T>
T& MatricaIterator<T>::operator* () {
	return mat->data[poz];
}

template<class T>
bool MatricaIterator<T>::operator! () {
	return poz < mat->rows * mat->cols;
}

void iterator_test() {
	Matrica<int> brojke(4, 5);

	int y = 0;
	
	/* Ovo je jedan vrlo sveobuhvatni test iteratora inace */
	for (auto& x : brojke) {
		x = ++y;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cout << brojke[i][j] << ' ';
		}
		cout << endl;
	}

	// Ovo ne valja. Ko popravi obavezno neka me obavesti. Verovatno nisam lupio dovoljno typedefova svuda.
	//cout << "Pozicija osmice:" << endl;
	//cout << lower_bound(brojke.begin(), brojke.end(), 8) - brojke.begin() << endl;
}