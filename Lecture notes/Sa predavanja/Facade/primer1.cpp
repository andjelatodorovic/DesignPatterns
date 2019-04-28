//
// Created by Maverick on 4/20/2017.
//

#include <iostream>
#include <math.h>

using namespace std;

class PolarnaTacka;

class DekatrovaTacka {
public:
    DekatrovaTacka(double _x, double _y) : x(_x), y(_y){}
    DekatrovaTacka(const DekatrovaTacka &other) : x(other.x), y(other.y){}

    DekatrovaTacka& pomeri (double px, double py) {
        x += px;
        y += py;
        return *this;
    }
    DekatrovaTacka& rotiraj(double theta);
    DekatrovaTacka& rotiraj(double theta, const DekatrovaTacka& centar);

    operator PolarnaTacka() const;

    double getX() const { return x; }
    double getY() const { return y; }
private:
    double x, y;
};

class PolarnaTacka {
public:
    PolarnaTacka(double _r, double _alpha): r(_r), alpha( fmod(_alpha, 360)){}
    PolarnaTacka(const PolarnaTacka &other) : r(other.r), alpha(other.alpha){}

    PolarnaTacka& rotiraj(double theta) {
        alpha = fmod(alpha + theta, 360);
        return *this;
    }
    PolarnaTacka& pomeri(double px, double py);
    operator DekatrovaTacka() const;

private:
    double r, alpha;
};

// Magija?? haahaha

PolarnaTacka& PolarnaTacka::pomeri(double px, double py) {
    return *this = DekatrovaTacka(*this).pomeri(px,py);
}

PolarnaTacka::operator DekatrovaTacka() const {
    return DekatrovaTacka(r*cos(alpha*M_PI/180), r*sin(alpha*M_PI/180) );
}

DekatrovaTacka::operator PolarnaTacka() const {
    return PolarnaTacka(sqrt(x * x + y * y),
                        atan2(y, x) * 180 / M_PI);
}
DekatrovaTacka& DekatrovaTacka::rotiraj(double theta) {
    return *this = PolarnaTacka(*this).rotiraj(theta); // KAKOOO OVO RADII ??? ;)
}

DekatrovaTacka& DekatrovaTacka::rotiraj(double theta, const DekatrovaTacka& centar){
    DekatrovaTacka tmp(x - centar.x, y - centar.y);
    tmp = PolarnaTacka(tmp).rotiraj(theta);
    x = centar.x + tmp.x; y = centar.y+tmp.y;
    return *this;
}

class Tacka {
public:
    Tacka(double x, double y):a(x,y){}
    Tacka(const Tacka& t):a(t.a){}
    Tacka(const PolarnaTacka& p):a(p){}
    void pomeri(double dx, double dy) {a.pomeri(dx,dy);}
    void rotiraj(double theta){ a.rotiraj(theta);}
    void rotiraj(double theta, const Tacka& centar){
        a.rotiraj(theta, centar.a);
    }
    double getX() const { return a.getX(); }
    double getY() const { return a.getY(); }

private:
    DekatrovaTacka a;
};

class Duz {
public:
    Duz(Tacka p, Tacka k):poc(p), kraj(k){}
    void pomeri(double dx, double dy) {
        poc.pomeri(dx, dy);
        kraj.pomeri(dx, dy);
    }
    void rotiraj(double theta) { kraj.rotiraj(theta, poc); }
    Tacka getPoc() const { return poc; }
    Tacka getKraj() const { return kraj; }

private:
    Tacka poc, kraj;
};

int main() {
    Tacka* a = new Tacka(10, 10);
    cout << a->getX() << " , " << a->getY() << endl;
    a->pomeri(5,5);
    cout << a->getX() << " , " << a->getY() << endl;
    a->rotiraj(10);
    cout << a->getX() << " , " << a->getY() << endl;
}