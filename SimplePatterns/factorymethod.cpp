#include "factorymethod.h"

#include <iostream>
using namespace std;

string NalivPeroZlatno::Pisi() {
	return "Zlatnim vrhom";
}

string NalivPeroCelicno::Pisi() {
	return "Celicnim vrhom";
}

template <typename T>
template <typename Izveden>
void Fabrika<T>::registrujTip(int IDTipa) {
	/* Staticka provera (u toku kompajliranja da li je
	Tizveden zaista izveden iz T samo u C++11 */
	static_assert(std::is_base_of<T, Izveden>::value,
		"TIzveden nije izveden iz tipa T");

	fabrickiMetod[IDTipa] = &FabrickiMetod<Izveden>;
}

template <typename T>
T* Fabrika<T>::napravi(int IDTipa) {
	if (fabrickiMetod[IDTipa] != nullptr)
		/* Poziv fabricke metode preko pointera na fabricku metodu nizFabMetoda[IDTipa] */
		return fabrickiMetod[IDTipa]();
	return nullptr;
}

template <typename T>
template <typename Izveden>
T* Fabrika<T>::FabrickiMetod() {
	return new Izveden();
}

void factorymethod_test() {
	Fabrika<INalivPero> fabrika;
	fabrika.registrujTip<NalivPeroZlatno>(0);
	fabrika.registrujTip<NalivPeroCelicno>(1);

	// ovo naravno puca:
	// fabrika.registrujTip<bool>(2);

	INalivPero *prvo = fabrika.napravi(0);
	INalivPero *drugo = fabrika.napravi(1);

	cout << prvo->Pisi() << endl;
	cout << drugo->Pisi() << endl;
}
