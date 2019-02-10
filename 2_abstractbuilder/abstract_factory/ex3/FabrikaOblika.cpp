/* primer iz knjige Design Patterns Explained Simply. */

#include <iostream>

/* otkomentarisati ako zelimo da koristimo fabrku FabrikaPravilnihOblika */

//#define PRAVILNI

using namespace std;

/* astraktni proizvod */
class Oblik {
  public:
    Oblik() {
      id = ukupanBroj++;
    }
    virtual void nacrtaj() = 0;
  protected:
    int id;
    static int ukupanBroj;
};
int Oblik::ukupanBroj = 0;

/* konkretan proizvod A1 */
class Krug : public Oblik {
  public:
    void nacrtaj() {
      cout << "Nacrtaj krug #" << id << endl;
    }
};
/* konkretan proizvod A2 */
class Kvadrat : public Oblik {
  public:
    void nacrtaj() {
      cout << "Nacrtaj kvadrat #" << id << endl;
    }
};
/* konkretan proizvod B1 */
class Elipsa : public Oblik {
  public:
    void nacrtaj() {
      cout << "Nacrtaj elipsu #" << id << endl;
    }
};
/* konkretan proizvod B2 */
class Pravougaonik : public Oblik {
  public:
    void nacrtaj() {
      cout << "Nacrtaj pravougaonik #" << id << endl;
    }
};
/* apstraktna fabrika */
class Fabrika {
  public:
    virtual Oblik* napraviObliOblik() = 0;
    virtual Oblik* napraviOstarOblik() = 0;
};
/* konkretna fabrika A, za konkretne proizvode A1 i A2 */
class FabrikaPravilnihOblika : public Fabrika {
  public:
    Oblik* napraviObliOblik() {
      return new Krug();
    }
    Oblik* napraviOstarOblik() {
      return new Kvadrat();
    }
};
/* konkretna fabrika B, za konkretne proizvode B1 i B2 */
class FabrikaNepravilnihOblika : public Fabrika {
  public:
    Oblik* napraviObliOblik()   {
      return new Elipsa();
    }
    Oblik* napraviOstarOblik() {
      return new Pravougaonik();
    }
};

int main() {
#ifdef PRAVILNI
  Fabrika* fabrika = new FabrikaPravilnihOblika();
#else
  Fabrika* fabrika = new FabrikaNepravilnihOblika();
#endif
  Oblik* oblici[3];

  oblici[0] = fabrika->napraviObliOblik();
  oblici[1] = fabrika->napraviOstarOblik();
  oblici[2] = fabrika->napraviObliOblik();

  for (int i = 0; i < 3; i ++) {
    oblici[i]->nacrtaj();
  }
}
