#ifndef __CLASS3_H
#define __CLASS3_H

#include <iostream>

/* klasa koja predstavlja neki kompleksan podsistem */
class Class3 {
public:
    virtual void do3() {
        std::cout << "Class3.do3()" << std::endl;
    }
};
#endif // __CLASS3_H
