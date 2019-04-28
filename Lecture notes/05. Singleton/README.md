# Singleton
Singleton je objekat koji se krejira samo **jedno** i nikad više. Obezbeđuje globalan pristup *(globalan objekat)*.

Mogući je *lazi load* (lenje učitavnje) objekta.

**Često ga koriste *apstraktna fabrika*, *graditelj* i *prototip*.**

## Klase

Jedna konkretna klasa koja ima `private` ili `protected`:
* Konstruktor
* Konstruktor kopije
* Operator dodele vrednosti

```
class Singleton{
public:
	static Singleton& get() {
		static Singleton single;
		return single;
	}

private:
	Singleton() {}
	Singleton(const Singleton& drugi) {}
	Singleton& operator=(const Singleton& drugi) {}
}
```

Objekat se poziva u ovom primeru metodom `get`.

```
Singleton& s = Singleton::get();
```

## Diagram:

![UML Diagram](https://sourcemaking.com/files/v2/content/patterns/singleton1.svg)

## Napomena:

Moguca je i implementacija sa if-om unutar statičke metode

```
static Singleton& get() {
	if(single == null){
		single = new Singleton();
	}
	return single;
```

Ova verzija je takođe isprava ali nije **thread safe** u verziji C++03. Tako da
bolje koristiti onaj primer odozogo.
