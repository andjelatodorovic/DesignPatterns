#include <iostream>

using namespace std;

// Realan subjekat
class Racun {
public:
	Racun(int _IBAN, int _stanje): IBAN(_IBAN), stanje(_stanje){}
	virtual ~Racun(){}
	virtual bool podigniNovac(int kolicina) {
		if(kolicina <= stanje) {
			cout << "Skinuto: " << kolicina << " RSD sad racuna #" << IBAN << endl;
			return true;
		} else {
			cout << "Transakcija nije uspesna, nemate dovoljno para na racunu" << endl;
		}
	}
protected:
	int IBAN;
	int stanje;
};

// Zastupnik
class Banka : public Racun {
public:
	Banka(int _IBAN, int _stanje, int _r): Racun(_IBAN, _stanje), raspolozivo(_r), racun(NULL){}
	// Ovde vrsimo kontrolu i ako je sve OK onda vrsimo zahtev, Lazy request.
	bool podigniNovac(int kolicina) {
		if(raspolozivo - kolicina > 0 ) {
			if(racun == NULL) {
				racun = new Racun(IBAN, stanje);
			}
			if(racun->podigniNovac(kolicina)) {
				raspolozivo -= kolicina;
				return true;
			}
		}
		cout << "U banci vise nema para, probajte sutra" << endl;
		return false;

	}
	~Banka(){
		if(racun != NULL) delete racun;
	}
protected:
	int raspolozivo;
	Racun* racun;
};


int main(int argc, char *argv[]) {
	Banka* erste = new Banka(124565768, 100, 50);
	erste->podigniNovac(20);
	// Output: Skinuto: 20 RSD sad racuna #124565768

	erste->podigniNovac(50);
	// Output: U banci vise nema para, probajte sutra
	// Ovde smo upravo zaobisli skok do racuna i sacuvali vreme.
}
