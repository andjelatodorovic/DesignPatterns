#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

/* adaptee/klasa koju treba da prilagodimo */
class BankovniRacun {
private:
    int brojRacuna;
public:
    BankovniRacun(int brojRacuna) {
        this->brojRacuna = brojRacuna;
    }
    void prikaziRacun() {
        cout << "Prikazujem detalje bankovnog racuna broj #" << brojRacuna << endl;
    }
};

/* target / apstraktna klasa/interfejs ZA koji treba da prilagodimo */
class ElektronskiRacun {
public:
    virtual void prikazi() = 0;
};

/* implementirani ciljani interfejs */
class HitRacun : public ElektronskiRacun {
private:
    string brojRacuna;
public:
    HitRacun(string brojRacuna) {
        this->brojRacuna = brojRacuna;
    }
    void prikazi() {
        cout << "Prikazujem detalje elektronskog Hit racuna broj #" << brojRacuna << endl;
    }
};

/* adapter koji prilagodjava klasu ciljanom interfejsu */
class BankovniRacunAdapter : private BankovniRacun, public ElektronskiRacun {
public:
    BankovniRacunAdapter(string brojRacuna) : BankovniRacun(atoi(brojRacuna.c_str())) { }

    void prikazi() {
        this->prikaziRacun();
    }
};

void prikaziRacune(vector<ElektronskiRacun*> racuni) {
    for (vector<ElektronskiRacun*>::iterator it = racuni.begin(); it != racuni.end(); it ++) {
        ElektronskiRacun* racun = *it;
        racun->prikazi();
    }
}

int main()
{
    vector<ElektronskiRacun*> racuni;
    racuni.push_back(new HitRacun("RS 123456000123"));
    racuni.push_back(new HitRacun("RS 987654003232"));
    racuni.push_back(new BankovniRacunAdapter("43332"));
    prikaziRacune(racuni);

    for (vector<ElektronskiRacun*>::iterator it = racuni.begin(); it != racuni.end(); it ++) {
        delete *it;
    }
    racuni.clear();
}
