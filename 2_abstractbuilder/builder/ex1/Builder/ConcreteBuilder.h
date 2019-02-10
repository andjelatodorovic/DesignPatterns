#ifndef __CONCRETE_BUILDER_H
#define __CONCRETE_BUILDER_H

/* konkretan graditelj / concrete builder, ima mogucnost da konstruise proizvod deo po deo */
class ConcreteBuilder: public Builder {
private:
    Product *product;
public:
    ConcreteBuilder() {
        product = new Product();
    }
    void buildPart() {
        product->setPart(5);
    }
    Product *getProduct() {
        return product;
    }
};
#endif // __CONCRETE_BUILDER_H

