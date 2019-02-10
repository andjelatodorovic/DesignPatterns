#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

/* funkcija koja koristi ostringstream da pretvori broj (tipa int) u string */
string broj2string(int n) {
    ostringstream out;
    out << n;
    return out.str();
}

/* pretpostavljamo da je osoba zapisana u formatu
   ime prezime, broj_telefona */
/* kreiramo template klase Osoba koja moze da ima dva parametra broj_mesta (na koliko mesta ce da budu
   stampana polja tipa objekta tipa Osoba) a razdvajanje biti karakter kojim ce da se razdvajaju ta polja
   prilikom stampanja */
template<int broj_mesta, char razdvajanje>
class Osoba {
   private:
      string ime, prezime, broj_telefona;
   public:
      Osoba(){
         ime = prezime = broj_telefona = "";
      }
      Osoba(string ime, string prezime, string broj_telefona){
         this->ime = ime;
         this->prezime = prezime;
         this->broj_telefona = broj_telefona;
      }
      /* overload-ujem/preopterecujemo operatore citanja/pisanja << i >> kako bismo mogli
         da ih koristimo za ucitavanja/pisanje objekata tipa Osoba,
         nismo testirali moguce scenarije u kojima moze doci do greske prilikom iscitavanja
         objekta iz stream-a */
      friend ostream &operator<<(ostream &output, const Osoba &osoba) {
         output << setw(broj_mesta) << osoba.ime
                << razdvajanje << setw(broj_mesta) << osoba.prezime
                << razdvajanje << setw(broj_mesta) << osoba.broj_telefona << endl;
         return output;
      }
      friend istream &operator>>(istream  &input, Osoba &osoba) {
         char ch;
         input >> osoba.ime >> osoba.prezime >> ch >> osoba.broj_telefona;

         return input;
      }
};

int main() {
    /* u file lepi_imponik.txt cemo da upisemo sve osobe iscitane iz svih file-ova */
    ofstream out("lepi_imenik.txt", ios::app);
    int idx = 1;
    while (true) {
        /* program redom iscitava file-ove imenik1.txt, imenik2.txt, ... dok ne naidje na imenikN.txt koji
           ne postoji i tu prekida iscitavanje */
        string fileName = "imenik" + broj2string(idx) + ".txt";
        ifstream in(fileName.c_str());
        if (!in.is_open()) {
           cout << "Kraj Ucitavanja"<< endl;
           break;
        }
        Osoba<20, '#'> osoba;
        cout << "Citam file " << fileName << endl;
        while (!in.eof()) {
            in >> osoba;
            out << osoba;
            cout << osoba;
        }
        in.close();
        idx ++;
    }
    out.close();
}
