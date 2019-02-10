#include <cstdio>
#include <iostream>

using namespace std;

/* Handler / razresavac */
class TesterDeljivosti {
public:
    TesterDeljivosti(): m_naredniTesterDeljivosti(NULL) {}
    virtual void testirajDeljivost(int broj) {
        if (m_naredniTesterDeljivosti != NULL) {
            m_naredniTesterDeljivosti->testirajDeljivost(broj);
        } else {
            cout << "Ne znam kojim brojem je deljiv broj " << broj << "." << endl;
        }
    }
    void postaviNaredniTesterDeljivosti(TesterDeljivosti* testerDeljivosti) {
        m_naredniTesterDeljivosti = testerDeljivosti;
    }
private:
    TesterDeljivosti*   m_naredniTesterDeljivosti;
};
/* konkretan razresavac / Concrete Handler */
class TesterDeljivostiSa2: public TesterDeljivosti {
public:
    void testirajDeljivost(int broj) {
        if (broj % 2 == 0) {
            cout << broj << " je deljiv sa 2!" << endl;
        } else {
            TesterDeljivosti::testirajDeljivost(broj);
        }
    }
};
/* konkretan razresavac / Concrete Handler */
class TesterDeljivostiSa3: public TesterDeljivosti {
public:
    void testirajDeljivost(int broj) {
        if (broj % 3 == 0) {
            cout << broj << " je deljiv sa 3!" << endl;
        } else {
            TesterDeljivosti::testirajDeljivost(broj);
        }
    }
};
/* konkretan razresavac / Concrete Handler */
class TesterDeljivostiSa5: public TesterDeljivosti {
public:
    void testirajDeljivost(int broj) {
        if (broj % 5 == 0) {
            cout << broj << " je deljiv sa 5!" << endl;
        } else {
            TesterDeljivosti::testirajDeljivost(broj);
        }
    }
};

int main() {
    TesterDeljivosti *testerDeljivostiSa2 = new TesterDeljivostiSa2();
    TesterDeljivosti *testerDeljivostiSa3 = new TesterDeljivostiSa3();
    TesterDeljivosti *testerDeljivostiSa5 = new TesterDeljivostiSa5();

    testerDeljivostiSa2->postaviNaredniTesterDeljivosti(testerDeljivostiSa3);
    testerDeljivostiSa3->postaviNaredniTesterDeljivosti(testerDeljivostiSa5);

    // out: deljiv sa 2
    testerDeljivostiSa2->testirajDeljivost(100);
    // out: deljiv sa 3
    testerDeljivostiSa2->testirajDeljivost(105);
    // out: deljiv sa 5
    testerDeljivostiSa2->testirajDeljivost(115);
    // nepokriven slucaj
    testerDeljivostiSa2->testirajDeljivost(107);

    delete testerDeljivostiSa2;
    delete testerDeljivostiSa3;
    delete testerDeljivostiSa5;

    return 0;
}
