#include <iostream>
#include <cstdlib>

using namespace std;

/* singleton sablon, jedinstven primerak kreiramo putem loklane staticke promenljive unutar
    funkcije dajPrimerak */
class UpravljacStampaca {
public:
    static UpravljacStampaca& dajPrimerak() {
        static UpravljacStampaca s_upravljacStampaca;
        return s_upravljacStampaca;
    }
    void stampaj() { cout << "Stampam na stampacu..." << endl; }
protected:
    UpravljacStampaca() {}
    UpravljacStampaca(const UpravljacStampaca& upravljacStampaca) {}
    UpravljacStampaca& operator=(const UpravljacStampaca& upravljacStampaca) {}
};

class UpravljacLaserskogStampaca: UpravljacStampaca {
public:
    static UpravljacStampaca& dajPrimerak() {
        static UpravljacLaserskogStampaca s_upravljacLaserskogStampaca;
        return s_upravljacLaserskogStampaca;
    }
    void stampaj() { cout << "Stampam na laserskom stampacu..." << endl; }
protected:
    UpravljacLaserskogStampaca() {}
    UpravljacLaserskogStampaca(const UpravljacLaserskogStampaca& upravljacStampaca) {}
    UpravljacLaserskogStampaca& operator=(const UpravljacLaserskogStampaca& upravljacStampaca) {}
};
int main() {
    UpravljacStampaca &upravljacStampaca = UpravljacStampaca::dajPrimerak();
    upravljacStampaca.stampaj();

    UpravljacLaserskogStampaca &upravljacLaserskogStampaca =
        (UpravljacLaserskogStampaca&) UpravljacLaserskogStampaca::dajPrimerak();
    upravljacLaserskogStampaca.stampaj();

    return 0;
}
