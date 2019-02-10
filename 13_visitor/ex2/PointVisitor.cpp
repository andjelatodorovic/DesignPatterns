#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define SQR(x) ((x) * (x))

class CPoint2D;
class CPoint3D;

/* posetilac / visitor
   iako su metodi istog naziva C++ nam omogucava da ce biti pozvan
   metod koji odgovara konkretnom tipu prosledjenog parametra */
class IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) = 0;
    virtual void Visit(CPoint3D& point) = 0;
};
/* apstraktni element / element */
class IPoint {
public:
    IPoint(): m_norm(0.0) {}
    virtual double GetNorm() { return m_norm; }
    virtual void SetNorm(double norm) { m_norm = norm; }
    virtual void Accept(IPointVisitor& visitor) = 0;
private:
    double  m_norm;
};
/* konkretan element / concrete element */
class CPoint2D: public IPoint {
public:
    CPoint2D(double x = 0.0, double y = 0.0): m_x(x), m_y(y) {}
    virtual void Accept(IPointVisitor& visitor) {
        visitor.Visit(*this);
    }
    virtual double GetX() { return m_x; }
    virtual void SetX(double x) { m_x = x; }
    virtual double GetY() { return m_y; }
    virtual void SetY(double y) { m_y = y; }
private:
    double  m_x;
    double  m_y;
};
/* konkretan element / concrete element */
class CPoint3D: public IPoint {
public:
    CPoint3D(double x = 0.0, double y = 0.0, double z = 0.0): m_x(x), m_y(y), m_z(z) {}
    virtual void Accept(IPointVisitor& visitor) { visitor.Visit(*this); }
    virtual double GetX() { return m_x; }
    virtual void SetX(double x) { m_x = x; }
    virtual double GetY() { return m_y; }
    virtual void SetY(double y) { m_y = y; }
    virtual double GetZ() { return m_z; }
    virtual void SetZ(double z) { m_z = z; }
private:
    double  m_x;
    double  m_y;
    double  m_z;
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju koja racuna normu L1 na elementima */
class CPointNormL1Visitor: public IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) {
        point.SetNorm(ABS(point.GetX()) + ABS(point.GetY()));
    }
    virtual void Visit(CPoint3D& point) {
        point.SetNorm(ABS(point.GetX()) + ABS(point.GetY()) + ABS(point.GetZ()));
    }
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju koja racuna normu L2 na elementima */
class CPointNormL2Visitor: public IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) {
        point.SetNorm(sqrt(SQR(point.GetX()) + SQR(point.GetY())));
    }
    virtual void Visit(CPoint3D& point) {
        point.SetNorm(sqrt(SQR(point.GetX()) + SQR(point.GetY()) + SQR(point.GetZ())));
    }
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju koja racuna normu L inf na elementima */
class CPointNormLinfVisitor: public IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) {
        point.SetNorm(MAX(ABS(point.GetX()), ABS(point.GetY())));
    }
    virtual void Visit(CPoint3D& point) {
        point.SetNorm(MAX(MAX(ABS(point.GetX()), ABS(point.GetY())), ABS(point.GetZ())));
    }
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju koja translira elemente
   u ovom slucaju operacija ima parametre (smer translacije) i parametre
   cemo da prosledjujemo putem atributa konkretnog posetioca, u ovom slucaju m_transX, m_transY i m_transZ */
class CPointTranslateVisitor: public IPointVisitor {
public:
    CPointTranslateVisitor(double transX = 0.0, double transY = 0.0, double transZ = 0.0)
        : m_transX(transX), m_transY(transY), m_transZ(transZ) {}
    virtual void Visit(CPoint2D& point) {
        point.SetX(point.GetX() + m_transX);
        point.SetY(point.GetY() + m_transY);
    }
    virtual void Visit(CPoint3D& point) {
        point.SetX(point.GetX() + m_transX);
        point.SetY(point.GetY() + m_transY);
        point.SetZ(point.GetZ() + m_transZ);
    }
protected:
    double  m_transX;
    double  m_transY;
    double  m_transZ;
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju kojom se prikazuju norme tacaka */
class CPointDisplayNormVisitor: public IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) {
        cout << "norm [" << point.GetX() << ", " << point.GetY() << "] = " << point.GetNorm() << endl;
    }
    virtual void Visit(CPoint3D& point) {
        cout << "norm [" << point.GetX() << ", " << point.GetY() << ", " << point.GetZ() << "] = " << point.GetNorm() << endl;
    }
};
/* konkretan posetilac / concrete visitor
   predstavlja operaciju kojom se prikazuju tacke */
class CPointDisplayVisitor: public IPointVisitor {
public:
    virtual void Visit(CPoint2D& point) {
        cout << "(" << point.GetX() << ", " << point.GetY() << ")" << endl;
    }
    virtual void Visit(CPoint3D& point) {
        cout << "(" << point.GetX() << ", " << point.GetY() << ", " << point.GetZ() << ")" << endl;
    }
};
/* kolekcija elemenata / object structure
   predstavlja kompoziciju vise tacaka */
class CPointsCollection {
public:
    typedef vector<IPoint*>::iterator PointsIter;

    virtual ~CPointsCollection() {
        for (PointsIter it = m_points.begin(); it != m_points.end(); ++it) {
            delete *it;
        }
        m_points.clear();
    }
    virtual void AddPoint(IPoint* point) { m_points.push_back(point); }
    virtual void Accept(IPointVisitor& visitor) {
        for (PointsIter it = m_points.begin(); it != m_points.end(); ++it) {
            (*it)->Accept(visitor);
        }
    }
protected:
    vector<IPoint*> m_points;
};
/* kreiramo kolekciju tacaka, dodamo nekoliko razlicitih konkretnih tacaka i pozovemo
   razlicite operaciju putem prosledjivanja konkretnih posetioca metodu Accept na strukturi */
int main() {
    CPointsCollection points;
    points.AddPoint(new CPoint2D(1.0, 2.0));
    points.AddPoint(new CPoint3D(0.5, 1.5, -4.0));
    points.AddPoint(new CPoint2D(1.0, 2.0));
    points.AddPoint(new CPoint3D(1.5, -2.5, 2.0));
    points.AddPoint(new CPoint2D(-3.0, -1.0));
    points.AddPoint(new CPoint3D(-0.5, -1.5, 2.0));

    CPointDisplayVisitor pointDisplayVisitor;
    points.Accept(pointDisplayVisitor);

    CPointNormL1Visitor pointNormL1Visitor;
    points.Accept(pointNormL1Visitor);

    CPointDisplayNormVisitor pointDisplayNormVisitor;
    points.Accept(pointDisplayNormVisitor);

    CPointNormL2Visitor pointNormL2Visitor;
    points.Accept(pointNormL2Visitor);

    points.Accept(pointDisplayNormVisitor);

    points.Accept(pointDisplayVisitor);
    CPointTranslateVisitor pointTranslateVisitor(1.0, -2.0, 3.0);
    points.Accept(pointTranslateVisitor);
    points.Accept(pointDisplayVisitor);

    return 0;
}
