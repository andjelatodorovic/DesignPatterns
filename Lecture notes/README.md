# Projektni uzorci

## Sadržaj

### Stvaralacki projetni uzorci

* [Apstraktna fabrika](01. Abstract factory/)
* [Graditelj](02. Builder/)
* ~~Fabricki metod~~
* [Prototip](04. Prototype/)
* [Unikat](05. Singleton/)

### Strukturni projektni uzorci

* [Adapter](06. Adapter/)
* [Most](07. Bridge/)
* [Kompozicija](08. Composite/)
* [Dekorater](09. Decorator/)
* [Fasada](10. Facade/)
* [Muva](11. Flyweight/)
* [Zastupnik](12. Proxy/)


## Podsetnik


<table >
<tr>
<td>Ime Klase</td>
<td>Klasa</td>
<td>Opis</td>
</tr>
<tr>
<td colspan='3' align='center'><strong><strong>Apstraktna fabrika</strong></strong></td>
</tr>
<tr>
<td><code>IFabrika</code></td>
<td><code>virtual UI *napravi_dugme()=0;</code></td>
<td>Zajednicke metode za sve fabrike</td>
</tr>
<tr>
<td><code>Fabrika</code></td>
<td><code>class WindowsFabrika : public IFabrika{}</code></td>
<td>Kokrenta fabrika koja vraca konkretan proizvod</td>
</tr>
<tr>
<td><code>IProizvod</code></td>
<td><code>virtual void crtaj() = 0;</code></td>
<td>Zajednicke metode za sve proizvode</td>
</tr>
<tr>
<td><code>Proizvod</code></td>
<td><code>class WindowsDugme : public Iproizvod{}</code></td>
<td>Konkretan proizvod</td>
</tr>
<tr>
<td colspan='3' align='center'><strong>Prototip</strong></td>
</tr>
<tr>
<td><code>IPrototype</code></td>
<td><code>virtual Iprototype* clone()=0;</code></td>
<td>Ima clone za sve prototipove i jos neke metode</td>
</tr>
<tr>
<td><code>Prototype</code></td>
<td><pre><code>virtual Iprototype* clone(){
IPrototype* tmp = new Prototip1();
tmp->setBroj( getBroj() );
return tmp;
}</code></pre></td>
<td>Kokrentan prototip implementira <code>clone</code>. Vraca kopiju sebe</td>
</tr>
<tr>
<td colspan='3' align='center'><strong>Unikat</strong></td>
</tr>
<tr>
<td><code>singleton</code></td>
<td><pre><code>static Singleton& get() {
static Singleton single;
return single;
}</code></pre></td>
<td>Jednom se samo generise objekat</td>
</tr>
<tr>
<td colspan='3' align='center'><strong>Adapter</strong></td>
</tr>
<tr>
<td><code>NovaKlasa</code></td>
<td><code>virtual void novaMetoda()=0;</code></td>
<td>Klasa u koju hocemo da adaptiramo.</td>
</tr>
<tr>
<td><code>StaraKlasa</code></td>
<td><code>void staraMetoda(){}</code></td>
<td>Klasa koju hocemo da adaptiramo.</td>
</tr>
<tr>
<td><code>AdapterKlase</code></td>
<td><pre><code>class Adapter : private StaraKlasa, public NovaKlasa{
void novaMetod(){
this->staraMetoda();
}
}</code></pre></td>
<td>Privatno nasledjuje <code>Staruklasu</code>, javno <code>Novuklasu</code></td>
</tr>
<tr>
<td><code>AdapterObjekta</code></td>
<td><pre><code>class Adapter : public NovaKlasa{
StaraKlasa *stari
}</code></pre></td>
<td>Adapter čuva referencu na <code>Staruklasu</code> koja se prosleđuje konstruktorom</td>
</tr>
<tr>
<td colspan='3' align='center'><strong>Most</strong></td>
</tr>
<tr>
<td><code>Implementacija</code></td>
<td><code>virtual void crtajPortret() = 0;</code></td>
<td>Sadrzi virtualne funkcije za konkretne implementatore. Koliko ovde metoda imamo toliko imamo i apstrakcija</td>
</tr>
<tr>
<td><code>Implementator</code></td>
<td><pre><code>class Pikaso : public Crtac {
void crtajPortret() {}
}</code></pre></td>
<td>Konkretni implementator koji se izvodi iz<code>Implementacija</code>.</td>
</tr>
<tr>
<td><code>IApstrakcija</code></td>
<td><pre><code>class Platno {
Crtac* crtac;
public:
Platno(Crtac* c): crtac(c){}
virtual void crtaj() = 0;
}</code></pre></td>
<td>Sadzi pokazivac na <code>Implementatora</code> i virtualno metodu za apstrakciju</td>
</tr>
<tr>
<td><code>Apstrakcija</code></td>
<td><pre><code>class Portret : public Platno {
public:
Portret(Crtac* c): Platno(c){}
void crtaj() {
crtac->crtajPortret();
}
};</code></pre></td>
<td>Implementira metodu iz <code>IApstrakcije</code></td>
</tr>
<tr>
<td colspan='3' align='center'><strong>Kompozicija</strong></td>
</tr>
<tr>
<td><code>IList</code></td>
<td><code>virtual void napadni() = 0</code></td>
<td>Apstraktna klasa koja je zajednicka za sve objekte u kompoziciji.</td>
</tr>
<tr>
<td><code>List</code></td>
<td><code>class List : public IList {}</code></td>
<td>Idividualni objekat koji ce ici uci u kompoziciju.</td>
</tr>
<tr>
<td><code>Kompozicija</code></td>
<td><pre><code>class Kompoz : public IList {
vector
	<IList*> listovi;}</code></pre>
	</td>
	<td>Nasleđuje <code>IList</code>, zato što treba da omogući iste metode samo za svu decu. Sadži komponentu koja čuva listove</td>
</tr>
<tr>
	<td colspan='3' align='center'><strong>Dekorater</strong></td>
</tr>
<tr>
	<td><code>Komponenta</code></td>
	<td><code>virtual void crtaj() = 0;</code></td>
	<td>Definise interfejs za objekte koji se adaptiraju</td>
</tr>
<tr>
	<td><code>Subjekat</code></td>
	<td><code>class Input : public Polje {}</code></td>
	<td>Klasu koju adaptiramo, izvodi se iz <code>Komponente</code></td>
</tr>
<tr>
	<td><code>IDekorater</code></td>
	<td><pre><code>class Dekorater : public Polje {
Komonenta* ptrPolje;
public:
Dekorater(Komonenta* _ptr): ptrPolje(_ptr){}
void crtaj() { ptrPolje->crtaj(); }
}</code></pre></td>
	<td>Mora da sadrzi referencu na objekat klase <code>Komponenta</code> i nasledjuje interfejs klase <code>Komponenta</code>.</td>
</tr>
<tr>
	<td><code>Dekorater</code></td>
	<td><code>class InputIcon : public Dekorater {}</code></td>
	<td>Izvodi se iz dekoratera i implementira nove funkcionalnosti i "dodaje" je ih subjektu.</td>
</tr>
<tr>
	<td colspan='3' align='center'><strong>Fasada</strong></td>
</tr>
<tr>
	<td><code>Podsistem</code></td>
	<td><code>class CPU {}</code></td>
	<td>Jedna ili vise kompleksnih klasa koje izvrsavaju zahtev fasade</td>
</tr>
<tr>
	<td><code>Fasada</code></td>
	<td><pre><code>class Kompjuter {
CPU* ptr_cpu;
void start() {
ptr_prav->upali();
ptr_prav->proveri();
}
}</code></pre></td>
	<td>Sadži pokazivače na sve podsisteme, i u nekoj funkciji ih sve poziva. Tako sakriva kompleksnost i izbegava pozivanje u pogrešnom redosledu</td>
</tr>
<tr>
	<td colspan='3' align='center'><strong>Muva</strong></td>
</tr>
<tr>
	<td><code>IMuva</code></td>
	<td><pre><code>class Slovo {
virtual void prikazi(int) = 0;
Slovo(char _simbol): simbol(_simbol){}
char simbol;
};</code></pre></td>
	<td>Deklariše bazu muve. Trebalo bi da sadrži i unutrašnje i spoljašnje stanje</td>
</tr>
<tr>
	<td><code>Muva</code></td>
	<td><pre><code>class SlovoA : public Slovo {
SlovoA(): Slovo('A'){}
void prikazi(int font) {...}
};</code></pre></td>
	<td>Koknretna muva koja se izvodi iz <code>IMuve</code>. I implementira spoljašnje stanje</td>
</tr>
<tr>
	<td><code>Fabrika</code></td>
	<td><pre><code>class Fabrika {
….
map
		<char, Slovo*> slova;
};</code></pre>
		</td>
		<td>Kreira i upravlja muvama, čuva muva i ako postoji ne pravi ih opet</td>
	</tr>
	<tr>
		<td colspan='3' align='center'><strong>Zastupnik</strong></td>
	</tr>
	<tr>
		<td><code>Subjekat</code></td>
		<td><code>class Racun {}</code></td>
		<td>Objekat koji treba da radi sa zastupnikom, on prima zahteve od zastupnika.</td>
	</tr>
	<tr>
		<td><code>Zatupnik</code></td>
		<td><code>class Banka : public Racun {}</code></td>
		<td>Unutar zastupnika proveravamo ulosve i tek onda zovemo <code>Subjekat</code></td>
	</tr>
</table>

---
### Drugi kolokvijum

#### Chain of responsibility _(Logger)_

- Handler: Definise interfase za razresavanje zahteva.
- ConcreteHandler: Konkretan razresivac, izvodi se iz Handler-a. Treba da pokazuje na njegovog sledbenika.

#### Komanda (Televizor)
- Command: Deklarise interfejs za izvrsavanje operacije
- ConcreteCommand: Cuva referencu na Primaoca, implementira Execute koj poziva Primaoca
- Reciever: Izvrsava radnju kad dobij poziv od Konkretne komande
- Invoker: Cuva referencu na komandu, na njemu su poziva izvrsavanje komande


#### Mediator _(Chat)_

- Mediator: Interfase za komunikaciju sa 'kolegama'.
- ConsreteMediator: Implementira komunikaciju izmedju kolega, zna kolege.
- Colleague: Svaki kolega zna svog mediatora i preko njega komunicira sa drugim kolegama.

#### Memento _(Kalkulator)_

- Originator: Subjekat, koji zna da sacuva samog sebe. Na njemu se poziva funkcija Restore()
- Caretaker: Onaj koji cuva listu kreiranih podsetnika
- Memento: Jedan restore point (snapshot), koji cuva sve potrebno da se rekonstruise objekat

#### Observer _(Youtube)_
- Subject: Cuva observere u listi i kad treba obavestva sve pozivom f-je iz Observer
- Observer: Ima funkciju za obavestavanje koja se poziva od strane subjekta
- ConcreteObserver: Redefinise funkciju za obavestavanje

#### State _(Paljenje motora)_
- Context: Sadrzi referencu na konkretna stanja, u njemu se definise stanje. Nasledjuje state
- State: Interfejs za sva stanja.
- ConcreteState: Impementira konkretno ponasanje objekta u nekom stanju

#### Strategy _(Sorting)_

- Context: Sadrzi referencu na konkretan algoritam.
- Strategy: Interfejs za sva stanja.
- ConcreteStrategy: Impementira konkretne algoritme

#### Template method _(Pokretanje motora/igrice)_

- Template: Definise algoritam, i primitivne funkcije (koje su private).
- ConcreteClass: Redefinise primitivne funkcije iz Template-a

#### Visitor _(Bonus plata)_

- Visitor: Sadrzi operacije Poseti() za svaku podklasu Element
- ConcreteVisitor: Implementira operacije Poseti(), implrementira se za svaku potklasu
- Element: Deklarise operaciju Prihvati() posetioca
- ConcreteElement	Implementira prihvacivanje posetioca
- ObjectStructure	Definise intefejs za obilazenje elementa i slanje visitora. Compsite cesto
