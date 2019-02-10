#include <iostream>

using namespace std;

/* konkretan proizvod */
class Pica {
private:
    int velicina;
    int kecap;
    int sir;
    int papricice;
    int sunka;
public:
    Pica() {
        velicina = 10;
        kecap = 0;
        sir = 0;
        sunka = 0;
        papricice = 0;
    }
    int dajVelicinu() { return this->velicina; }
    void staviVelicinu(int velicina) { this->velicina = velicina; }
    int dajKecap() { return this->kecap; }
    void staviKecap(int kecap) { this->kecap = kecap; }
    int dajSir() { return this->sir; }
    void staviSir(int sir) { this->sunka = sunka; }
    int dajSunku() { return this->sunka; }
    void staviSunku(int sunka) { this->sunka = sunka; }
    int dajPapricice() { return this->papricice; }
    void staviPapricice(int papricice) { this->papricice = papricice; }
    void prikazi() {
        cout << "Pica: velicina(" << velicina << "), kecap(" << kecap << "), " ;
        cout << "sir(" << sir << "), sunka(" << sunka << "), papricice(" << papricice << ")" << endl;
    }
};

/* apstraktan graditelj */
class PicaGraditelj {
public:
    virtual PicaGraditelj* staviVelicinu(int velicina) = 0;
    virtual PicaGraditelj* staviSir(int sir) = 0;
    virtual PicaGraditelj* staviKecap(int kecap) = 0;
    virtual PicaGraditelj* staviSunku(int sunka) = 0;
    virtual PicaGraditelj* staviPapricice(int papricice) = 0;
    virtual Pica* napraviPicu() = 0;
};

/* konkretan graditelj */
class PicaMargeritaGraditelj: public PicaGraditelj {
private:
    Pica *pica;
public:
    PicaMargeritaGraditelj() {
        pica = new Pica();
    }
    ~PicaMargeritaGraditelj() {
        delete pica;
    }
    PicaGraditelj* staviVelicinu(int velicina) {
        pica->staviVelicinu(velicina);
        return (PicaGraditelj*) this;
    }
    PicaGraditelj* staviSir(int sir) {
        pica->staviSir(sir);
        return (PicaGraditelj*) this;
    }
    PicaGraditelj* staviKecap(int kecap) {
        pica->staviKecap(kecap);
        return (PicaGraditelj*) this;
    }
    PicaGraditelj* staviSunku(int sunka) {
        pica->staviSunku(sunka);
        return (PicaGraditelj*) this;
    }
    PicaGraditelj* staviPapricice(int papricice) {
        pica->staviPapricice(papricice);
        return (PicaGraditelj*) this;
    }

    Pica* napraviPicu() {
        return pica;
    }
};

/* upravljac / director, koristi konkretnog graditelja (koji u ovom slucaju nije prosledjen preko
  kontruktora) da bi napravio konkretan proizvod */
class PicerijaMargerita {
public:
    PicerijaMargerita() { }
    Pica *napraviPicu() {
        PicaGraditelj *picaGraditelj = new PicaMargeritaGraditelj();
        picaGraditelj->staviKecap(5)->staviSir(7)->staviSunku(8);
        return picaGraditelj->napraviPicu();

    }
};

/* kreiramo upravljaca i trazimo mu da nam kreira proizvod */
int main() {
    PicerijaMargerita *picerija = new PicerijaMargerita();
    Pica *pica = picerija->napraviPicu();
    pica->prikazi();

    PicaMargeritaGraditelj* graditelj = new PicaMargeritaGraditelj;

    graditelj->staviKecap(50)->staviPapricice(5);

    return 0;
}
