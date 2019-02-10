#include "Composite.h"
#include "Leaf.h"

int main() {
    Composite *root = new Composite();
    Composite *leftChild = new Composite();
    Leaf *rightChild = new Leaf();
    Leaf *leftLeftChild = new Leaf();
    Leaf *leftRightChild = new Leaf();
    leftChild->add(leftLeftChild);
    leftChild->add(leftRightChild);
    root->add(leftChild);
    root->add(rightChild);
    /* kada pozovemo opereciju rekurzivno ce biti pozvana operacija na svim potkomponentama */
    root->operation();

    cout << "removing left child" << endl;
    root->remove(leftChild);
    root->operation();

    /* u ovom slucaju cemo mi rucno da eliminisemo sve komponente koje smo kreirali,
       ovaj kod ce da prijavljuje gresku ukoliko imamo destruktora za Composite koji
       unistava i potkomponente/decu, u tom slucaju dovoljno je unistiti samo koren
       svake od slozenih komponenti */
    delete root;
    delete leftChild;
    delete rightChild;
    delete leftLeftChild;
    delete leftRightChild;

    return 0;
}
