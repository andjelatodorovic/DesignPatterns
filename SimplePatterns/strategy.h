#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class IAlgoritamSortiranja {
public:
	virtual void sortiraj(vector<size_t>& niz) = 0;
};

class Sorter {
	unique_ptr<IAlgoritamSortiranja> algo;
	vector<size_t> niz;
public:
	void dodajBroj(size_t x);
	vector<size_t> dajSortirani();
	void postaviSorter(IAlgoritamSortiranja* algo);
};

class STLSort : public IAlgoritamSortiranja {
public:
	virtual void sortiraj(vector<size_t>& niz);
};

class CountingSort : public IAlgoritamSortiranja {
public:
	virtual void sortiraj(vector<size_t>& niz);
};

void strategy_test();