# Prototip
Služi za kreiranje kopija konkretnih objekta, uzimajuću u obzir preformanse.

## Klase
Sastoji se od minimalno 1 apstrakne klase i kokretnih objekta.

### Apstaktan prototip (interface)
Apstraktna klasa koja sadži *čisto virtualnu funkciju* **clone()**.

Konkretno u ovom primeru naši prototipovi imaju neko polje `broj`, pošto je to privatana promenjiva potrebni su nam geteri i seteri.

#### Primer:
```
class ApstraktPrototip{
private:
	int broj;
public:
	virtual ApstraktPrototip* clone()=0;

	int getBroj(){ return broj; }
	void setBroj(int i){ broj = i; }
}
```

### Konkretan prototip (objekat)
Kokretan objekat koji se izvodi iz **apstraknog prototipa**. Unutar ove klase redefinišemo **clone()** funkciju.

#### Primer:
```
class Prototip1 : public ApstraktPrototip{
public:
	virtual ApstraktPrototip* clone(){
		ApstraktPrototip* tmp = new Prototip1();
		tmp->setBroj( getBroj() );
		return tmp;
	}
}
```

## Diagram

![UML Diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/1/14/Prototype_UML.svg/1200px-Prototype_UML.svg.png)
