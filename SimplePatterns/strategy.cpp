#include "strategy.h"

void Sorter::dodajBroj(size_t x) {
	niz.push_back(x);
}

vector<size_t> Sorter::dajSortirani() {
	algo->sortiraj(niz);
	return niz;
}

void Sorter::postaviSorter(IAlgoritamSortiranja* algo) {
	this->algo = unique_ptr<IAlgoritamSortiranja>(algo);
}

void STLSort::sortiraj(vector<size_t>& niz) {
	cout << "Sortiram pomocu std::sort" << endl;
	sort(niz.begin(), niz.end());
}

void CountingSort::sortiraj(vector<size_t>& niz) {
	cout << "Sortiram pomocu counting sorta" << endl;

	size_t najveci = *max_element(niz.begin(), niz.end());
	size_t* brojac = new size_t[najveci + 1];
	fill(brojac, brojac + najveci + 1, 0);

	for (size_t x : niz) {
		brojac[x]++;
	}

	size_t idx = 0;
	for (size_t x = 0; x <= najveci; x++) {
		while (brojac[x]--) niz[idx++] = x;
	}

	delete[] brojac;
}

void strategy_test() {
	Sorter sortirac;
	sortirac.postaviSorter(new STLSort);

	for (size_t x : {5, 1, 4, 9}) sortirac.dodajBroj(x);
	auto rezultat = sortirac.dajSortirani();
	for (size_t x : rezultat) cout << x << endl;

	sortirac.postaviSorter(new CountingSort);

	for (size_t x : {2, 1, 3}) sortirac.dodajBroj(x);
	rezultat = sortirac.dajSortirani();
	for (size_t x : rezultat) cout << x << endl;
}