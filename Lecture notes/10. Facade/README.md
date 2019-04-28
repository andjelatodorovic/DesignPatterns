# Fasada

Fasada sluzi da sakrije slozen sistem klasa i obezbedi jedinsven interfejs klijentu, sa kojim klijent moze da upravlja podsistemom. Fasada zna koje klase podsistema su odgovorne za koji zahtev.

## Klase

Struktura je vrlo prosta, ima samo dve klase:

* Klase podsistema
* Fasada

### Klase podsistem

Jedna ili vise kompleksnih klasa koje izvrsavaju zahtev fasade, one nista ne znaju o fasadi.

#### Primer:
Jedan primer sa pravougaonikom koji ima neke "kompleksne" funkcije koje mora da izracuna pre pokretanja.

```
class Pravougaonik {
	int x, y,a, b;
public:
	Pravougaonik(int _x=1, int _y=1, int _a=3, int _b=5): x(_x), y(_y), a(_a), b(_b) {}
	void crtaj() { cout << "Crtam pravougaonik" << endl; }

	void orijentacija() {
		if(a>b) cout << "Pravougaonik je uspravan" << endl;
		else cout << "Pravougaonik je polozen" << endl;
	}

	void racunajKraj() { cout << "Kraj pravougaonik je u (" << x+a << ", " << y+b << ")" << endl; }

	void povrsina() { cout << "Sa povrsinom: " << a*b << endl; }
}
```

### Fasada

Poziva podsisteme i sakriva od klijenta samo kompleksnost.

#### Primer:
```
class Fasada {
private:
	Pravougaonik* ptr_prav;
public:
	Fasada() {
		ptr_prav = new Pravougaonik();
	}
	void crtajPravougaonik() {
		ptr_prav->crtaj();
		ptr_prav->orijentacija();
		ptr_prav->racunajKraj();
		ptr_prav->povrsina();
	}
}
```
---
### Primena

Primena je vrlo prosta i intuitivna. Napravimo fasadu i pozovemo zeljenu metodu.
Da nema fasade, klijen bi morao da pozove sve 4 funkcije (u nasem primeru) posebno, fasad smo obezbedili da pozove samo jednu.

```
Fasada* oblici = new Fasada();
oblici->crtajPravougaonik();
```
