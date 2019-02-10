#include <iostream>

#include "ConcreteAggregate.h"
#include "Iterator.h"

using namespace std;

/* kreiramo konkretnu kolekciju, dodamo nekoliko elemenata,
   zatim kreiramo iterator koristeci fabricki metod CreateIterator
   i onda pokazemo elegantnost koriscenja iteratora u petlji for */
int main() {
    Aggregate *v = new ConcreteAggregate();
    v->Add(2);
    v->Add(3);
    v->Add(5);

    Iterator* it;
    try {
        for (it = v->CreateIterator(); !it->IsDone(); it->Next()) {
            cout << it->CurrentItem() << endl;
        }
    } catch (const char* e) {
        cout << "ERROR: " << e << endl;
    }
    if (it != NULL) delete it;

    return 0;
}
