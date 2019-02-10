#include <cstring>
#include <iostream>

using namespace std;

/* konkretan proizvod koji ima vise delova (u ovom slucaju trup, krila) */
class Avion {
private:
    string trup;
    string krila;
public:
    Avion() {}
    string dajTrup() { return trup; }
    void postaviTrup(string trup) { this->trup = trup; }
    string dajKrila() { return krila; }
    void postaviKrila(string krila) { this->krila = krila; }

    void prikazi() {
        cout << "Avion izgleda ovako -> " << endl;
        cout << "Trup: " << trup << endl;
        cout << "Krila: " << krila << endl;
    }
};

/* apstraktni graditelj, ima mogucnost da proizvodu podesava delove pri kreiranju proizvoda */
class GraditeljAviona {
public:
    virtual void napraviTrup() = 0;
    virtual void napraviKrila() = 0;
    virtual Avion* dajAvion() = 0;
};

/* konkretan graditelj */
class GraditeljMlaznihAviona : public GraditeljAviona {
private:
    Avion* product;
public:
    GraditeljMlaznihAviona() {
        product = new Avion();
    }
    void napraviTrup() {
        product->postaviTrup("Metalna sasija za MLAZNI avion");
    }
    void napraviKrila() {
        product->postaviKrila("Metalna krila za MLAZNI avion");
    }
    Avion* dajAvion() {
        return product;
    }
};

/* konkretan graditelj */
class GraditeljAvionaSaPropelerom : public GraditeljAviona {
private:
    Avion* product;
public:
    GraditeljAvionaSaPropelerom() {
        product = new Avion();
    }
    void napraviTrup() {
        product->postaviTrup("Metalna sasija za PROPELERSKI avion");
    }
    void napraviKrila() {
        product->postaviKrila("Metalna krila za PROPELERSKI avion");
    }
    Avion* dajAvion() {
        return product;
    }
};

/* updavljac/director koji koristeci graditelja pravi proizvod i vraca nam gotov proizvod */
class Upravljac {
public:
    Avion* napraviAvion(GraditeljAviona *m) {
        m->napraviTrup();
        m->napraviKrila();
        return m->dajAvion();
    }
};

/* kreiramo upravljaca i prosledjujemo mu konkretnog graditelja da bi nam napravio gotov proizvod */
int main() {
    Upravljac *d = new Upravljac();
    cout << "Napravi MLAZNI avion" << endl;
    Avion *a = d->napraviAvion(new GraditeljMlaznihAviona());
    a->prikazi();

    cout << "Napravi PROPELERNI avion" << endl;
    Avion *b = d->napraviAvion(new GraditeljAvionaSaPropelerom());
    b->prikazi();

    return 0;
}
