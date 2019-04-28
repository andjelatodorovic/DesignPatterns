# Muva

Projektni uzorak koji deli **lake** objekte sa ciljem da se izbegne hiperprodukcija.

Kod ovog uzorka je vrlo **važno** razumeti dva stanja koja se javljaju:

* Extrinsic - Spoljašnje
* Intrinsic - Unutrašnje

Bitno je razdvojiti ova dva stanja kod muve, kako bi postigli pravinlnu implementaciju.

**Extrinsic (spoljašnje) stanje**

Je stanje koje je zavisno od okoline, to je stanje koje se **ne pamti** u samoj muvi
već kad se poziva sama muva prenosi se kao parametar. *Na primer, `(x,y)` kordinate
na kojima će se muva prikazati ili veličina u nekim slučajevima*.

**Intrinsic (unutrašnje) stanje**

Je stanje koje pripada muvi po prirodi i trebalo bi biti permanentno zato se i čuva u muvi.
*Na primer, ime muve (ikonice) ili koje slovo predstavlja u fontu*.

## Klase

* IMuva
* Muva/e
* Fabrika Muva

#### IMuva

Deklariše interfejs kroz koji muva prima eksterno stanje.

#### Primer:
```
class Slovo {
public:
	virtual void prikazi(int) = 0; // Extrinsic state
protected:
	Slovo(char _simbol): simbol(_simbol){}
	// Intrinsic state
	char simbol;
};
```

### Muva

Koknretna muva koja se izvodi iz `IMuve`.

#### Primer:
```
class SlovoA : public Slovo {
public:
	SlovoA(): Slovo('A'){}
	void prikazi(int font) {
		cout << "Prikazujem slovo '" << simbol << "' font-size: " << font << "px" << endl;
	}
};
```

### Fabrika Muva

Kreira i upravlja muvama, vrlo je važno da fabrika **čuva napravljene** muve.
Kada klijent zahteva muvu, fabrika prosledi postojeću ili kreira novu.

#### Primer:
```
class Fabrika {
public:
	Slovo* uzmiSlovo(char _slovo) {
		if(slova.find(_slovo) == slova.end()) {
			switch(_slovo) {
				case 'A': slova[_slovo] = new SlovoA();
			}
		}
		return slova[_slovo];
	}
protected:
	map<char, Slovo*> slova;
};
```
