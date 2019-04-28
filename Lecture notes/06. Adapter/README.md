# Adapter
Prvi od uzorka koji ne pripada kategoriji **kreatora** već **strukturni**.

"Obmotava" već postojeću klasu sa novim interfejsom.

Adapter govori na koji način će stara klasa i novi klijentski definisan interfejs
da komuniciraju.

## Klase

Sadrži minimalno 3 klase:
* Novi interfejs
* Stara klasa
* Adapter

### Ciljna interface (nova klasa)
Nova **apstraktna** klasa u koju hoćemo da prebacimo staru klasu.

#### Primer:

```
class NovaKlasa{
public:
	virtual void novaMetoda()=0;
}
```

### Izvorna klasa

Ovo je originalna klasa koju trebamo preko nove apstrakne klase (`NovaKlasa`) da predstavimo.

#### Primer:

```
class StaraKlasa{
public:
	void staraMetoda(){cout << "Stara metoda" << endl;}
}
```

### Adapter klasa

U ovoj klasi trebamo da "pokažemo" novoj metodi (`novaMetoda`) kako da funkcioniše sa
 starom metodom (`staraMetoda`).

Postoje dve vrste adaptera
* Adapter klase
* Adapter objekta

*Izvorna* i *Ciljna* klase su iste za obe vrste, jedino se razlikuje **Adapter** klasa.


## Način 1: Adapter **Klase**

Klasa adapter **privatno** nasleđuje izvornu klasu `StaraKlasa` i **javno** nasleđuje novi apstraktni interfejs `NovaKlasa`.


Unutar adaptera pozivo stari metod pomoću novog metoda.

#### Primer

```
class Adapter : private StaraKlasa, public NovaKlasa{
public:
	void novaMetod(){
		this->staraMetoda();
	}
}
```
## Način 2: Adapter **objekta**

U ovom slučaju adapter klasu izvodimo iz ciljne klase `NovaKlasa` a sam adapter konstruišemo
iz izvorne klase (`StaraKlasa`).

#### Primer

```
class Adapter : public NovaKlasa{
private:
	StaraKlasa *stari
public:
	// U konstruktur prosleđujemo izvornu klasu kao parametar
	Adapter(StaraKlasa* s): stari(s){};
	void noviMetod(){
		stari->stariMetod();
	}
}
```

## Razlika

Adapter **klase** se oslanja na nasleđivanje klase, tako da ne može za *izvor* da se uzme
apstraktna klasa, već neka konkretna. Šta više ako više *izvora* za svaki posebno **moramo** napisati
adapter.

Kod adaptera *objekta* mi pravimo na neki način *"wrapper"* oko stare klase, takođe klasu
prosleđujemo kao argument, tako da je *moguće* da se više klasa adaptira preko jednog adaptera.

*Kod adaptera objekta, nije uvek moguće adaptirati više klasa, to je moguće ako dele osobine koje adaptiramo*

## Diagram

**Adapter objekta:**

![UML dijagram adaptera objketa][1]

**Adapter klase:**

![UML dijagram adaptear klase][2]

[1]: https://upload.wikimedia.org/wikipedia/commons/d/d7/ObjectAdapter.png
[2]: https://upload.wikimedia.org/wikipedia/commons/3/35/ClassAdapter.png
