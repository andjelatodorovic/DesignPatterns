#include<iostream>
#include<string>

using namespace std;

class Pen {
public:
    Pen(const string _type) : type(_type) {};
    virtual ~Pen(){}
    Pen* clone() { return this; };
    virtual void write() {
        cout << "Debljina vrha: " << type << endl;
    }
    static Pen* create(int id) {
        Pen* tmp;
        if (tmp = pens[id]) {
            return tmp->clone();
        }
        return nullptr;
    }

    static Pen* addPrototype(int id, Pen *p) {
        pens[id] = p;
        return p;
    }
    static void destroyPrototypes() {
        for (int i = 0; i < 10; ++i) {
            delete pens[i];
        }
    }
private:
    string type;
    static Pen* pens[];
};

template <class Derived>
class ClonablePen : public Pen {
public:
    ClonablePen(const string _type): Pen(_type){}
    ClonablePen(const ClonablePen<Derived> &other) : Pen(other) {}

    Pen* clone() const {
        return new Derived(*(Derived*) this); // hahah like a pro??
    }
};

class BallPointPen : public ClonablePen<BallPointPen> {
private:
    int id;
public:
    BallPointPen(const string type, const int _id) : ClonablePen<BallPointPen>(type), id(_id){}
    BallPointPen(const ClonablePen<BallPointPen> &other) : ClonablePen<BallPointPen>(other) {}

    void write() {
        cout << "Olovka" << endl;
        cout << "TEST ID: " << id << endl;
        Pen::write();
    }
};

class FountainPen : public ClonablePen<FountainPen> {
private:
    int id;
public:
    FountainPen(const string type, const int _id) : ClonablePen<FountainPen>(type), id(_id) {}
    FountainPen(const ClonablePen<FountainPen> &other) : ClonablePen<FountainPen>(other) {}

    void write() {
        cout << "Naliv pero" << endl;
        cout << "TEST ID: " << id << endl;
        Pen::write();
    }
};

Pen* Pen::pens[10];

int main() {
    Pen::addPrototype(1, new FountainPen("0.7", 10));
    Pen::addPrototype(2, new BallPointPen("1.2",15));

    Pen* ptrPen = Pen::create(1);
    ptrPen->write();

    ptrPen = Pen::create(2);
    ptrPen->write();

    Pen::destroyPrototypes();
}