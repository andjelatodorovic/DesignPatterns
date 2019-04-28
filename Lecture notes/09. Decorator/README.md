# Dekorator

Dodaje dodatnu funkcionalnost objektima. Imajte na umu da ne moraju biti svi objekti klase dekorisani vec samo oni koje mi zelimo.

## Klase

* Komponenta
* Subjekat
* Dekorater
* Konkretan dekorater

### Komponenta

Definise interfejs za objekte koji se adaptiraju (`subjekat`).

#### Primer:
```
class Polje {
public:
	virtual void crtaj() = 0;
}
```
### Subjekat

Klasa kojoj se dodaju funkcionalnosti, znaci ovo klasu cemo adaptirati. Izvodi se iz `Komponente`.

#### Primer:
```
class Input : public Polje {
	void crtaj() { cout << "Iscrtavam Input" << endl; }
}
```
### Dekorater

Mora da sadrzi referencu na objekat klase `Komponenta` i nasledjuje interfejs klase `Komponenta`.

#### Primer:
```
class Dekorater : public Polje {
private:
	Polje* ptrPolje; // Pokazivac na objekat klase Komponenta
public:
	Dekorater(Polje* _ptr): ptrPolje(_ptr){}
	void crtaj() { ptrPolje->crtaj(); }
}
```

### Konkretan dekorater

**Izvodi se iz dekoratera** i implementira nove funkcionalnosti i *"dodaje"* je ih subjektu.

#### Primer:
Recimo da hocemo na nas `input` da dodamo i ikonicu.

```
class InputIcon : public Dekorater {
	string icon;
public:
	InputIcon(Polje* _p, string _i = "icon_user"): Dekorater(_p), icon(_i) {}
	void crtaj() {
		Dekorater::crtaj();
		cout << " sa ikonicom " << icon << endl;
	}
}
```

### Primena:

Primena je sledeca, recimo napravimo obicno polje `Input` i recimo zelimo da mu dodamo ikonicu. Napravimo polje sa ikonicom `InputIcon` i prosledimo mu `Input`, sad ako pozovemo metodu crtaj nad poljem sa ikonicom crtace polje sa ikonicom.

```
Polje* input = new Input();
input->crtaj();
// Output: Iscrtavam Input

Polje* ikonica = new InputIcon(input);
ikonica->crtaj();
// Output: Iscrtavam Input sa ikonicom icon_user
```
