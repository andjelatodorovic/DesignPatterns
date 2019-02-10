#ifndef __CLASS2_H
#define __CLASS2_H

#include <iostream>

/* klasa koja predstavlja neki kompleksan podsistem */
class Class2 {
public:
    virtual void do2() {
        std::cout << "Class2.do2()" << std::endl;
    }
};
#endif // __CLASS2_H
