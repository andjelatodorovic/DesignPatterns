//
// Created by Maverick on 4/21/2017.
//

#include <iostream>

using namespace std;

class IKomanda {
public:
    virtual void izvrsi() = 0;
    virtual void otkaziIzvrseno() = 0;
    virtual void ponovoIzvrsi() = 0;
};

class TV {
public:
    TV(){}
    void ukljuci() { ukljucen = true; }
    void iskljuci() { ukljucen = false; }
    void promeniKanal(unsigned kanal) { this->kanal = kanal; }

    bool getStatus() const { return ukljucen; }
    unsigned getKanal() const { return kanal; }
private:
    bool ukljucen;
    unsigned kanal;
};

class KomandaUkljuciTV : public IKomanda {
public:
    KomandaUkljuciTV(TV* tv) : ptrTV(tv) {}
    void izvrsi() { ptrTV->ukljuci(); }
    void otkaziIzvrseno() { ptrTV->iskljuci(); }
    void ponovoIzvrsi() { ptrTV->ukljuci(); }
private:
    TV* ptrTV;
};

class KomandaIskljuciTV : public IKomanda {
public:
public:
    KomandaIskljuciTV(TV* tv) : ptrTV(tv) {}
    void izvrsi() { ptrTV->iskljuci(); }
    void otkaziIzvrseno() { ptrTV->ukljuci(); }
    void ponovoIzvrsi() { ptrTV->iskljuci(); }
private:
    TV* ptrTV;
};

class KomandaPromeniKanal : public IKomanda {
public:
    KomandaPromeniKanal(TV* tv, unsigned kanal) : ptrTV(tv), noviKanal(kanal){}
    void izvrsi() {
        stariKanal = ptrTV->getKanal();
        ptrTV->promeniKanal(noviKanal);
    }
    void otkaziIzvrseno()
private:
    TV* ptrTV;
    unsigned stariKanal, noviKanal;
};