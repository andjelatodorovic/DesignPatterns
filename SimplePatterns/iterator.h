#pragma once

/* Implementirati matricu - RowFirstIterator */

#include <cstddef>
using namespace std;

template<class T>
class Matrica;

template<class T>
class MatricaIterator {
	Matrica<T>* mat;
	size_t poz;
public:
	MatricaIterator(Matrica<T>* mat, size_t poz) : mat(mat), poz(poz) {}
	MatricaIterator& operator++ ();
	MatricaIterator operator++ (int);
	MatricaIterator& operator-- ();
	MatricaIterator operator-- (int);
	MatricaIterator operator+ (ptrdiff_t offs) const;
	MatricaIterator operator- (ptrdiff_t offs) const;
	MatricaIterator& operator+= (ptrdiff_t offs);
	MatricaIterator& operator-= (ptrdiff_t offs);
	bool operator< (const MatricaIterator& other) const;
	bool operator> (const MatricaIterator& other) const;
	bool operator== (const MatricaIterator& other) const;
	bool operator!= (const MatricaIterator& other) const;
	bool operator<= (const MatricaIterator& other) const;
	bool operator>= (const MatricaIterator& other) const;
	ptrdiff_t operator- (const MatricaIterator& other) const;
	T operator* () const;
	T& operator* ();
	bool operator! ();

	/* typedefovi */
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference_type;
	// typedef random_access_iterator_tag iterator_category;

	friend class Matrica<T>;
};

template<class T>
class Matrica {
	size_t rows, cols;
	T* data;
public:
	Matrica() : rows(0), cols(0), data(0) {}
	Matrica(size_t rows, size_t cols) : rows(rows), cols(cols), data(new T[rows*cols]) {}
	~Matrica() { delete[] data; }
	
	/* Klasicno indeksiranje */
	T* operator[] (size_t x) { return data + cols*x; }
	const T* operator[] (size_t x) const { return data + cols*x; }

	/* Iterator koji ide red po red */
	typedef MatricaIterator<T> iterator;
	//typedef MatricaConstIterator<T> const_iterator;

	iterator begin() { return iterator(this, 0); }
	iterator end() { return iterator(this, rows*cols); }

	friend class iterator;
	//friend class const_iterator;
};

void iterator_test();