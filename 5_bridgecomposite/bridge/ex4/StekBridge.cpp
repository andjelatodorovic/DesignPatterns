#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <memory>

using namespace std;

template<class T> class StekImplementacija;
template<class T> class VectorStekImpl;
template<class T> class NizStekImpl;

enum TipSteka { VEKTOR, NIZ };

/* apstrakcija */
template<class T>
class Stek {
private:
    StekImplementacija<T> *m_stekImpl;
public:
    Stek() { m_stekImpl = new VectorStekImpl<T>(); }
    /* u ovom slucaju implementora ne prosledjujemo preko konstruktora ili pomocu nekog posebnog
    metoda za postavljanje implementora, vec ga kreiramo unutar konstruktora u zavisnosti
    od tipa implementora koji zelimo da koristimo, a tip se konfigurise preko parametra konstruktora,
    u ovom slucaju to je parametar tipSteka, na ovaj nacin je implementor blisko vezan sa samom apstrakcijom
    sto je u ovom slucaju i neophodno */
    Stek(TipSteka tipSteka) {
        if (tipSteka == VEKTOR) {
            m_stekImpl = new VectorStekImpl<T>();
        } else if (tipSteka == NIZ) {
            m_stekImpl = new NizStekImpl<T>();
        } else {
            cout << "Nepostojeci tip steka." << endl;
        }
    }
    virtual ~Stek() { delete m_stekImpl; }
    virtual void stavi(T element) { m_stekImpl->stavi(element); }
    virtual T izvadi() { return m_stekImpl->izvadi(); }
    virtual T vrh() { return m_stekImpl->vrh(); }
    virtual bool jePrazan() { return m_stekImpl->jePrazan(); }
    virtual bool jePun() { return m_stekImpl->jePun(); }
    void prikazi() { m_stekImpl->prikazi(); }
};
/* konkretna apstrakcija A
   pravimo stek koji mozemo da konfigurisemo tako da ubacuje samo vrednosti <= maksVrednost */
template<class T, T maksVrednost>
class LimitiraniStek: public Stek<T> {
private:
    int m_ukupnoOdbijeno;
public:
    LimitiraniStek(): Stek<T>(VEKTOR) { m_ukupnoOdbijeno = 0; }
    LimitiraniStek(TipSteka tipSteka): Stek<T>(tipSteka) { m_ukupnoOdbijeno = 0; }
    virtual ~LimitiraniStek() {}
    virtual int dajUkupnoOdbijeno() { return m_ukupnoOdbijeno; }
    virtual void stavi(T element) {
        if (element > maksVrednost) {
            m_ukupnoOdbijeno ++;
        } else {
            Stek<T>::stavi(element);
        }
    }
};

/* implementator */
template<class T>
class StekImplementacija {
public:
    virtual ~StekImplementacija() { };
    virtual void stavi(T element) = 0;
    virtual T izvadi() = 0;
    virtual T vrh() = 0;
    virtual bool jePrazan() = 0;
    virtual bool jePun() = 0;
    virtual void prikazi() = 0;
};
/* konkretni implementor */
template<class T>
class VectorStekImpl: public StekImplementacija<T> {
private:
    vector<T> m_sadrzaj;
    static int s_kapacitet;
public:
    VectorStekImpl() {}
    virtual ~VectorStekImpl() { }
    virtual void stavi(T element) {
        if (!jePun()) { m_sadrzaj.push_back(element); }
    }
    virtual T izvadi() {
        if (!jePrazan()) {
            T zadnji = m_sadrzaj.back();
            m_sadrzaj.pop_back();
            return zadnji;
        } else {
            cout << "Greska: Prazan stek" << endl;
            return -1;
        }
    };
    virtual T vrh() {
        if (!jePrazan()) { return m_sadrzaj.back(); }
        return -1;
    }
    virtual bool jePrazan() { return m_sadrzaj.size() == 0; };
    virtual bool jePun() { return m_sadrzaj.size() >= s_kapacitet; }
    virtual void prikazi() {
        cout << "<VEKTOR STEK>: ";
        for (int i = 0; i < m_sadrzaj.size(); i ++) cout << m_sadrzaj[i] << "  ";
        cout << endl;
    }
};

template<class T> int VectorStekImpl<T>::s_kapacitet = 10;

/* konkretni implementor */
template<class T>
class NizStekImpl: public StekImplementacija<T> {
private:
    int m_indeks;
    T* m_sadrzaj;
    static int s_kapacitet;
public:
    NizStekImpl(): StekImplementacija<T>() { m_sadrzaj = new T[s_kapacitet]; m_indeks = 0; }
    virtual ~NizStekImpl() {
        delete[] m_sadrzaj;
    }
    virtual void stavi(T element) {
        if (!jePun()) { m_sadrzaj[m_indeks ++] = element; }
    }
    virtual T izvadi() {
        if (!jePrazan()) {
            T zadnji = m_sadrzaj[--m_indeks];
            return zadnji;
        } else {
            cout << "Greska: Prazan stek" << endl;
            return -1;
        }
    };
    virtual T vrh() {
        if (!jePrazan()) { return m_sadrzaj[m_indeks - 1]; }
        return -1;
    }
    virtual bool jePrazan() { return m_indeks == 0; };
    virtual bool jePun() { return m_indeks >= s_kapacitet; }
    virtual void prikazi() {
        cout << "<NIZ STEK>: ";
        for (int i = 0; i < m_indeks; i ++) cout << m_sadrzaj[i] << "  ";
        cout << endl;
    }
};

template<class T> int NizStekImpl<T>::s_kapacitet = 15;

int main() {
    /* kreiramo dva steka sa razlicitim implementorima */
    Stek<int> *limitiraniVektorStek = new LimitiraniStek<int, 20>(VEKTOR);
    Stek<double> *nizStek = new Stek<double>(NIZ);
    /* generisemo 30ak slucajnih brojeva izmedju 0 i 39 i ubacimo ih i u jedan i u drugi stek */
    srand(time(NULL));
    for (int i = 0; i < 30; i ++) {
        int num = rand() % 40;
        cout << num << " ";
        limitiraniVektorStek->stavi(num);
        nizStek->stavi(num);
    }
    cout << endl;
    /* i prikazemo sadrzaj oba steka */
    limitiraniVektorStek->prikazi();
    cout << fixed << setprecision(2);

    /* u ovom slucaju objekti implementori ce biti izbrisani unutar destruktora apstrakcije */
    delete limitiraniVektorStek;
    delete nizStek;

    return 0;
}
