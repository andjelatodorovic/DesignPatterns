#ifndef __VISITOR_H
#define __VISITOR_H

class ConcreteElementA;
class ConcreteElementB;

/* apstraktni posetilac / visitor
   nudi virtuelne metode da "poseti" konkretne elemente A i B,
   u sustini ti metodi, implementirani kasnije u konkrentim posetiocima,
   ne vrse nikakvo "posecivanje" tih konkretnih elemenata, vec im
   daju nove operacije,
   umesto da nove operacije budu dodane u hijerarhije elemenata koje nasledjuju
   apstraktnu klasu element i implementirane u svakoj nasledjenoj klasi
   mi nove operacije toj hijerarhiji mozemo ovako spolja/eksterno da dodelimo
   koristeci obrazac posetioc/visitor
   svaka ta nova operacije je koncepcijski objedinjena u jednom konkretnom posetiocu
   ovaj obrazac je koristan kada je hijerarhija objekata/elemenata stabila i nema
   prosirivanja a imamo slucaj da se cesto dodaju nove operacije
   kada se dodaje novi element u hijerarhiju klasa onda svi posetioci moraju da
   implementiraju novi metod za taj prirodani konkretan element */
class Visitor {
public:
    virtual ~Visitor() {}
    virtual void VisitConcreteElementA(ConcreteElementA& element) = 0;
    virtual void VisitConcreteElementB(ConcreteElementB& element) = 0;
};

#endif // __VISITOR_H
