#ifndef __ABSTRACTCLASS_H
#define __ABSTRACTCLASS_H

#include <iostream>

using namespace std;

/* apstraktna klasa koja poseduje neki sablonski metod / template method
   u nasem slucaju to je TemplateMethod
   u apstraktnoj klasi data je implementacija ovog metoda koristeci virtuelne metode
   PrimitiveOperation1/2 koji nisu implementirani,
   izvedene klase od AbstractClass treba da daju implementacije metoda PrimitiveOperation1/2
   ali ne menjajuci korake u TemplateMethod,
   na taj nacin konkretne klase mogu da daju odgovarajuce izmene ovih primitivnih operacija,
   razlika u odnosu na strategija obrazac je sto kod sablon metoda mozemo da vrsimo
   izmenu finijih delova implementacije, dok kod strategije kod konkretnih strategija
   moramo da dajemo implementacije celog metoda */
class AbstractClass {
public:
    virtual void TemplateMethod() {
        cout << "AbstractClass.TemplateMethod()" << endl;
        PrimitiveOperation1();
        PrimitiveOperation2();
    }
    virtual void PrimitiveOperation1() = 0;
    virtual void PrimitiveOperation2() = 0;
};
#endif // __ABSTRACTCLASS_H
