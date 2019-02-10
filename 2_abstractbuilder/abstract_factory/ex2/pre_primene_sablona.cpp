/* primer iz knjige Design Patterns Explained Simply. */

/* ovo je kod bez upotrebe sablona, sa identifikatorom WINDOWS se sugerise da kod treba da se kompajlira
   za Windows OS, a sa Linux se sugerise prevodjenje za Linux. Razlika je koji tip ElementUI-a ce biti
   koriscen da li WindowsMenu/WindowsDugme ili LinuxMenu/LinuxDugme. Te varijante se kontrolisu
   svaki put putem direktiva. Imamo upotrebu direktiva na 3 mesta sto znacajno otezava debug-iranje
   kao i izmene u programu, kao i mogucnost prosirenja funkcija programa (scalability) */

// #define LINUX_OS
#define WINDOWS_OS

#include <iostream>

using namespace std;

class ElementUI {
public:
   virtual void nacrtaj() = 0;
};

class LinuxDugme : public ElementUI {
public:
   void nacrtaj() { cout << "LinuxDugme\n"; }
};
class LinuxMenu : public ElementUI {
public:
   void nacrtaj() { cout << "LinuxMenu\n"; }
};

class WindowsDugme : public ElementUI {
public:
   void nacrtaj() { cout << "WindowsDugme\n"; }
};
class WindowsMenu : public ElementUI {
public:
   void nacrtaj() { cout << "WindowsMenu\n"; }
};

void prikaziProzorA() {
#ifdef LINUX_OS
   ElementUI* w[] = {
       new LinuxMenu(),
       new LinuxDugme(),
       new LinuxDugme()};
#else // WINDOWS_OS
   ElementUI* w[] = {
       new WindowsMenu(),
       new WindowsDugme(),
       new WindowsDugme()};
#endif
   w[0]->nacrtaj();
   w[1]->nacrtaj();
   w[2]->nacrtaj();
}

void prikaziProzorB() {
#ifdef LINUX_OS
   ElementUI* w[] = {
       new LinuxMenu,
       new LinuxDugme};
#else // WINDOWS_OS
   ElementUI* w[] = {
       new WindowsMenu,
       new WindowsDugme};
#endif
   w[0]->nacrtaj();
   w[1]->nacrtaj();
}

int main() {
#ifdef LINUX_OS
   ElementUI* w = new LinuxDugme();
#else // WINDOWS_OS
   ElementUI* w = new WindowsDugme();
#endif
   w->nacrtaj();
   prikaziProzorA();
   prikaziProzorB();
}
