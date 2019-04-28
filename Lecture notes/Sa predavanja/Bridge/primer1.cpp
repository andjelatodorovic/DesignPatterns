//
// Created by Maverick on 4/18/2017.
//

#include <iostream>

using namespace std;

struct Implementator {
    virtual void crtajPortret(double, double) = 0;
    virtual ~Implementator() {}
};

struct DaVinci : public Implementator {
    void crtajPortret(double v, double s) {
        cout << "DaVinci portert [" << v << " x " << s << "]" << endl;
    }
};

struct Pikaso : public Implementator {
    void crtajPortret(double v, double s) {
        cout << "Pikaso portert [" << v << " x " << s << "]" << endl;
    }
};

struct Slika {
    virtual void crtaj() = 0;
    virtual void promeniVelicinu(double, double) = 0;
    virtual ~Slika() {}
};

class Portret : public Slika {
public:
    Portret(double v, double s, Implementator* _um) : visina(v), sirina(s), umetnik(_um) {}
    virtual ~Portret() {}
    void crtaj() {
        umetnik->crtajPortret(visina, sirina);
    }
    void promeniVelicinu(double v, double s) {
        visina = v;
        sirina = s;
    }
private:
    double visina;
    double sirina;
    Implementator* umetnik;
};

int main() {
    DaVinci* Leonardno = new DaVinci();
    Pikaso* Pablo = new Pikaso();

    Portret* monaliza = new Portret(5, 8, Leonardno);
    Portret* gitarista = new Portret(3, 7, Pablo);

    monaliza->crtaj();
    gitarista->crtaj();
}

