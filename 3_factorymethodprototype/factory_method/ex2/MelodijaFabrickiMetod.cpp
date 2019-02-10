#include <iostream>

using namespace std;

enum Zanr { ROK, BALADA, POP};

/* apstraktan proizvod, ima jedan metod za bi demonstrirali koriscenje proizvoda */
class Melodija {
public:
    virtual void sviraj() = 0;
};

/* konkretan proizvod */
class RokMelodija: public Melodija {
public:
    void sviraj() {
        cout << "Pogledaj dom svoj andjele..." << endl;
    }
};
/* konkretan proizvod */
class BaladaMelodija: public Melodija {
    void sviraj() {
        cout << "Bila je tako leeeeepa..." << endl;
    }
};
/* konkretan proizvod */
class PopMelodija: public Melodija {
    void sviraj() {
        cout << "Ispred teatra Baljsoj, ja sam te cekao..." << endl;
    }
};
/* apstraktan kreator/stvaralac koji ima fabricki metod dajMelodiju */
class MuzickaKutija {
public:
    virtual Melodija* dajMelodiju(Zanr zanr) = 0;
};
/* konkretan kreator/stvaralac koji na osnovu prosledjenog tipa kreira odgovarajuci
   konkretan proizvod, drugacije resenje je da imamo za svaki konkretan proizvod po jednog
   konkretnog kreatora/stvaraoca */
class DomacaMuzickaKutija: public MuzickaKutija {
public:
    Melodija* dajMelodiju(Zanr zanr) {
        switch (zanr) {
        case ROK: return new RokMelodija();
        case POP: return new PopMelodija();
        case BALADA: return new BaladaMelodija();
        default: return NULL;
        }
    }
};

/* koriscenje sablona fabricki metod, kreiramo konkretnog kreatora (DomacaMuzickaKutija) vidljiv kao MuzickaKutija
   pomocu njega konkretan proizvod (RokMelodija) vidljiv kao Melodija i koristimo taj konkretan proizvod,
   ostatak testa je slican */
int main() {
    MuzickaKutija *muzickaKutija = new DomacaMuzickaKutija();
    Melodija *rokMelodija = muzickaKutija->dajMelodiju(ROK);
    rokMelodija->sviraj();

    Melodija *popMelodija = muzickaKutija->dajMelodiju(POP);
    popMelodija->sviraj();

    cout << "Unesi vrstu melodije koju hoces da sviram (R-Rok, B-Balada, P-Pop): ";
    char tip;
    cin >> tip;
    Melodija *mojaMelodija;
    switch (toupper(tip)) {
    case 'R': mojaMelodija = muzickaKutija->dajMelodiju(ROK); break;
    case 'B': mojaMelodija = muzickaKutija->dajMelodiju(BALADA); break;
    case 'P': mojaMelodija = muzickaKutija->dajMelodiju(POP); break;
    default: mojaMelodija = NULL;
    }
    if (mojaMelodija != NULL) {
        mojaMelodija->sviraj();
    } else {
        cout << "Nepostojeca vrsta melodije" << endl;
    }

    delete muzickaKutija;
    delete rokMelodija;
    delete popMelodija;
    delete mojaMelodija;
}
