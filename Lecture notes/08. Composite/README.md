# Kompozicija

Projektni uzorak koji komponuje objekte u strukturu stabla. Omogucava komunikaciju sa slozenom celinom na isti nacin.

## Klase

Klase su prilicno intuitivne:

* IKomponenta
* List
* Kompozicija

### IKomponenta

Apstraktna klasa koja je zajednicka za sve objekte u kompoziciji. U sustini to je najmanji zajednicki deo svih klasa u kompoziciji.

#### Primer:
```
class Vojnik {
public:
	virtual void napadni() = 0;
	virtual void brani() = 0;
}
```

### List

Idividualni objekat koji ce ici uci u kompoziciju, nasledjuje `IKomponenta`.

#### Primer:
```
class Pesak : public Vojnik {
public:
	void napadni() { cout << "Pesak napada" << endl; }
	void napadni() { cout << "Pesak se brani" << endl; }
}
```

### Kompozicija

Nasledjuje `Ikomponenta`, zato sto treba da radi omoguci iste metode samo za svu decu. Takodje bitno je da sadzi komponentu koja cuva *listove* (najcesce vector<>).

#### Primer:
```
class Vod : public Vojnik {
protected:
	vector<Vojnik*> vojska; // Ovde idu listovi
public:
	void regrutuj(Vojnik* v) {
		vojska.push_back(v);
	}
	void napadni() {
		for(int i=0; i < vojska.size(); i++)
			vojska[i]->napadni();
	}

	void odbrani() {
		for(int i=0; i < vojska.size(); i++)
			vojska[i]->odbrani();
	}
};
```