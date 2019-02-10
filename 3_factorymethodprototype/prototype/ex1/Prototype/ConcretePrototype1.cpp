#include "ConcretePrototype1.h"
#include <iostream>

using namespace std;

Prototype* ConcretePrototype1::clone() {
    return new ConcretePrototype1();
}

void ConcretePrototype1::use() {
    cout << "Koristim konkretan prototip 1" << endl;
}
