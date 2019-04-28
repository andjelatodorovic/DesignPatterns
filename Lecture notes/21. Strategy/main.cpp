/*
	Uzorak isti kao i stanje, samo algoritmi :D Koristi se da u toku izvrsavanja klasa
	pormeni svoj algoritam.

	@Context				Sadrzi referencu na konkretan algoritam.
	@Strategy				Interfejs za sva stanja.
	@ConcreteStrategy		Impementira konkretne algoritme
*/

#include <iostream>

using namespace std;

// Strategy
class Sorting {
public:
	virtual void Sort() = 0;
	virtual ~Sorting() {}
};

// ConcreteStrategy
class BubbleSort : public Sorting {
	void Sort() { cout << "Radimo spori bubble sort" << endl; }
};

class MergeSort : public Sorting {
	void Sort() { cout << "Delim na pola i radim brzi MERGE SORT" << endl; }
};

class ShellSort : public Sorting {
	void Sort() { cout << "Najbrzi SHELL SORTTTTTT" << endl; }
};

// Context
class SortingAlgorithms {
public:
	SortingAlgorithms() :algorithm(NULL) {}
	void SetAlgorithm(Sorting* a) {
		algorithm = a;
	}
	void Sort() {
		if (algorithm != NULL) {
			algorithm->Sort();
		} else {
			cout << "NEMA POSTAVLJEN ALGORITAM" << endl;
		}
	}
private:
	Sorting* algorithm;
};


int main() {
	SortingAlgorithms* sortiranje = new SortingAlgorithms();

	sortiranje->Sort();
	sortiranje->SetAlgorithm(new ShellSort());

	sortiranje->Sort();

}
