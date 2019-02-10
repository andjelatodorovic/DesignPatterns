#include <vector>
#include <iostream>

using namespace std;

class CShapeCircle;
class CShapeSquare;
class CShapeTriangle;
/* pomocna klasa */
class CPoint {
public:
    CPoint(double x = 0.0, double y = 0.0): m_x(x), m_y(y) {}
    double  m_x;
    double  m_y;
};
/* apstraktni posetilac / visitor */
class IShapeVisitor {
public:
    virtual void Visit(CShapeCircle& circle) = 0;
    virtual void Visit(CShapeSquare& square) = 0;
    virtual void Visit(CShapeTriangle& triangle) = 0;
};
/* apstraktni element / element */
class IShape {
public:
    virtual void Accept(IShapeVisitor& visitor) = 0;
};
/* konkretni element / concrete element */
class CShapeCircle: public IShape {
public:
    CShapeCircle(double x = 0.0, double y = 0.0, double r = 0.0): m_x(x), m_y(y), m_r(r) {}
    virtual void Accept(IShapeVisitor& visitor) { visitor.Visit(*this); }
public:
    double  m_x;
    double  m_y;
    double  m_r;
};
/* konkretni element / concrete element */
class CShapeSquare: public IShape {
public:
    CShapeSquare(double x = 0.0, double y = 0.0, double width = 0.0): m_x(x), m_y(y), m_width(width) {}
    virtual void Accept(IShapeVisitor& visitor) { visitor.Visit(*this); }
public:
    double  m_x;
    double  m_y;
    double  m_width;
};
/* konkretni element / concrete element */
class CShapeTriangle: public IShape {
public:
    CShapeTriangle(CPoint a = CPoint(), CPoint b = CPoint(), CPoint c = CPoint()): m_a(a), m_b(b), m_c(c) {}
    virtual void Accept(IShapeVisitor& visitor) { visitor.Visit(*this); }
public:
    CPoint  m_a;
    CPoint  m_b;
    CPoint  m_c;
};
/* kolekcija objekata / object structure */
class CModel {
public:
    typedef vector<IShape*>::iterator ShapeIter;

    virtual ~CModel() {
        for (ShapeIter it = m_shapes.begin(); it != m_shapes.end(); ++it) {
            delete (*it);
        }
        m_shapes.clear();
    }
    virtual void AddShape(IShape* shape) { m_shapes.push_back(shape); }
    virtual void Accept(IShapeVisitor& visitor) {
        for (ShapeIter it = m_shapes.begin(); it != m_shapes.end(); ++it) {
            (*it)->Accept(visitor);
        }
    }
protected:
    vector<IShape*> m_shapes;
};
/* konkretni posetilac / concrete visitor
   predstavlja operaciju crtanja oblika */
class CDrawShapeVisitor: public IShapeVisitor {
public:
    virtual void Visit(CShapeSquare& square) {
        cout << "Drawing Square" << endl;
        cout << "\tdrawing line (" << square.m_x << ", " << square.m_y << ") - (" << (square.m_x + square.m_width) << ", " << square.m_y << ")" << endl;
        cout << "\tdrawing line (" << (square.m_x + square.m_width) << ", " << square.m_y << ") - (" << (square.m_x + square.m_width) << ", " << (square.m_y + square.m_width) << ")" << endl;
        cout << "\tdrawing line (" << (square.m_x + square.m_width) << ", " << (square.m_y + square.m_width) << ") - (" << square.m_x << ", " << (square.m_y + square.m_width) << ")" << endl;
        cout << "\tdrawing line (" << square.m_x << ", " << (square.m_y + square.m_width) << ") - (" << square.m_x << ", " << square.m_y << ")" << endl;
    }
    virtual void Visit(CShapeCircle& circle) {
        cout << "Drawing Circle" << endl;
        cout << "\tdrawing circle center at (" << circle.m_x << ", " << circle.m_y << ") with radius " << circle.m_r << endl;
    }
    virtual void Visit(CShapeTriangle& triangle) {
        cout << "Drawing Triangle" << endl;
        cout << "\tdrawing line (" << triangle.m_a.m_x << ", " << triangle.m_a.m_y << ") - (" << triangle.m_b.m_x << ", " << triangle.m_b.m_y << ")" << endl;
        cout << "\tdrawing line (" << triangle.m_b.m_x << ", " << triangle.m_b.m_y << ") - (" << triangle.m_c.m_x << ", " << triangle.m_c.m_y << ")" << endl;
        cout << "\tdrawing line (" << triangle.m_c.m_x << ", " << triangle.m_c.m_y << ") - (" << triangle.m_a.m_x << ", " << triangle.m_a.m_y << ")" << endl;
    }
};
/* kreiramo kompoziciju oblika, dodamo razlicite konkretne oblike i pozovemo operaciju
   da se nacrta kompozicija, tako sto metodu Accept prosledimo konkretnog posetioca
   koji predstavlja operaciju crtanja oblika */
int main() {
    CModel model;
    model.AddShape(new CShapeSquare(0.5, 0.5, 2.0));
    model.AddShape(new CShapeCircle(2.5, 2.5, 4.0));
    model.AddShape(new CShapeTriangle(CPoint(2.0, 3.0), CPoint(5.0, 6.0), CPoint(-4.0, 10.0)));
    CDrawShapeVisitor visitor;
    model.Accept(visitor);

    return 0;
}
