#include "ConcreteVisitor1.h"
#include "ConcreteVisitor2.h"
#include "ObjectStructure.h"

/* kreiramo strukturu elemenata, dodamo joj dva konkretna elementa,
   kreiramo dva razlicita konkretna posetioca i prosledimo ih strukturi
   na ekranu ce biti odstampan tok izvrsavanja */
int main() {
    ObjectStructure structure;
    structure.AddElement(new ConcreteElementA());
    structure.AddElement(new ConcreteElementB());

    Visitor* v1 = new ConcreteVisitor1();
    Visitor* v2 = new ConcreteVisitor2();

    structure.Accept(*v1);
    structure.Accept(*v2);

    delete v1;
    delete v2;

    return 0;
}
