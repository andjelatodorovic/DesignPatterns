#ifndef __LEAF_H
#define __LEAF_H

class Leaf: public Composite {
public:
    virtual ~Leaf() {}
    virtual void operation() {
        cout << "Leaf.operation()" << endl;
    }
};
#endif // __LEAF_H
