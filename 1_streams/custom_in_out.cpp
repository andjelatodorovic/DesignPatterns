#include <iostream>
#include <iomanip>
#include <complex>

using namespace std;

/* pravimo sablon klase Tacka koja ce da overload-uje/preotereti operatore << i >> za upisivanje i iscitavanje
   iz stream-ova kako bismo mogli direktno da citamo/pisemo objekte tipa Tacka. Klasa ima dva parametra
   razmak - na koliko mesta ce da se stampaju koordinate x i y tacke i znak - kojim znakom ce biti popunjene
   praznine u stampanju */
template <int razmak, char znak>
class Tacka {
   private:
      int x;
      int y;
   public:
      Tacka(){
         x = 0;
         y = 0;
      }
      Tacka(int x, int y){
         this->x = x;
         this->y = y;
      }
      friend ostream &operator<<(ostream &output, const Tacka &p) {
         output << "(" << setfill(znak) << setw(razmak) << p.x << ", " << setfill(znak) << setw(razmak) << p.y << ")" << endl;
         return output;
      }
      friend istream &operator>>(istream  &input, Tacka &p) {
         input >> p.x >> p.y;
         return input;
      }
};

/* preopterecujemo operator za izlaz << za tip complex<T>. Inace standardan metod za ucitavanje
   tipa complex<T> je (x, y) */
template <class T>
ostream& operator<<(ostream&s, complex<T> z)  {
    return s << z.real() << " + " << z.imag() << "i";
}

int main() {
   Tacka<10, ' '> p1(11, 10);
   Tacka<5, '.'> p2(5, 11), p3;

   /* imamo dve tacke sa razlicitim parametrima i vec dodeljenim koordinatama i trecu koju unosimo
      preko opterecenog operatora >> i sve te tacke stampamo sa << */
   cout << "Prva tacka: " << p1 << endl;
   cout << "Druga tacka:" << p2 << endl;
   cout << "Unesite tacku (u formatu x y, npr 3 4): ";
   cin >> p3;
   cout << "Treca tacka:" << p3 << endl;
   /* stampamo complex<int> sa << i ucitavamo i stampano uneseni complex<float> */
   complex<int> a(1, 3);
   cout << a << endl;
   complex<float> b;
   cout << "Unesite kompleksan broj (u formatu (Realni, Imaginarni), npr (3, 4)): ";
   cin >> b;
   cout << b << endl;


   return 0;
}
