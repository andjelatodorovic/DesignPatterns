#include "Director.h"
#include "ConcreteBuilder.h"

/* koriscenje sablona, kreiramo konkretnog graditelja (concrete builder), prosledimo ga upravljacu (director)
  pomocu kojeg kreiramo prouzvod */
int main() {
    Builder *builder = new ConcreteBuilder();
    Director *director = new Director(builder);
    Product *product = director->construct();
    product->use();

    delete builder;
    delete director;
    delete product;

    return 0;
}
