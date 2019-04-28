//
// Created by Maverick on 4/24/2017.
//

#include <iostream>
#include <list>
#include <algorithm> // find
#include <string>

using namespace std;

class Posmatrani;

class IPosmatrac {
public:
    virtual ~IPosmatrac() {}
    virtual void obavesti(Posmatrani*) = 0;
};

class Posmatrani {
public:
    virtual ~Posmatrani() {}
    bool dodajPosmatraca(IPosmatrac* ptrPosmatrac) {
        list<IPosmatrac*>::iterator it = find(posmatraci.begin(), posmatraci.end(), ptrPosmatrac);
        if (it != posmatraci.end())
            return false;
        posmatraci.push_back(ptrPosmatrac);
        return true;
    }
    bool uknloniPosmatraca(IPosmatrac* ptrPosmatrac) {
        list<IPosmatrac*>::iterator it = find(posmatraci.begin(), posmatraci.end(), ptrPosmatrac);
        if (it == posmatraci.end())
            return false;
        posmatraci.erase(it);
        return true;
    }
    void alarm() {
        list<IPosmatrac*>::iterator it;

        for (it = posmatraci.begin(); it != posmatraci.end(); ++it) {
            (*it)->obavesti(this);
        }
    }
    virtual string getStatus() const = 0;
private:
    list<IPosmatrac*> posmatraci;

};

class Nakit : public Posmatrani {
public:
    Nakit() : status("Sigurno") {}
    virtual ~Nakit() {}
    void kradja() { status = "KRADJAA"; }
    string getStatus() const { return status; }
private:
    string status;
};

class SigurnosnaVrata : public IPosmatrac {
public:
    SigurnosnaVrata() : status("OTVORENA") {}
    virtual ~SigurnosnaVrata() {}

    void print() const {
        cout << "Vrata: " << status << endl;
    }

    virtual void obavesti(Posmatrani *ptrPosmatrani) {
        if (ptrPosmatrani->getStatus() == "Sigurno")
            status = "OTVORENA";
        else
            status = "ZATVORENA";
        print();
    }

private:
    string status;
};

class Cuvar : public IPosmatrac {
public:
    Cuvar(string ime) : m_ime(ime), m_status("CUVA OBJEKAT") {}
    virtual ~Cuvar() {}

    void print() const {
        cout << "Cuvar: " << m_ime << " " << m_status << endl;
    }
    virtual void obavesti(Posmatrani *ptrPosmatrani) {
        if (ptrPosmatrani->getStatus() == "Sigurno")
            m_status = "CUVA OBJEKAT";
        else
            m_status = "JURI ULJEZA";
        print();
    }

private:
    string m_ime, m_status;
};

int main() {
    Cuvar* cuvar1 = new Cuvar("Miki Mikic");
    Cuvar* cuvar2 = new Cuvar("Marko Ilic");
    SigurnosnaVrata* vrata1 = new SigurnosnaVrata();
    Nakit* nakit = new Nakit();

    nakit->dodajPosmatraca(cuvar1);
    nakit->dodajPosmatraca(cuvar2);
    nakit->dodajPosmatraca(vrata1);

    nakit->alarm();
    nakit->kradja();
    nakit->alarm();

}