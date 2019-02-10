#ifndef __FLYWEIGHT_H
#define __FLYWEIGHT_H

/* apstraktna klasa za Flyweight/muva objekte
   svaki objekat tog tipa ima unustrasnje (instrinsic) stanje koje ne zavisi od konteksta (okruzenja)
   u kome se objekat nalazi, i spoljasnje (extrinsic) koje zavisi od konteksta (okruzenja) u kome se objekat koristi
   u nasem slucaju spoljasnje stanje prosledjujemo preko parametara extrinsicState metoda Operation */
class Flyweight {
public:
    virtual ~Flyweight() {}
    virtual void Operation(const string& extrinsicState) = 0;
    virtual string GetIntrinsicState() { return m_intrinsicState; }
protected:
    Flyweight(string intrinsicState) : m_intrinsicState(intrinsicState) { }
private:
    string  m_intrinsicState;
};

#endif // __FLYWEIGHT_H
