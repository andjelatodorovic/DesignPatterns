#include <iostream>

using namespace std;

class CFliper;

/* Handler / razresavac */
class IUpravljacZetonima {
public:
    IUpravljacZetonima(CFliper* fliper): m_naredniUpravljac(NULL), m_fliper(fliper) {}
    virtual ~IUpravljacZetonima() {
        if (m_naredniUpravljac != NULL) {
            delete m_naredniUpravljac;
        }
    }
    virtual void DodajNaredniUpravljac(IUpravljacZetonima *naredniUpravljac) {
        if (m_naredniUpravljac == NULL) {
            m_naredniUpravljac = naredniUpravljac;
        } else {
            m_naredniUpravljac->DodajNaredniUpravljac(naredniUpravljac);
        }
    }
    virtual void UbaciNovcic(int novcic) {
        if (m_naredniUpravljac == NULL) {
            cout << "Moneta od " << novcic << " ne moze da se koristi u ovom fliperu." << endl;
        } else {
            m_naredniUpravljac->UbaciNovcic(novcic);
        }
    }
protected:
    CFliper*         m_fliper;
    IUpravljacZetonima* m_naredniUpravljac;
    void UbaciUFliper(int novcic);
};

/* konkretan razresavac */
template<int moneta>
class CUpravljacZetonima: public IUpravljacZetonima {
public:
    CUpravljacZetonima(CFliper* fliper): IUpravljacZetonima(fliper) {}
    virtual ~CUpravljacZetonima() { }
    /* metod HandleRequest() koji razresava zahtev, u ovom slucaju detektovanje novcica
    koji je ubacen u fliper */
    virtual void UbaciNovcic(int novcic);
};

/* klijent, interno kreira listu razresavaca */
class CFliper {
public:
    friend class IUpravljacZetonima;
    CFliper(int cenaIgre): m_cenaIgre(cenaIgre), m_stanje(0) {
        m_upravljacZetonima = new CUpravljacZetonima<1>(this);
        m_upravljacZetonima->DodajNaredniUpravljac(new CUpravljacZetonima<5>(this));
        m_upravljacZetonima->DodajNaredniUpravljac(new CUpravljacZetonima<10>(this));
        m_upravljacZetonima->DodajNaredniUpravljac(new CUpravljacZetonima<20>(this));
    }
    virtual ~CFliper() {
        delete m_upravljacZetonima;
    }
    friend ostream& operator<<(ostream& out, const CFliper& fliper) {
        out << "Stanje na fliperu: " << fliper.m_stanje << " RSD. Fliper prima monete od 1, 5, 10 i 20 RSD.";
        return out;
    }
    virtual void UbaciZeton(int novcic);
    virtual void Igraj() {
        if (m_stanje >= m_cenaIgre) {
            cout << "Igra pocela." << endl;
            m_stanje -= m_cenaIgre;
        } else {
            cout << "Nemate dovoljno novca za igru. Jedna igra kosta " << m_cenaIgre << ", a Vi ste ubacili " << m_stanje << " RSD." << endl;
        }
    }
protected:
    int                 m_cenaIgre;
    int                 m_stanje;
    IUpravljacZetonima* m_upravljacZetonima;
};


void IUpravljacZetonima::UbaciUFliper(int novcic) {
    m_fliper->m_stanje += novcic;
}
template<int moneta>
void CUpravljacZetonima<moneta>::UbaciNovcic(int novcic) {
        if (novcic == moneta) {
            IUpravljacZetonima::UbaciUFliper(novcic);
        } else {
            IUpravljacZetonima::UbaciNovcic(novcic);
        }
    }

void CFliper::UbaciZeton(int novcic) {
    m_upravljacZetonima->UbaciNovcic(novcic);
}

int main() {
    CFliper* fliper = new CFliper(25);
    int odabir;
    do {
        cout << *fliper << endl;
        cout << "Sta zelite:\n 0 - izadji\n 1 - igraj igru\n 2 - ubaci zeton\n > ";
        cin >> odabir;
        if (odabir == 1) {
            fliper->Igraj();
        }
        if (odabir == 2) {
            int moneta;
            cout << "Koju monetu ubacujete: ";
            cin >> moneta;
            fliper->UbaciZeton(moneta);
        }
    } while (odabir != 0);
    /*
    fliper->UbaciZeton(1);
    fliper->UbaciZeton(5);
    cout << *fliper << endl;
    fliper->Igraj();
    fliper->UbaciZeton(8);
    fliper->UbaciZeton(20);
    fliper->UbaciZeton(10);
    fliper->UbaciZeton(5);
    cout << *fliper << endl;
    fliper->Igraj();
    fliper->Igraj();
    fliper->UbaciZeton()
    cout << *fliper << endl;
    */
    delete fliper;

    return 0;
}
