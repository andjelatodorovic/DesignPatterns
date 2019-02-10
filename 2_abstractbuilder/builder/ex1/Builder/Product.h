#ifndef __PRODUCT_H
#define __PRODUCT_H

#include <iostream>

using namespace std;

/* konkretan proizvod */
class Product {
private:
    int part;
public:
    void setPart(int part) { this->part = part; }
    void use() { cout << "Koristim Proizvod koji ima deo #" << part << endl ; }
};
#endif // __PRODUCT_H
