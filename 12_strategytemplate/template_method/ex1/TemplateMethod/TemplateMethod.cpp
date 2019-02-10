#include <memory>
#include "ConcreteClass.h"

/* kreiramo instancu konkretne klase i pozovemo sablon metod/ TemplateMethod */
int main() {
    unique_ptr<AbstractClass> c(new ConcreteClass());
    c->TemplateMethod();

    return 0;
}
