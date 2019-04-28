//
// Created by Maverick on 4/20/2017.
//
#include <iostream>
#include <list>

using namespace std;

class BiblElement {
public:
    BiblElement(unsigned b = 0): br_kopija(b) {}
    void setBrKopija(unsigned b) { br_kopija = b; }
    unsigned getBrKopija() { return br_kopija; }
    virtual void info() = 0;
private:
    unsigned br_kopija;
};

class Knjiga : public BiblElement {
public:
    Knjiga(string _naslov, string _autor, unsigned _kopije): BiblElement(_kopije), autor(_autor), naslov(_naslov){}
    void info() {
        cout << endl << "----- Knjiga -----" << endl;
        cout << "Autor :    " << autor << endl;
        cout << "Naslov :   " << naslov << endl;
        cout << "Kopije :   " << getBrKopija() << endl;
    };
private:
    Knjiga();
    string naslov;
    string autor;
};

class Video : public BiblElement {
public:
    Video(string _naslov, string _reziser, unsigned _trajanje, unsigned _kopije): BiblElement(_kopije), reziser(_reziser), naslov(_naslov), trajanje(_trajanje){}
    void info() {
        cout << endl << "----- Film -----" << endl;
        cout << "Reziser :  " << reziser << endl;
        cout << "Naslov :   " << naslov << endl;
        cout << "Trajanje:  " << trajanje << endl;
        cout << "Kopije :   " << getBrKopija() << endl;
    };
private:
    Video();
    string naslov;
    string reziser;
    unsigned trajanje;
};

class Dekorater : public  BiblElement {
public:
    Dekorater(BiblElement* ptr) : ptrBibl(ptr) {}
    void info() { ptrBibl->info(); }
    void setBrKopija(unsigned b) const { ptrBibl->setBrKopija(b); }
    unsigned getBrKopija() const { return ptrBibl->getBrKopija(); }

protected:
    BiblElement* ptrBibl;
private:
    Dekorater();
};

class ZaIzdavanje : public Dekorater {
public:
    ZaIzdavanje(BiblElement* ptr) : Dekorater(ptr){}

    void pozajmi(string name) {
        unsigned br_kopija = ptrBibl->getBrKopija();
        if(br_kopija > 0) {
            pozajmljivaci.push_back(name);
            ptrBibl->setBrKopija(--br_kopija);
        }
    }

    void vrati(string name) {
        list<string>::iterator it = pozajmljivaci.begin();
        bool nadjen = false;
        while(it != pozajmljivaci.end() && nadjen == false) {
            if(*it == name) {
                pozajmljivaci.erase(it);
                nadjen = true;
            }
            ++it;
        }
        if(nadjen) {
            ptrBibl->setBrKopija(ptrBibl->getBrKopija() + 1);
            cout << endl << name << " se uspesno razduzio" << endl;
        } else {
            cout << endl << name << "' nije se nije zaduzivao" << endl;
        }
    }

    void info() {
        Dekorater::info();
        cout << "Broj pozajmenjih kopija: " << pozajmljivaci.size() << endl;

        list<string>::iterator it = pozajmljivaci.begin();
        while(it != pozajmljivaci.end()) {
            cout << "Korisnik: " << *it << endl;
            ++it;
        }
    }

private:
    list<string> pozajmljivaci;
};

int main() {
    Knjiga* htmlcss = new Knjiga("Html & CSS", "Jon Duckett", 2);
    Video* deadpool = new Video("DeadPool", "Tim Miller", 108, 2);

    htmlcss->info();
    //deadpool->info();

    ZaIzdavanje* vKDP = new ZaIzdavanje(deadpool);
    ZaIzdavanje* vKHC = new ZaIzdavanje(htmlcss);

    vKHC->pozajmi("Katarina Zejnulov");
    vKHC->pozajmi("Marko Ilic");
    vKHC->info();

    vKHC->vrati("Pera Peric");
    vKHC->vrati("Marko Ilic");
    vKHC->info();

}
