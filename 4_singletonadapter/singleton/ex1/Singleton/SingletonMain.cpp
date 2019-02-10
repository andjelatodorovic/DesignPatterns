#include "Singleton.h"

/* primer koriscenja unikat / Singleton sablona */
int main() {
    Singleton* singletonInstance = Singleton::getInstance();
    singletonInstance->use();

    Singleton::getInstance()->use();
    return 0;
}
