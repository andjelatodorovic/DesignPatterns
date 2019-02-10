#include <iostream>
#include <vector>

using namespace std;
/* primalac akcije / receiver */
class CDigitron {
public:
    CDigitron(): m_rezultat(0) {}
    int Dodaj(int broj) {
        return m_rezultat += broj;
    }
    int Oduzmi(int broj) {
        return m_rezultat -= broj;
    }
    int Pomnozi(int broj) {
        return m_rezultat *= broj;
    }
    int Podeli(int broj) {
        if (broj == 0) throw("Zabranjeno je deljenje sa nulom!");
        return m_rezultat /= broj;
    }
    int PostaviRezultat(int rezultat) {
        return m_rezultat = rezultat;
    }
    int DajRezultat() {
        return m_rezultat;
    }
private:
    int     m_rezultat;
};
/* interfejs komande */
class IKomanda {
public:
    virtual int Izvrsi() = 0;
};
/* konkretna komanda, interni parametri komande (m_operacija) omogucavaju razlicite manifestacije operacije Izvrsi,
   umesto da pravimo razlicite konkretne komande za svaku od operacija,
   putem konstruktora dodeljujemo i primaoca akcije */
class CDigitronKomanda: public IKomanda {
public:
    CDigitronKomanda(CDigitron* digitron): m_digitron(digitron), m_operacija('+'), m_broj(0) {}
    CDigitronKomanda(CDigitron* digitron, char operacija, int broj): m_digitron(digitron), m_operacija(operacija), m_broj(broj) {}
    virtual ~CDigitronKomanda() {}
    /* metod Execute */
    virtual int Izvrsi() {
        switch (m_operacija) {
            case '+': return m_digitron->Dodaj(m_broj);
            case '-': return m_digitron->Oduzmi(m_broj);
            case '*': return m_digitron->Pomnozi(m_broj);
            case '/': return m_digitron->Podeli(m_broj);
            default: throw("Nepostojeca operacija");
        }
    }
    virtual int Izvrsi(char operacija, int broj) {
        cout << "Izvrsi(" << operacija << ", " << broj << ")" << endl;
        m_operacija = operacija;
        m_broj = broj;
        return Izvrsi();
    }
protected:
    CDigitron*  m_digitron;
    char        m_operacija;
    int         m_broj;
};
/* konkretna komanda koja omogucava operaciju undo/povracanje na prethodno stanje
   implementirana tako sto cuva unutar sebe stanje pre nego sto je izvrsena operacija */
class CPovratljivaDigitronKomanda: public CDigitronKomanda {
public:
    CPovratljivaDigitronKomanda(CDigitron* digitron): CDigitronKomanda(digitron), m_stariRezultat(0) {}
    CPovratljivaDigitronKomanda(CDigitron* digitron, char operacija, int broj): CDigitronKomanda(digitron, operacija, broj), m_stariRezultat(0) {}

    virtual int Izvrsi() {
        m_stariRezultat = m_digitron->DajRezultat();
        return CDigitronKomanda::Izvrsi();
    }
    virtual int Izvrsi(char operacija, int broj) {
        m_stariRezultat = m_digitron->DajRezultat();
        return CDigitronKomanda::Izvrsi(operacija, broj);
    }
    virtual int VratiNazad() {
        m_digitron->PostaviRezultat(m_stariRezultat);
    }
protected:
    int     m_stariRezultat;
};
/* upravljac komandi koji je i Invoker / pokretac akcije, unutar sebe cuva listu svih izvrsenih komandu
   pa tako moze da se vrati na stanje pre nego sto je izvrsena neka konkretna komanda,
   tj. da nudi mogucnost undo/vracanje na neko prethodno stanje */
class UpravljacKomandi {
public:
    virtual ~UpravljacKomandi() {
        for (vector<IKomanda*>::iterator it = m_listaKomandi.begin(); it != m_listaKomandi.end(); ++it) {
            delete *it;
        }
        m_listaKomandi.clear();
    }
    virtual int IzvrsiKomandu(IKomanda *komanda) {
        m_listaKomandi.push_back(komanda);
        return komanda->Izvrsi();
    }
    virtual int VratiKomandu(int indeks) {
        if (indeks <= 0 || indeks > m_listaKomandi.size()) {
            throw("Nepostojeca komanda");
        }
        if (CPovratljivaDigitronKomanda* komanda = dynamic_cast<CPovratljivaDigitronKomanda*>(m_listaKomandi[indeks - 1])) {
            return komanda->VratiNazad();
        } else {
            throw("Komanda ne moze da se vrati nazad!");
        }
    }
protected:
    vector<IKomanda*>   m_listaKomandi;
};
/* kreiramo primaoca akcije/receiver i upravljac komandi, zatim klijent vrsi malu interakciju
   birajuci koju konkretno operaciju zeli da izvrsi, nakon toga se kreira konkretna komanda koja se prosledi upravljacu
   moguce je da klijent bira i da vrati stanje na neko prethodno prosledjujuci komandu U i redni broj komande koju zeli da vrati */
int main() {
    CDigitron* digitron = new CDigitron();
    UpravljacKomandi* upravljacKomandi = new UpravljacKomandi();
    char ch;
    int broj;
    do {
        cout << "Odaberite operaciju + - * / q(izlaz) U(undo)  > ";
        cin >> ch;
        if (ch == 'q' || ch == 'Q') break;
        cout << "Unesite broj > ";
        cin >> broj;
        try {
            if (ch != 'u' && ch != 'U') {
                cout << "Trenutni rezultat: " << upravljacKomandi->IzvrsiKomandu(new CPovratljivaDigitronKomanda(digitron, ch, broj)) << endl;
            }
            if (ch == 'u' || ch == 'U') {
                cout << "Trenutni rezultat: " << upravljacKomandi->VratiKomandu(broj) << endl;
            }
        } catch (const char* s) {
            cout << "GRESKA: " << s << endl;
        }
    } while (ch != 'q');

    delete upravljacKomandi;
    delete digitron;

    return 0;
}

