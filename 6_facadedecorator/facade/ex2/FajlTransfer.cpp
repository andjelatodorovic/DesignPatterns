#include <iostream>
#include <memory>

using namespace std;

/* kompleksan podsistem - za citanje/pisanje na USB */
class USBDrajver {
public:
    bool jeDostupan() {
        return false;
    }
    void poveziSe() {
        cout << "Povezujem se na USB..." << endl;
    }
    void posalji(string fajl) {
        cout << fajl << " je uspesno poslan putem USB." << endl;
        m_fajl = fajl;
    }
    string citaj() {
        return m_fajl;
    }
private:
    string  m_fajl;
};
/* kompleksan podsistem - citanje i pisanje koriscenjem Bluetooth-a */
class BTDrajver {
public:
    bool jeDostupan() {
        return true;
    }
    void poveziSe() {
        cout << "Povezujem se na Bluetooth..." << endl;
    }
    void potvrdiIdentitet() {
        cout << "Potvrdjujem identitet za Bluetooth..." << endl;
    }
    void posalji(string fajl) {
        cout << fajl << " uspesno poslan putem BT." << endl;
        m_fajl = fajl;
    }
private:
    string  m_fajl;
};

/* fasada - klijentu je dostupan metod posaljiFajl pomocu koga moze da posalje fajl
   nacin na koji je to realizovano nije problematika klijenta vec onoga ko kreira fasadu
   on je zaduzen da vrsi pravilnu interakciju sa razlicitim podsistemima da bi ostvario
   ono sto je klijentu neophodno
   u ovom slucaju proverava dostupnost USB servisa ako je dostupan koristi ga za slanje
   fajla preko USB protokola, u suprotnom proverava dostupnost Bluetooth servisa i ako je
   dostupan salje fajl preko njega */
class FajlTransfer {
public:
    void posaljiFajl(string fajl) {
        unique_ptr<USBDrajver> usb(new USBDrajver());
        unique_ptr<BTDrajver> bt(new BTDrajver());
        if (usb->jeDostupan()) {
            usb->poveziSe();
            usb->posalji(fajl);
        } else if (bt->jeDostupan()) {
            bt->poveziSe();
            bt->potvrdiIdentitet();
            bt->posalji(fajl);
        } else {
            cout << "Nedostupni servisi USB i BT" << endl;
        }
    }
};

/* sada klijent ima mnogo manje problema kada koristi fasadu da bi ostvario
   ono sto zeli, u ovom slucaju da posalje fajl */
int main() {
    unique_ptr<FajlTransfer> ft(new FajlTransfer());
    ft->posaljiFajl("Izvestaj o rezultatima");

    return 0;
}
