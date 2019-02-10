
#include "ConcreteCreator.h"
#include "Product.h"

/* testiranje kreatora koji je dizajniran sledeci sablon fabricki metod,
   pravimo konkretnog kreatora i pomocu njegovog fabrickog metoda kreiramo konkretan
   proizvod */
int main() {
    Creator *creator = new ConcreteCreator();
    Product *product = creator->factoryMethod();
    product->use();

    delete creator;
    delete product;
}
