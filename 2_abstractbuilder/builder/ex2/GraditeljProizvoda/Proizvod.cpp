#include "Proizvod.h"

#include <iostream>

using namespace std;

void Proizvod::prikazi() {
	cout << "<SASTAV PROIZVODA>" << endl;
	cout << "\tintSvojstvo: " << this->intSvojstvo << endl;
	cout << "\tfloatSvojstvo: " << this->floatSvojstvo << endl;
	cout << "\tcharSvojstvo: " << this->charSvojstvo << endl;
}

void Proizvod::uradiNesto() {
    cout << "Proizvod > Radim nesto..." << endl;
}

void Proizvod::uradiNestoDrugo() {
    cout << "Proizvod > Radim nesto drugo..." << endl;
}
