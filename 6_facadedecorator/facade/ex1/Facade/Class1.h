#ifndef __CLASS1_H
#define __CLASS1_H

#include <iostream>

/* klasa koja predstavlja neki kompleksan podsistem */
class Class1 {
public:
    virtual void do1() {
        std::cout << "Class1.do1()" << std::endl;
    }
};
#endif // __CLASS1_H
