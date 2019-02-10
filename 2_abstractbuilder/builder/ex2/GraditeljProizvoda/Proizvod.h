#ifndef __PROIZVOD_H
#define __PROIZVOD_H

/* konkretan proizvod */
class Proizvod {
private:
    /* interna svojstva proizvoda, npr. delovi proizvoda */
    int intSvojstvo;
    float floatSvojstvo;
    char charSvojstvo;
public:
    /* konstruktor proizvoda */
    Proizvod() {}
    Proizvod(const int intSvojstvo, const float floatSvojstvo, const char charSvojstvo) :
        intSvojstvo(intSvojstvo),
        floatSvojstvo(floatSvojstvo),
        charSvojstvo(charSvojstvo) {}
    void postaviIntSvojstvo(int intSvojstvo) { this->intSvojstvo = intSvojstvo; }
    void postaviFloatSvojstvo(float floatSvojstvo) { this->floatSvojstvo = floatSvojstvo; }
    void postaviCharSvojstvo(char charSvojstvo) { this->charSvojstvo = charSvojstvo; }
    void prikazi();
    void uradiNesto();
    void uradiNestoDrugo();
};



#endif // __PROIZVOD_H
