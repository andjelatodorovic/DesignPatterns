/* primer iz knjige Design Patterns Explained Simply. */

/* ovo su primeri koda gde je kod napisan prvo bez koriscenja sablona apstraktna fabrika (abstract factory pattern)
   a u drugom je primer gde je kod izmenjem primenom sablona apstraktne fabrike */

/* ovo je kod nakon upotrebe sablona apstraktne fabrike. Sada je direktiva upotrebljena samo na
   jednom mestu i to prilikom odabira fabrike za generisanje objekata za GUI. Ovo u mnogome olaksava
   ispravljanje programa kao i prosirivanje njegovih funkcija */
// #define LINUX_OS  // direktiva za koriscenje Linux grafickih UI elemenata
#define WINDOWS_OS

#include <iostream>

using namespace std;

/* apstraktni proizvod */
class ElementUI {
public:
   virtual void nacrtaj() = 0;
};

/* konkretan proizvod A1 */
class LinuxDugme : public ElementUI {
public:
   void nacrtaj() { cout << "LinuxDugme\n"; }
};

/* konkretan proizvod A2 */
class LinuxMenu : public ElementUI {
public:
   void nacrtaj() { cout << "LinuxMenu\n"; }
};

/* konkretan proizvod B1 */
class WindowsDugme : public ElementUI {
public:
   void nacrtaj() { cout << "WindowsDugme\n"; }
};

/* konkretan proizvod B2 */
class WindowsMenu : public ElementUI {
public:
   void nacrtaj() { cout << "WindowsMenu\n"; }
};

/* apstraktna fabrika */
class Factory {
public:
   virtual ElementUI* napraviDugme() = 0;
   virtual ElementUI* napraviMenu() = 0;
};

/* konkretna fabrika A, za konkretne proizvode A1 i A2 */
class LinuxFactory : public Factory {
public:
   ElementUI* napraviDugme() {
      return new LinuxDugme; }
   ElementUI* napraviMenu()   {
      return new LinuxMenu; }
};

/* konkretna fabrika B, za konkretne proizvode B1 i B2 */
class WindowsFactory : public Factory {
public:
   ElementUI* napraviDugme() {
      return new WindowsDugme; }
   ElementUI* napraviMenu()   {
      return new WindowsMenu; }
};

Factory* factory;

void prikaziProzorA() {
   ElementUI* w[] = {
       factory->napraviMenu(),
       factory->napraviDugme(),
       factory->napraviDugme()};
   w[0]->nacrtaj();
   w[1]->nacrtaj();
   w[2]->nacrtaj();
}

void prikaziProzorB() {
   ElementUI* w[] = {
       factory->napraviMenu(),
       factory->napraviDugme()};
   w[0]->nacrtaj();
   w[1]->nacrtaj();
}

int main() {
#ifdef LINUX_OS
   factory = new LinuxFactory;
#else // WINDOWS_OS
   factory = new WindowsFactory;
#endif

   ElementUI* w = factory->napraviDugme();
   w->nacrtaj();
   prikaziProzorA();
   prikaziProzorB();
}
