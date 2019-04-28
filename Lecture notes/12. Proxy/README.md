# Zastupnik

Predstavlja **surogat** drugog objekta koji kotroliše pristup originalnom objektu.
Takođe vrlo važna primena je odlaganje kreiranja i inicijalizacije objekta.

Možda neki realan primer za zastupnika je kreditna kartica, kontroliše pristup u banci.
Isto tako pametna referenca.

## Klase

* ~~Subjekat~~ - **Opcioni** zajednički interfejs za `Zastupnika` i `Realnog subjekta`.
* Realan subjekat
* Zastupnik

### Realan subjekat

Objekat koji treba da radi sa zastupnikom, on prima zahteve od zastupnika.

#### Primer:
```
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
```

### Zastupnik

Unutar zastupnika vrslimo proveru kada pozivmo `Realnog subjekta`.

```
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
```
