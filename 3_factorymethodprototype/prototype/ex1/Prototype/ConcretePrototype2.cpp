#include "ConcretePrototype2.h"
#include <iostream>

using namespace std;

Prototype* ConcretePrototype2::clone() {
    return new ConcretePrototype2();
}

void ConcretePrototype2::use() {
    cout << "Koristim konkretan prototip 2" << endl;
}
