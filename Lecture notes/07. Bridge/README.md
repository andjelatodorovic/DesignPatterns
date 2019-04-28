# Most
Projektni uzoram mosta radvaja apstrakciju od njene implementacije, da bi se mogla menjati.

## Klase
Struktura klasa je malo komplikovanija:

* Implementacija
* Implementator
* Apstrakcija
* DoradjenApstrakcija

### Implementacija

Apstraktna klasa koja sadrzi cisto virtualne funkcije za konkretne implementatore.

#### Primer:
```
class Crtac {
public:
	virtual void crtajPortret() = 0;
	virtual void crtajPejzaz() = 0;
}
```
### Implementator(i)

Konkretni implementator(i) koji se izvodi iz `Implementacija`.

#### Primer:
```
class Pikaso : public Crtac {
	void crtajPortret() { cout << "Portret by Pikaso" << endl; }
	void crtajPejzaz() { cout << "Pejzaz by Pikaso" << endl; }
}
```

## Apstrakcija

Apstraktna klasa, definise interfejs apstrakcije i **sadrzi referencu an objekat implementacije**. 
Takodje trebla bi da postoji metoda za menjanje reference.

#### Primer:
```
class Platno {
protected:
	Crtac* crtac;
public:
	Platno(Crtac* c): crtac(c){}
	virtual void crtaj() = 0;
	void postaviCrtaca(Crtac* c) {
		crtac = c;
	}
}
```

## DoradjenApstrakcija

Prosiruje interfejs `Apstrakcija`. Odnosi se na konkretnu apstrakciju iz implementacije.

#### Primer:
```
class Portret : public Platno {
public:
	Portret(Crtac* c): Platno(c){}
	void crtaj() {
		crtac->crtajPortret();
	}
};

class Pejzaz : public Platno {
public:
	Pejzaz(Crtac* c): Platno(c){}
	void crtaj() {
		crtac->crtajPejzaz();
	}
};
```

## Primena

Evo i kako se primenjuje *(naravno ovo se moze u jednoj liniji da se odradi)*:

1) Napravimo crtaca koji hocemo da crta nesto
2) Napravimo ono sto ce crtac da crta *(kod nas u primeru `portret` i `pejzaz`)*
3) Dodelimo objektu koji treba da se crta ko ce ga crtati
4) Nad objektom pozovemo crtanje

```
Crtac* pikaso = new Pikaso();
Portret* portret = new Portret(pikaso); // Portret koji ce pikaso da crta
Pejzaz* pejzaz = new Pejzaz(pikaso);

portret->crtaj(); // Output: Portret by Pikaso
pejzaz->crtaj(); // Output: Pejzaz by Pikaso

// Sad ce neki novi umetnik da nacrta isti portret
portret->postaviCrtaca(new Rembrandt()); // Postavi rembrandt-a da crta portret
portret->crtaj(); // Output: Portret by Rembrandt
```