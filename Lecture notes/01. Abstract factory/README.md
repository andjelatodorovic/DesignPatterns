# Apstraktna fabrika

Svrha **apstraktne fabrike** je da pruzi zajednicki interface za pravljenje familiju sličnih objekta, bez pravljenja konkretnih klasa.

Klijent ne zna *(ne zanima)* kako i koju ce klasu dobiti, već ga interesuje konkretan rezultat.

## Klase

Sastoji se od minimalno 2 apstraktne klase i 2 konkretne klase.

### Apstraktna fabrika (inteface)

Treba da sadži čiste virtuelne funkcije za kreiranje svih konkretnih proizvoda.

#### Primer:
```
virtual UI *napravi_dugme()=0;
virtual UI *napravi_meni()=0;
```

## Konkretna fabrika
Fabrika nasleđuje interface *(apstraktnu fabriku)*, i redefiniše čiste virtuelne funkcije.

**Mogu da postoje više *različitih, konkretnih* fabrika**

#### Primer:
```
class WindowsFabrika : public ApstraktnaFabrika{};
class LinuxFabrika : public ApstraktnaFabrika{};
class MacOSFabrika : public ApstraktnaFabrika{};
```

## Apstraktan proizvod (interface)
Sadrži čiste virtuelne funkcije koje su zajedničke za sve proizvode **tog tipa**.

#### Primer:
```
virtual void prikazi()=0;
virtual void pomeri()=0;
```

## Kokretan proizvod
Proizvod nasleđuje interface proizvoda *(apstraktni proizvod)*, zatim se redefinišu čiste viruelne funkcije konkretno za taj tip proizvoda.

#### Primer:

```
class WindowsDugme : public ApstraktanProizvod{};
class LinuxDugme : public ApstraktanProizvod{};
class MacOSDugme : public ApstraktanProizvod{};

class WindowsMeni : public ApstraktanProizvod{};
class LinuxMeni : public ApstraktanProizvod{};
class MacOSMeni : public ApstraktanProizvod{};
```

## Rezime
Gore sam uzeo primer za multiplatform UI.

**Proces razmišljanja:**

Proces razmišljanja ide malo u obrnutom smeru, krećemo od proizvoda ka fabrici.
* Na svakom operativnom sistemu nam treba dugme i meni.
* Imamo konkretne proizvode `dugme` i `meni`. **To su dva konkretna proizvoda**
* Svaki od tih proizvoda mora da se prikaze *("nacrta")*. **Znači to je metoda u apstraktnom proizvodu**.
* Svaka fabrika mora da može da napravi konkretan proizvod. **Znači za svaki proizvod nam treba metod u apstraktnoj fabrici*
* Svaki operativni sistem će mi biti fabrika `WindowsFabrika`, `LinuxFabrika` i `MacOSFabrika`.

To je to.

Za linux sistem napravim `LinuxFabrika`-u, iz *apstraktne fabrike* znam da mogu da pozovem `napravi_dugme` i/ili `napravi_meni`.

 A u konkretnoj fabrici (`LinuxFabrika`) je definisano koji to proizvod zovem, u ovom slučaju `LinuxMeni` i/ili `LinuxDugme`.

 Zatim oba proizvada mogu da se nacrtaju pošto to dele preko *apstraknog proizvoda*.


## Diagram

![UML Dijagram](https://upload.wikimedia.org/wikipedia/commons/9/9d/Apstract_factory_UML.svg.png)
