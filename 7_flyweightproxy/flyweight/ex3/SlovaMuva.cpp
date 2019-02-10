#include<map>
#include<iostream>

using namespace std;

/* muva */
class ISlovo {
public:
    virtual ~ISlovo() {}
    virtual void Prikazi(int visina, int sirina, int debljina) = 0;
protected:
    ISlovo(char znak, int sirina, int visina, int debljina)
        :m_znak(znak), m_sirina(sirina), m_visina(visina), m_debljina(debljina) {}
    char    m_znak;
    int     m_sirina;
    int     m_visina;
    int     m_debljina;
};
/* konkretna muva */
class CSlovoA: public ISlovo {
public:
    CSlovoA(): ISlovo('A', 10, 10, 2) {}
    virtual ~CSlovoA() {}
    virtual void Prikazi(int visina, int sirina, int debljina) {
        m_visina = visina;
        m_sirina = sirina;
        m_debljina = debljina;
        cout << "Prikazujem slovo A, visina = " << m_visina << ", sirina = " << m_sirina << ", debljina = " << m_debljina << endl;
    }
};
/* konkretna muva */
class CSlovoB: public ISlovo {
public:
    CSlovoB(): ISlovo('B', 10, 10, 2) {}
    virtual ~CSlovoB() {}
    virtual void Prikazi(int visina, int sirina, int debljina) {
        m_visina = visina;
        m_sirina = sirina;
        m_debljina = debljina;
        cout << "Prikazujem slovo B, visina = " << m_visina << ", sirina = " << m_sirina << ", debljina = " << m_debljina << endl;
    }
};
/* konkretna muva */
class CSlovoC: public ISlovo {
public:
    CSlovoC(): ISlovo('C', 10, 10, 2) {}
    virtual ~CSlovoC() {}
    virtual void Prikazi(int visina, int sirina, int debljina) {
        m_visina = visina;
        m_sirina = sirina;
        m_debljina = debljina;
        cout << "Prikazujem slovo C, visina = " << m_visina << ", sirina = " << m_sirina << ", debljina = " << m_debljina << endl;
    }
};
/* fabrika muva */
class FabrikaSlova {
public:
    FabrikaSlova() {}
    virtual ~FabrikaSlova() {
        while (m_kolekcijaSlova.begin() != m_kolekcijaSlova.end()) {
            delete m_kolekcijaSlova.begin()->second;
            m_kolekcijaSlova.erase(m_kolekcijaSlova.begin());
        }
    }
    virtual ISlovo* dajSlovo(char slovo) {
        cout << "dajSlovo(" << slovo << ")" << endl;
        if (m_kolekcijaSlova.find(slovo) == m_kolekcijaSlova.end()) {
            switch (slovo) {
                case 'A': m_kolekcijaSlova[slovo] = new CSlovoA(); break;
                case 'B': m_kolekcijaSlova[slovo] = new CSlovoB(); break;
                case 'C': m_kolekcijaSlova[slovo] = new CSlovoC(); break;
                default: throw(string("Slovo nije podrzano"));
            }
        }
        return m_kolekcijaSlova[slovo];
    }
protected:
    map<char, ISlovo*>   m_kolekcijaSlova;
};

int main() {
    FabrikaSlova fabrikaSlova;
    string tekst = "BABA BACA ACA";
    for (int i = 0; i < tekst.size(); ++i) {
        try {
            ISlovo* slovo = fabrikaSlova.dajSlovo(tekst[i]);
            slovo->Prikazi(10, 5, i % 3 + 3);
        } catch (string ex) {
            cout << ex << endl;
        }
    }

    return 0;
}
